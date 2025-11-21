#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Incluindo o .c para compilação em arquivo único (embora .h seja o ideal em projetos maiores)
#include "source/arvore/Matriz_Arvore.c" 

// --- Funções Auxiliares de Limpeza (Não existiam no original) ---
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
    destruir_coluna_aux(no->col); // Libera a AVL de colunas dentro da linha
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
    
    // CORREÇÃO: Se a entrada é 1.0, assume-se 1% de itens NÃO NULOS (Densidade)
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

    // NOME AJUSTADO: 1.0 aqui significa 1% preenchido (Densidade), não 99% cheio.
    float densidade = 20.0; 
    int tamanho_vetor = 0;
    
    // Cabeçalho CSV para facilitar plotagem
    printf("Num_Elementos,Tempo_Medio_Segundos\n");

    for(int n = 100; n <= 5000; n += 500) { // Reduzi o teto para teste rápido; aumente para 10000 se tiver RAM (~800MB+ na pool)
        double tempo_total_acumulado = 0;
        int repeticoes = 10; // 5 repetições para média estatística

        for(int r = 0; r < repeticoes; r++){
            Dado *entradas = gerar_dados_esparsos(n, densidade, &tamanho_vetor);
            p_matriz_arvore matriz = criar_matriz();
            
            // 1. Popular a matriz (Preparação)
            for (int k = 0; k < tamanho_vetor; k++) {
                inserir_matriz(matriz, entradas[k].i, entradas[k].j, entradas[k].valor);                
            }
        
            // 2. Medição: Inserir vários elementos extras para ter precisão no clock()
            // Medir apenas 1 elemento dá 0ms. Vamos inserir 100 elementos aleatórios novos.
            int qtd_teste = 1000; 
            clock_t inicio = clock();
            for(int t=0; t<qtd_teste; t++) {
                int i = rand() % n;
                int j = rand() % n;
                inserir_matriz(matriz, i, j, 42); // Pode ser update ou insert novo
            }
            clock_t fim = clock();

            // Acumula o tempo por inserção (tempo total do lote / qtd do lote)
            double tempo_deste_round = (double)(fim - inicio) / CLOCKS_PER_SEC;
            tempo_total_acumulado += tempo_deste_round / qtd_teste;

            // IMPORTANTE: Liberar memória das estruturas
            destruir_matriz_completa(matriz);
            free(entradas);
        }
        
        // Média das repetições
        double media_tempo_insercao = tempo_total_acumulado / repeticoes;
        
        // CORREÇÃO PRINTF:
        // 1. Cast para (int) no número de elementos
        // 2. Formatação %.10f para o double de tempo
        int num_elementos = (int)(n * n * (densidade / 100.0));
        printf("%d,%.10f\n", num_elementos, media_tempo_insercao);
    }

    return 0;
}