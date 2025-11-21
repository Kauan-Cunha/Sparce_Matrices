#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "source/hash/Hash.h"

#define MAX_K 200000
#define PASSO_K 5000
#define LOTE_TESTE 2000

/**
 *  Escolhe uma coordenada aleatória para i e j
 * 
 */
void gerar_coordenada(int N, int *i, int *j, int *val) {
    *i = rand() % N;                
    *j = rand() % N;
    *val = (rand() % 100) + 1;
}

/**
 * 
 * 
 */
int main() {
    srand(42);
    int N = 2000;

    printf("K,Tempo_100_Insercoes\n");

    for (int k_atual = PASSO_K; k_atual <= MAX_K; k_atual += PASSO_K) {
        
        // Hash dimensionada para não fazer rehash durante o teste
        p_matriz_esparsa H = criar_matriz(N, N, k_atual + LOTE_TESTE + 1000);

        // 1. AQUECIMENTO
        for (int i = 0; i < k_atual; i++) {
            int r, c, v;
            gerar_coordenada(N, &r, &c, &v);
            inserir_atualizar(H, r, c, v);
        }

        // 2. LOTE
        int *lote_i = malloc(LOTE_TESTE * sizeof(int));
        int *lote_j = malloc(LOTE_TESTE * sizeof(int));
        int *lote_v = malloc(LOTE_TESTE * sizeof(int));

        for(int i=0; i<LOTE_TESTE; i++) {
            gerar_coordenada(N, &lote_i[i], &lote_j[i], &lote_v[i]);
        }

        // 3. MEDIÇÃO
        clock_t inicio = clock();
        for (int i = 0; i < LOTE_TESTE; i++) {
            inserir_atualizar(H, lote_i[i], lote_j[i], lote_v[i]);
        }
        clock_t fim = clock();
        
        double tempo_normalizado = ((double)(fim - inicio) / CLOCKS_PER_SEC) / (LOTE_TESTE / 100.0);

        printf("%d,%.8f\n", k_atual, tempo_normalizado);

        free(lote_i); free(lote_j); free(lote_v);
        // free(H);
    }

    return 0;
}