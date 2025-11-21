#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Incluindo a implementação da Árvore
#include "source/arvore/Matriz_Arvore.c" 

// --- Funções Auxiliares de Limpeza (CRÍTICAS para Multiplicação) ---
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

Dado* gerar_dados_esparsos(int n, float densidade_percentual, int *qtd_retorno) {
    long long total_elementos = (long long)n * n;
    int qtd_nao_nulos = (int)(total_elementos * (densidade_percentual / 100.0));
    
    if (qtd_nao_nulos == 0 && densidade_percentual > 0.0) qtd_nao_nulos = 1;

    *qtd_retorno = qtd_nao_nulos;

    Dado *dados = (Dado *)malloc(qtd_nao_nulos * sizeof(Dado));
    if (!dados) exit(1);

    long long *pool_indices = (long long *)malloc(total_elementos * sizeof(long long));
    if (!pool_indices) { free(dados); exit(1); }

    for (long long k = 0; k < total_elementos; k++) pool_indices[k] = k;

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

    float densidade = 20.0; // 1% preenchido
    int tamanho_vetor = 0;
    
    // CSV Header
    printf("Num_Elementos_A,Tempo_Medio_Multiplicacao_Segundos\n");

    // Cuidado: Multiplicação é pesada. Se N for muito grande (>2000), pode demorar.
    // Ajuste o passo ou o limite conforme a paciência/potência da CPU.
    for(int n = 100; n <= 2500; n += 500) { 
        double tempo_total_acumulado = 0;
        int repeticoes_experimento = 3; // Menos repetições pois a operação é lenta

        for(int r = 0; r < repeticoes_experimento; r++){
            // 1. Gerar e Popular Matriz A
            Dado *entradas = gerar_dados_esparsos(n, densidade, &tamanho_vetor);
            p_matriz_arvore A = criar_matriz();
            
            for (int k = 0; k < tamanho_vetor; k++) {
                inserir_matriz(A, entradas[k].i, entradas[k].j, entradas[k].valor);                
            }
        
            // 2. Medição da Multiplicação C = A * A
            // Fazemos poucas iterações no loop de medição porque C precisa ser alocado e liberado
            int loops_medicao = 1; 
            
            clock_t inicio = clock();
            for(int t=0; t < loops_medicao; t++) {
                // A função multiplicacao_matriz cria uma NOVA matriz internamente
                p_matriz_arvore C = multiplicacao_matriz(A, A);
                
                // CRÍTICO: Liberar C imediatamente após criar, senão a RAM estoura
                destruir_matriz_completa(C);
            }
            clock_t fim = clock();

            double tempo_deste_round = (double)(fim - inicio) / CLOCKS_PER_SEC;
            tempo_total_acumulado += tempo_deste_round / loops_medicao;

            // Limpeza de A e do vetor de entrada
            destruir_matriz_completa(A);
            free(entradas);
        }
        
        double media_final = tempo_total_acumulado / repeticoes_experimento;
        int num_elementos = (int)(n * n * (densidade / 100.0));
        
        printf("%d,%.10f\n", num_elementos, media_final);
    }

    return 0;
}