#include <stdio.h>
#include <stdlib.h>
#include "Matriz_Arvore.h"

/*
=================================================================
 FUNÇÃO DE IMPRESSÃO (Formato Matriz Padrão)
=================================================================
 Esta função imprime a matriz no formato NxM, testando
 exaustivamente a sua função 'acessar_elemento'.
*/
void imprimir_matriz_padrao(p_avl_linha M, const char *nome, int linhas, int colunas)
{
    printf("--- Matriz %s (%dx%d) ---\n", nome, linhas, colunas);

    for (int i = 0; i < linhas; i++)
    {
        printf("[");
        for (int j = 0; j < colunas; j++)
        {
            // Acessa CADA elemento, seja ele zero ou não
            int valor = acessar_elemento(i, j, M);
            
            // Imprime com 3 espaços para alinhar
            printf("%3d", valor); 
            
            if (j < colunas - 1) {
                printf(" "); // Um pequeno espaço entre os números
            }
        }
        printf(" ]\n");
    }
    printf("--------------------------------\n\n");
}


/*
=================================================================
 FUNÇÃO MAIN (Testes)
=================================================================
*/
int main()
{
    // Define o tamanho das matrizes
    const int N = 4;

    // 1. Inicializa as matrizes como ÁRVORES VAZIAS
    p_avl_linha A = NULL;
    p_avl_linha B = NULL;
    p_avl_linha C_copia = NULL;
    p_avl_linha S_soma = NULL;
    p_avl_linha M_mult = NULL;

    printf("================================\n");
    printf("  TESTE DE INSERÇÃO E ACESSO\n");
    printf("================================\n\n");

    // Vamos criar a Matriz A (Esparsa)
    // A = [  0   7   0   0 ]
    //     [  0   0   1   0 ]
    //     [  2   0   0   0 ]
    //     [  0   0   0   4 ]
    A = inserir_elemento(7, 0, 1, A);
    A = inserir_elemento(2, 3, 2, A);
    A = inserir_elemento(1, 1, 2, A);
    A = inserir_elemento(2, 2, 0, A);
    A = inserir_elemento(4, 3, 3, A);

    // Vamos criar a Matriz B (Esparsa)
    // B = [  1   0   0   0 ]
    //     [  0   0   3   0 ]
    //     [  0   0   0   0 ] (linha 2 de B é nula)
    //     [  5   0  -1   0 ]
    B = inserir_elemento(1, 0, 0, B);
    B = inserir_elemento(3, 1, 2, B);
    B = inserir_elemento(5, 3, 0, B);
    B = inserir_elemento(-1, 3, 2, B);
    
    // Teste 1: Imprimir A e B usando a nova função
    imprimir_matriz_padrao(A, "A", N, N);
    imprimir_matriz_padrao(B, "B", N, N);

    /*
    =================================================================
     TESTE DE CÓPIA (copiar)
    =================================================================
    */
    printf("================================\n");
    printf("       TESTE DE CÓPIA\n");
    printf("================================\n\n");
    
    C_copia = copiar(A);

    // Para provar que é uma cópia profunda (deep copy),
    // vamos modificar C e mostrar que A não muda.
    C_copia = inserir_elemento(99, 0, 0, C_copia);
    
    printf("--- Modificando C_copia[0][0] para 99 ---\n");
    imprimir_matriz_padrao(C_copia, "C (Cópia de A, Modificada)", N, N);
    
    imprimir_matriz_padrao(A, "A (Original, Inalterada)", N, N);


    /*
    =================================================================
     TESTE DE SOMA (somar)
    =================================================================
    */
    printf("================================\n");
    printf("        TESTE DE SOMA\n");
    printf("================================\n\n");
    
    // Resultado Esperado (S = A + B):
    // S = [  1   7   3   0 ]
    //     [  0   0   1   0 ]
    //     [  2   0   0   0 ]
    //     [  5   0  -1   4 ]
    S_soma = somar(A, B);
    imprimir_matriz_padrao(S_soma, "S = A + B", N, N);


    /*
    =================================================================
     TESTE DE MULTIPLICAÇÃO (multiplicacao_matrizes)
    =================================================================
    */
    printf("================================\n");
    printf("    TESTE DE MULTIPLICAÇÃO\n");
    printf("================================\n\n");

    // Resultado Esperado (M = A * B):
    // M[0,2] = A[0,1]*B[1,2] = 7 * 3 = 21
    // M[1,2] = A[1,2]*B[2,2] = 1 * 0 = 0 (Não entra na matriz)
    // M[2,0] = A[2,0]*B[0,0] = 2 * 1 = 2
    // M[3,0] = A[3,3]*B[3,0] = 4 * 5 = 20
    // M[3,2] = A[3,3]*B[3,2] = 4 * -1 = -4
    //
    // M = [  0   0  21   0 ]
    //     [  0   0   0   0 ]
    //     [  2   0   0   0 ]
    //     [ 20   0  -4   0 ]
    M_mult = multiplicacao_matrizes(A, B);
    imprimir_matriz_padrao(M_mult, "M = A * B", N, N);


    // NOTA: Você deve implementar funções 'destruir_matriz'
    // para liberar toda a memória alocada (calloc/malloc).
    // destruir_matriz(A);
    // destruir_matriz(B);
    // destruir_matriz(C_copia);
    // destruir_matriz(S_soma);
    // destruir_matriz(M_mult);

    return 0;
}