#include "stdlib.h"
#include "Hash.h"

p_matriz_esparsa criar_matriz(int n, int m, int tamanho)
{
    p_matriz_esparsa A = malloc(sizeof(struct Matriz_esparsa)); // aloca espaço
    A->n = n;
    A->m = m;
    A->tamanho;

    A->tabela_hash = calloc(tamanho, sizeof(p_no_hash)); // aloca espaço e inicializa com NULL
    A->linhas = calloc(n, sizeof(p_no_hash));            // aloca espaço e inicaliza com NULL

    return A;
}

long int chave_hash(int i, int j)
{
    return i * 10007 + j * 50021; // função hash utilizando primos intermediários
}

int acessar(p_matriz_esparsa A, int i, int j)
{
    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave]; // acessa o nó atual através do hash em tempo esperado O(1)

    while (atual)
    {
        if (atual->i == i && atual->j == j) // percorre a lista ligada se tiver conflito
            return atual->valor;

        atual = atual->prox;
    }

    return 0;
}

void inserir_atualizar(p_matriz_esparsa A, int i, int j, int valor)
{
    if (valor == 0)
        return;

    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave]; // acessa o nó atual através do hash em tempo esperado O(1)

    while (atual)
    {
        if (atual->i == i && atual->j == j)
        {
            atual->valor = valor; // atualiza
            return;
        }
        atual = atual->prox;
    }

    p_no_hash novo_no = malloc(sizeof(struct No_hash));
    novo_no->i = i;
    novo_no->j = j;
    novo_no->valor = valor;
    novo_no->prox = A->tabela_hash[chave];
    A->tabela_hash[chave] = novo_no; // insere na tabela hash

    novo_no->prox = A->linhas[i];
    A->linhas[i] = novo_no;
}

p_matriz_esparsa somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    p_matriz_esparsa C = criar_matriz(A->n, A->m, A->tamanho); // cria matriz C

    /* Insere os valores da matriz A em C*/
    for (int k = 0; k < A->tamanho; ++k)
    {
        p_no_hash atual = A->tabela_hash[k];

        while (atual)
        {
            int i = atual->i;
            int j = atual->j;
            int valor = atual->valor;

            inserir_atualizar(C, i, j, valor);
            atual = atual->prox;
        }
    }

    /* Soma os valores da matriz B com os valores existentes da matriz C*/
    for (int k = 0; k < B->tamanho; ++k)
    {
        p_no_hash atual = B->tabela_hash[k];

        while (atual)
        {
            int i = atual->i;
            int j = atual->j;
            int valor = atual->valor + acessar(C, i, j);

            inserir_atualizar(C, i, j, valor);
            atual = atual->prox;
        }
    }

    return C;
}

void multiplicar_por_escalar(p_matriz_esparsa A, int alpha)
{
    for (int i = 0; i < A->tamanho; ++i)
    {
        p_no_hash atual = A->tabela_hash[i];

        while (atual)
        {
            atual->valor *= alpha; // multiplica os valores da matriz A por um escalar
            atual = atual->prox;
        }
    }
}

p_matriz_esparsa multiplicar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    p_matriz_esparsa C = criar_matriz(A->n, A->m, A->tamanho);

    for (int k = 0; k < A->tamanho; ++k)
    {
        p_no_hash atual = A->tabela_hash[k];

        while (atual)
        {
            int i = atual->i;
            int k = atual->j;
            int Aik = atual->valor;

            p_no_hash aux = B->linhas[k];

            while (aux) {
                int j = aux->j;
                int Bkj = aux->valor;

                int valor = Aik * Bkj + acessar(C, i, j);
                inserir_atualizar(C, i, j, valor);
                aux = aux->prox; 
            }
        }
        atual = atual->prox;
    }

    return C;
}
