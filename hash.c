#include "stdlib.h"
#include "Hash.h"

p_matriz_esparsa criar_matriz(int n, int m, int tamanho)
{
    p_matriz_esparsa nova_matriz = malloc(sizeof(struct Matriz_esparsa));
    nova_matriz->n = n;
    nova_matriz->m = m;
    nova_matriz->tabela_hash = malloc(tamanho * sizeof(p_no_hash));

    for (int i = 0; i < tamanho; i++)
        nova_matriz->tabela_hash[i] = NULL;

    return nova_matriz;
}

int chave_hash(int i, int j)
{
    return i * 61 + j * 97;
}

int acessar(p_matriz_esparsa A, int i, int j)
{
    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave];

    while (atual)
    {
        if (atual->i == i && atual->j == j)
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
    p_no_hash atual = A->tabela_hash[chave];

    while (atual)
    {
        if (atual->i == i && atual->j == j)
        {
            atual->valor = valor;
            return;
        }
        atual = atual->prox;
    }

    p_no_hash novo_no = malloc(sizeof(struct No_hash));
    novo_no->i = i;
    novo_no->j = j;
    novo_no->valor = valor;
    novo_no->prox = A->tabela_hash[chave];
    A->tabela_hash[chave] = novo_no;
}

void somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    for (int i = 0; i < A->tamanho; ++i)
    {
        p_no_hash atual = A->tabela_hash[i];
    }
}

void multiplicar_por_escalar(p_matriz_esparsa A, int alpha)
{
    for (int i = 0; i < A->tamanho; ++i)
    {
        p_no_hash atual = A->tabela_hash[i];

        while (atual)
        {
            atual->valor *= alpha;
            atual = atual->prox;
        }
    }
}
