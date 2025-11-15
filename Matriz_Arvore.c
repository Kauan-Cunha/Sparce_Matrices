#include "Matriz_Arvore.h"
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(p_avl no)
{
    if (no == NULL)
        return 0;
    return no->alt;
}

void atualiza_altura(p_avl no)
{
    if (no != NULL)
    {
        no->alt = 1 + max(altura(no->esq), altura(no->dir));
    }
}

int f_balanceamento(p_avl no)
{
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

p_avl rotacao_direita(p_avl y)
{
    p_avl x = y->esq;
    p_avl aux = x->dir;

    //rotaciona
    x->dir = y;
    y->esq = aux;

    //atualiza a altura
    atualiza_altura(y);
    atualiza_altura(x);

    return x;
}

p_avl rotacao_esquerda(p_avl x)
{
    p_avl y = x->dir;
    p_avl aux = y->esq;

    //rotaciona
    y->esq = x;
    x->dir = aux;

    //atualiza a matriz
    atualiza_altura(x);
    atualiza_altura(y);

    return y;
}

p_avl inserir_avl(p_avl raiz, p_avl nova_entrada)
{
    if (raiz == NULL)
    {
        nova_entrada->esq = NULL;
        nova_entrada->dir = NULL;
        nova_entrada->alt = 1;
        return nova_entrada;
    }

    if (nova_entrada->j < raiz->j)
    {
        raiz->esq = inserir_avl(raiz->esq, nova_entrada);
    }
    else if (nova_entrada->j > raiz->j)
    {
        raiz->dir = inserir_avl(raiz->dir, nova_entrada);
    }
    else
    {
        raiz->valor = nova_entrada->valor;
        return raiz;
    }

    atualiza_altura(raiz);

    int fb = f_balanceamento(raiz);

    if (fb > 1 && nova_entrada->j < raiz->esq->j)
    {
        return rotacao_direita(raiz);
    }

    if (fb < -1 && nova_entrada->j > raiz->dir->j)
    {
        return rotacao_esquerda(raiz);
    }

    if (fb > 1 && nova_entrada->j > raiz->esq->j)
    {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && nova_entrada->j < raiz->dir->j)
    {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

int buscar_entrada(p_avl arvore, int j)
{
    if (arvore->j == j)
    {
        return arvore->j;
    }
    else if (arvore->j < j)
    {
        return buscar_entrada(arvore->dir, j);
    }
    return buscar_entrada(arvore->esq, j);
}