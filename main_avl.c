#include <stdio.h>
#include <stdlib.h>
#include "Matriz_Arvore.h"

/*
    Função auxiliar para imprimir usando o container e acesso O(1)
*/
void imprimir_container(p_matriz_arvore M, const char *nome, int n)
{
    printf("--- %s ---\n", nome);
    if (M == NULL) {
        printf(" (Nulo)\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("[");
        for (int j = 0; j < n; j++)
        {
            // Usa a função de acesso do container
            printf("%3d ", acessar_matriz(M, i, j));
        }
        printf("]\n");
    }
    printf("----------------\n\n");
}

int main()
{
    int N = 4;
    printf("=== TESTE DO CONTAINER (MATRIZ + TRANSPOSTA) ===\n\n");

    // 1. Criação
    p_matriz_arvore A = criar_matriz();
    
    // 2. Inserção (Deve inserir em A e na Transposta de A internamente)
    // Matriz A:
    // 1  2  0  0
    // 0  5  0  0
    // 0  0  0  9
    // 4  0  0  0
    inserir_matriz(A, 0, 0, 1);
    inserir_matriz(A, 0, 1, 2);
    inserir_matriz(A, 1, 1, 5);
    inserir_matriz(A, 2, 3, 9);
    inserir_matriz(A, 3, 0, 4);

    imprimir_container(A, "Matriz A (Container)", N);

    // 3. Teste da Transposta O(1)
    // A função transposta(A) deve retornar um container onde 
    // a 'matriz' principal é a transposta de A.
    printf(">>> Testando Transposta O(1) <<<\n");
    p_matriz_arvore A_T = transposta(A);
    
    // Se funcionar, A_T deve imprimir:
    // 1  0  0  4
    // 2  5  0  0
    // 0  0  0  0
    // 0  0  9  0
    imprimir_container(A_T, "Transposta de A (O(1))", N);

    // 4. Multiplicação de Matrizes (Container)
    // Vamos criar B
    // 1  0  0  0
    // 0  0  2  0
    // ...
    p_matriz_arvore B = criar_matriz();
    inserir_matriz(B, 0, 0, 1);
    inserir_matriz(B, 1, 2, 2);
    
    imprimir_container(B, "Matriz B", N);

    // C = A * B
    printf(">>> Testando Multiplicacao (Container) <<<\n");
    p_matriz_arvore C = multiplicacao_matriz(A, B);
    imprimir_container(C, "C = A * B", N);

    // Verificar se a transposta de C foi calculada corretamente internamente
    // C_T deve ser igual a (A*B)^T = B^T * A^T
    p_matriz_arvore C_T = transposta(C);
    imprimir_container(C_T, "Transposta de C (Interna)", N);

    // 5. Multiplicação por Escalar
    printf(">>> Testando Escalar (Container) <<<\n");
    // Multiplica B por 10ainer.c

    escalar(10, B); 
    imprimir_container(B, "B * 10", N);
    
    // Verifica se a transposta interna de B também foi atualizada
    p_matriz_arvore B_T = transposta(B);
    imprimir_container(B_T, "Transposta de B (Apos Escalar)", N);

    // Limpeza (assumindo que não há free implementado ainda, deixamos ao SO)
    return 0;
}