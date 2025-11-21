#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "source/hash/Hash.c"

// --- FUNÇÕES DE LIMPEZA ---
void destruir_matriz_esparsa_hash(p_matriz_esparsa A) {
    if (!A) return;
    p_no_hash atual = A->lista_todos;
    while (atual != NULL) {
        p_no_hash temp = atual;
        atual = atual->prox_todos;
        free(temp);
    }
    if (A->tabela_hash) free(A->tabela_hash);
    free(A);
}

void destruir_matrizes_hash(p_matrizes M) {
    if (!M) return;
    destruir_matriz_esparsa_hash(M->normal);
    destruir_matriz_esparsa_hash(M->transposta);
    free(M);
}

// --- DADOS ---
typedef struct { int i, j, valor; } Dado;
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
    long long *pool_indices = (long long *)malloc(total_elementos * sizeof(long long));
    if (!dados || !pool_indices) exit(1);
    for (long long k = 0; k < total_elementos; k++) pool_indices[k] = k;
    for (int k = 0; k < qtd_nao_nulos; k++) {
        long long r = k + rand_grande(total_elementos - k);
        long long temp = pool_indices[k]; pool_indices[k] = pool_indices[r]; pool_indices[r] = temp;
        long long indice = pool_indices[k];
        dados[k].i = (int)(indice / n); dados[k].j = (int)(indice % n); dados[k].valor = (rand() % 100) + 1;
    }
    free(pool_indices);
    return dados;
}

int main() {
    srand(time(NULL));
    float densidade = 10.0; // 1%
    int tamanho_vetor = 0;
    
    printf("Num_Elementos_Nao_Nulos,Tempo_Medio_Multiplicacao_Segundos\n");

    // Limite reduzido para evitar OOM Killer se a RAM for < 8GB
    for(int n = 100; n <= 500; n += 100) {
        double tempo_acumulado = 0;
        int repeticoes = 3;

        for(int r = 0; r < repeticoes; r++) {
            Dado *entradas = gerar_dados_esparsos(n, densidade, &tamanho_vetor);
            p_matrizes A = criar_matrizes(n, n, INICIAL);
            for (int k = 0; k < tamanho_vetor; k++) 
                inserir_atualizar_matrizes(A, entradas[k].i, entradas[k].j, entradas[k].valor);

            // MEDIÇÃO: A * A
            int qtd_teste = 1; // Poucas repetições pois é pesado
            clock_t inicio = clock();
            for(int t=0; t < qtd_teste; t++) {
                p_matrizes C = atualiza_multiplicacao_matrizes(A, A);
                
                // IMPORTANTE: Liberar resultado imediatamente
                destruir_matrizes_hash(C);
            }
            clock_t fim = clock();

            double tempo_batch = (double)(fim - inicio) / CLOCKS_PER_SEC;
            tempo_acumulado += tempo_batch / qtd_teste;

            destruir_matrizes_hash(A);
            free(entradas);
        }
        int num_elementos = (int)(n * n * (densidade / 100.0));
        printf("%d,%.10f\n", num_elementos, tempo_acumulado / repeticoes);
    }
    return 0;
}