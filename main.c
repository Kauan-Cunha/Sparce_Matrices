#include <stdio.h>
#include <stdlib.h>
#include "Matriz_Arvore.h" // Inclui as definições da sua estrutura

/* -------------------------------------------------
FUNÇÕES DE IMPRESSÃO (NÃO EXISTEM NO SEU .C)
-------------------------------------------------
Estas funções são essenciais para depurar e verificar
se as suas operações de matriz estão corretas.
*/

// Protótipos
void imprimir_matriz(p_avl_linha M, const char *nome);
void imprimir_linhas(p_avl_linha no_linha);
void imprimir_colunas(p_avl_coluna no_coluna);

/**
 * @brief Função principal para imprimir a matriz inteira.
 */
void imprimir_matriz(p_avl_linha M, const char *nome)
{
    printf("--- Matriz %s ---\n", nome);
    if (M == NULL)
    {
        printf(" (Matriz Vazia)\n");
    }
    else
    {
        imprimir_linhas(M);
    }
    printf("------------------\n");
}

/**
 * @brief Auxiliar recursiva para percorrer (em ordem) as linhas.
 */
void imprimir_linhas(p_avl_linha no_linha)
{
    if (no_linha == NULL)
    {
        return;
    }
    imprimir_linhas(no_linha->esq);

    // Processa a linha atual
    printf("  Linha %d: [ ", no_linha->i);
    imprimir_colunas(no_linha->col);
    printf("]\n");

    imprimir_linhas(no_linha->dir);
}

/**
 * @brief Auxiliar recursiva para percorrer (em ordem) as colunas de uma linha.
 */
void imprimir_colunas(p_avl_coluna no_coluna)
{
    if (no_coluna == NULL)
    {
        return;
    }
    imprimir_colunas(no_coluna->esq);

    // Processa a coluna atual
    printf("(j=%d, val=%d) ", no_coluna->j, no_coluna->valor);

    imprimir_colunas(no_coluna->dir);
}

/* -------------------------------------------------
FUNÇÃO MAIN
-------------------------------------------------
*/
int main()
{
    /*
     * ⚠️ IMPORTANTE:
     * Inicie matrizes vazias com NULL.
     * A sua função criar_matriz_arvore() está incorreta:
     * 1. Ela aloca memória desnecessariamente (a inserção AVL trata o NULL).
     * 2. Ela atribui `a->j = -1`, mas a struct AVL_Linha tem `i`, não `j`.
     *
     * A forma correta de criar uma matriz vazia é:
     */
    p_avl_linha A = NULL;
    p_avl_linha B = NULL;
    p_avl_linha C = NULL;

    printf("=== Teste de Inserção Matriz A ===\n");
    // Vamos criar a Matriz A:
    // A = [ 1 0 2 ]
    //     [ 0 3 0 ]
    A = inserir_elemento(1, 0, 0, A);
    A = inserir_elemento(2, 0, 2, A);
    A = inserir_elemento(3, 1, 1, A);
    imprimir_matriz(A, "A");

    printf("\n=== Teste de Inserção Matriz B ===\n");
    // Vamos criar a Matriz B:
    // B = [ 5 1 ]
    //     [ 0 0 ]
    //     [ 1 2 ]
    B = inserir_elemento(5, 0, 0, B);
    B = inserir_elemento(1, 0, 1, B);
    B = inserir_elemento(1, 2, 0, B);
    B = inserir_elemento(2, 2, 1, B);
    imprimir_matriz(B, "B");

    printf("\n=== Teste de Acesso ===\n");
    printf("Acessando A[0][0]: %d (Esperado: 1)\n", acessar_elemento(0, 0, A));
    printf("Acessando A[1][1]: %d (Esperado: 3)\n", acessar_elemento(1, 1, A));
    printf("Acessando A[1][0] (vazio): %d (Esperado: 0)\n", acessar_elemento(1, 0, A));
    printf("Acessando B[2][1]: %d (Esperado: 2)\n", acessar_elemento(2, 1, B));

    printf("\n=== Teste de Multiplicação C = A * B ===\n");
    // Cálculo esperado:
    // C[0][0] = (A[0][0]*B[0][0]) + (A[0][2]*B[2][0]) = (1*5) + (2*1) = 7
    // C[0][1] = (A[0][0]*B[0][1]) + (A[0][2]*B[2][1]) = (1*1) + (2*2) = 5
    // C[1][0] = (A[1][1]*B[1][0]) = (3*0) = 0
    // C[1][1] = (A[1][1]*B[1][1]) = (3*0) = 0
    //
    // Resultado C = [ 7 5 ]
    //             [ 0 0 ]
    C = multiplicacao_matrizes(A, B);
    imprimir_matriz(C, "C = A * B");

    printf("Acessando C[0][0]: %d (Esperado: 7)\n", acessar_elemento(0, 0, C));
    printf("Acessando C[0][1]: %d (Esperado: 5)\n", acessar_elemento(0, 1, C));
    printf("Acessando C[1][0] (vazio): %d (Esperado: 0)\n", acessar_elemento(1, 0, C));


    /*
    printf("\n--- Teste de Soma S = A + A2 ---\n");
    p_avl_linha A2 = NULL;
    A2 = inserir_elemento(1, 0, 1, A2);
    A2 = inserir_elemento(4, 1, 0, A2);
    imprimir_matriz(A2, "A2");

    // ⚠️ ATENÇÃO: A sua função 'somar' tem um BUG.
    // Em 'somar_colunas', a linha:
    //   c = inserir_elemento(valor_a, i, j, valor_a + valor_b);
    // Está com os argumentos errados. Deveria ser:
    //   c = inserir_elemento(valor_a + valor_b, i, j, c);
    //
    // O teste abaixo provavelmente irá falhar ou travar.
    // p_avl_linha S = somar(A, A2);
    // imprimir_matriz(S, "S = A + A2");
    */


    // Nota: Você também deve implementar funções "destruir_matriz"
    // para liberar toda a memória alocada (calloc/malloc).

    return 0;
}