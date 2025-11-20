#include <stdio.h>
#include <stdlib.h>
#include "Hash.h" // Inclui as definições da sua ESTRUTURA HASH

// Vamos usá-lo como o tamanho da tabela hash.
#define TAMANHO_HASH INICIAL

/*
=================================================================
 FUNÇÃO DE IMPRESSÃO (Formato Matriz Padrão)
=================================================================
 Esta função imprime a matriz no formato NxM, testando
 exaustivamente a sua função 'acessar'.
*/
void imprimir_matriz_padrao(p_matriz_esparsa M, const char *nome, int linhas, int colunas)
{
    printf("--- Matriz %s (%dx%d) ---\n", nome, linhas, colunas);

    for (int i = 0; i < linhas; i++)
    {
        printf("[");
        for (int j = 0; j < colunas; j++)
        {
            // Acessa CADA elemento, seja ele zero ou não
            // Chama a função 'acessar' do hash.c
            int valor = acessar(M, i, j); 
            
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
 FUNÇÃO AUXILIAR DE CÓPIA (Não fornecida no hash.c)
=================================================================
 A lógica abaixo foi baseada na sua função 'somar_matrizes',
 que primeiro copia A para C antes de somar B.
*/
p_matriz_esparsa copiar_matriz(p_matriz_esparsa A)
{
    // 1. Cria a nova matriz C
    p_matriz_esparsa C = criar_matriz(A->n, A->m, A->tamanho);

    // 2. Itera sobre toda a tabela hash de A
    for (int a = 0; a < A->tamanho; ++a)
    {
        p_no_hash atual = A->tabela_hash[a];

        // 3. Itera sobre a lista de colisão
        while (atual)
        {
            // 4. Insere o elemento de A em C
            inserir_atualizar(C, atual->i, atual->j, atual->valor);
            atual = atual->prox_hash;
        }
    }
    return C;
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

    // 1. Inicializa as matrizes usando 'criar_matriz'
    p_matriz_esparsa A = criar_matriz(N, N, TAMANHO_HASH);
    p_matriz_esparsa B = criar_matriz(N, N, TAMANHO_HASH);
    p_matriz_esparsa C_copia = NULL;
    p_matriz_esparsa S_soma = NULL;
    p_matriz_esparsa M_mult = NULL;

    printf("================================\n");
    printf("  TESTE DE INSERÇÃO E ACESSO (Hash)\n");
    printf("================================\n\n");

    // Vamos criar a Matriz A (Esparsa)
    // A = [  0   7   0   0 ]
    //     [  0   0   1   0 ]
    //     [  2   0   0   0 ]
    //     [  0   0   0   4 ]
    // Usando a função 'inserir_atualizar'
    inserir_atualizar(A, 0, 1, 7);
    inserir_atualizar(A, 1, 2, 1);
    inserir_atualizar(A, 2, 0, 2);
    inserir_atualizar(A, 3, 3, 4);

    // Vamos criar a Matriz B (Esparsa)
    // B = [  1   0   0   0 ]
    //     [  0   0   3   0 ]
    //     [  0   0   0   0 ]
    //     [  5   0  -1   0 ]
    inserir_atualizar(B, 0, 0, 1);
    inserir_atualizar(B, 1, 2, 3);
    inserir_atualizar(B, 3, 0, 5);
    inserir_atualizar(B, 3, 2, -1);
    
    // Teste 1: Imprimir A e B
    imprimir_matriz_padrao(A, "A", N, N);
    imprimir_matriz_padrao(B, "B", N, N);

    /*
    =================================================================
     TESTE DE CÓPIA (copiar_matriz - auxiliar)
    =================================================================
    */
    printf("================================\n");
    printf("       TESTE DE CÓPIA (Hash)\n");
    printf("================================\n\n");
    
    C_copia = copiar_matriz(A);

    // Modifica a cópia para provar que A não muda
    inserir_atualizar(C_copia, 0, 0, 99);
    
    printf("--- Modificando C_copia[0][0] para 99 ---\n");
    imprimir_matriz_padrao(C_copia, "C (Cópia de A, Modificada)", N, N);
    
    imprimir_matriz_padrao(A, "A (Original, Inalterada)", N, N);


    /*
    =================================================================
     TESTE DE SOMA (somar_matrizes)
    =================================================================
    */
    printf("================================\n");
    printf("        TESTE DE SOMA (Hash)\n");
    printf("================================\n\n");
    
    // Resultado Esperado (S = A + B):
    // S = [  1   7   0   0 ]
    //     [  0   0   1   0 ]
    //     [  2   0   0   0 ]
    //     [  5   0  -1   4 ]
    S_soma = somar_matrizes(A, B); //
    imprimir_matriz_padrao(S_soma, "S = A + B", N, N);


    /*
    =================================================================
     TESTE DE MULTIPLICAÇÃO (multiplicar_matrizes)
    =================================================================
    */
    printf("================================\n");
    printf("    TESTE DE MULTIPLICAÇÃO (Hash)\n");
    printf("================================\n\n");

    // Resultado Esperado (M = A * B):
    // M = [  0   0  21   0 ]
    //     [  0   0   0   0 ]
    //     [  2   0   0   0 ]
    //     [ 20   0  -4   0 ]
    M_mult = multiplicar_matrizes(A, B); //
    imprimir_matriz_padrao(M_mult, "M = A * B", N, N);


    // NOTA: Você deve implementar funções 'destruir_matriz'
    // para liberar toda a memória alocada (calloc/malloc).
    // ...

    return 0;
}