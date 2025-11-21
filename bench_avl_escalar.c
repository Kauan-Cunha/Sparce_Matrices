#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Incluindo a implementação da Árvore (ajuste o caminho se necessário)
#include "source/arvore/Matriz_Arvore.c" 

// --- Funções Auxiliares de Limpeza (Essenciais para evitar crash por falta de RAM) ---
void destruir_coluna_aux(p_avl_coluna no) {
    if (no == NULL) return;
    destruir_coluna_aux(no->esq);
    destruir_coluna_aux(no->dir);
    free(no);
}

void destruir_linha_aux(p_avl_linha no) {
    if (no == NULL) return;
    destruir_linha_aux(no->esq);
    destruir_linha_aux(no->dir);
    destruir_coluna_aux(no->col); 
    free(no);
}

void destruir_matriz_completa(p_matriz_arvore A) {
    if (A == NULL) return;
    destruir_linha_aux(A->matriz);
    destruir_linha_aux(A->transposta);
    free(A);
}
// -------------------------------------------------------------

typedef struct {
    int i;
    int j;
    int valor;
} Dado;

long long rand_grande(long long max) {
    if (max == 0) return 0;
    unsigned long long r = (unsigned long long)rand() | ((unsigned long long)rand() << 15) | ((unsigned long long)rand() << 30);
    return r % max;
}

// Função para gerar dados aleatórios sem repetição de coordenadas
Dado* gerar_dados_esparsos(int n, float densidade_percentual, int *qtd_retorno) {
    long long total_elementos = (long long)n * n;
    
    // Calcula quantos elementos NÃO serão zero com base na densidade
    int qtd_nao_nulos = (int)(total_elementos * (densidade_percentual / 100.0));
    
    // Garante pelo menos 1 elemento para teste
    if (qtd_nao_nulos == 0 && densidade_percentual > 0.0) qtd_nao_nulos = 1;

    *qtd_retorno = qtd_nao_nulos;

    Dado *dados = (Dado *)malloc(qtd_nao_nulos * sizeof(Dado));
    if (!dados) exit(1);

    long long *pool_indices = (long long *)malloc(total_elementos * sizeof(long long));
    if (!pool_indices) { free(dados); exit(1); }

    for (long long k = 0; k < total_elementos; k++) pool_indices[k] = k;

    // Algoritmo Fisher-Yates para selecionar índices únicos aleatórios
    for (int k = 0; k < qtd_nao_nulos; k++) {
        long long r = k + rand_grande(total_elementos - k);
        long long temp = pool_indices[k];
        pool_indices[k] = pool_indices[r];
        pool_indices[r] = temp;

        long long indice = pool_indices[k];
        dados[k].i = (int)(indice / n);
        dados[k].j = (int)(indice % n);
        dados[k].valor = (rand() % 100) + 1;
    }

    free(pool_indices);
    return dados;
}

int main() {
    srand(time(NULL));

    // Configuração do Teste
    float densidade = 20.0; // 1.0 = 1% da matriz preenchida
    int tamanho_vetor = 0;
    int escalar_val = 42;
    
    // CSV Header
    printf("Num_Elementos,Tempo_Medio_Escalar_Segundos\n");

    // Loop variando o tamanho N da matriz
    for(int n = 100; n <= 5000; n += 1000) { 
        double tempo_total_acumulado = 0;
        int repeticoes_experimento = 5; // Quantas matrizes diferentes testamos

        for(int r = 0; r < repeticoes_experimento; r++){
            // 1. Gerar e Popular a Matriz
            Dado *entradas = gerar_dados_esparsos(n, densidade, &tamanho_vetor);
            p_matriz_arvore matriz = criar_matriz();
            
            for (int k = 0; k < tamanho_vetor; k++) {
                inserir_matriz(matriz, entradas[k].i, entradas[k].j, entradas[k].valor);                
            }
        
            // 2. Medição da Multiplicação por Escalar
            // Como essa operação é rápida para N pequeno mas lenta para N grande,
            // executamos algumas vezes para pegar uma média estável no clock()
            int loops_medicao = 20; 
            
            clock_t inicio = clock();
            for(int t=0; t < loops_medicao; t++) {
                escalar(escalar_val, matriz); // Função do seu Matriz_Arvore.c
            }
            clock_t fim = clock();

            // Calcula o tempo de UMA operação escalar
            double tempo_deste_round = (double)(fim - inicio) / CLOCKS_PER_SEC;
            tempo_total_acumulado += tempo_deste_round / loops_medicao;

            // Limpeza
            destruir_matriz_completa(matriz);
            free(entradas);
        }
        
        double media_tempo_final = tempo_total_acumulado / repeticoes_experimento;
        
        // Número real de elementos na árvore
        int num_elementos = (int)(n * n * (densidade / 100.0));
        
        // Imprime: Quantidade de Nós, Tempo Médio (em segundos)
        printf("%d,%.10f\n", num_elementos, media_tempo_final);
    }

    return 0;
}