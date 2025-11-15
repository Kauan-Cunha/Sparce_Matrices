#include <stdlib.h>
#include "Matriz_Arvore.h"
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(p_avl_coluna no)
{
    if (no == NULL)
        return 0;
    return no->alt;
}

void atualiza_altura(p_avl_coluna no)
{
    if (no != NULL)
    {
        no->alt = 1 + max(altura(no->esq), altura(no->dir));
    }
}

int f_balanceamento(p_avl_coluna no)
{
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

p_avl_coluna rotacao_direita(p_avl_coluna y)
{
    p_avl_coluna x = y->esq;
    p_avl_coluna aux = x->dir;

    //rotaciona
    x->dir = y;
    y->esq = aux;

    //atualiza a altura
    atualiza_altura(y);
    atualiza_altura(x);

    return x;
}

p_avl_coluna rotacao_esquerda(p_avl_coluna x)
{
    p_avl_coluna y = x->dir;
    p_avl_coluna aux = y->esq;

    //rotaciona
    y->esq = x;
    x->dir = aux;

    //atualiza a matriz
    atualiza_altura(x);
    atualiza_altura(y);

    return y;
}

p_avl_coluna inserir_avl(p_avl_coluna raiz, p_avl_coluna nova_entrada)
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

int buscar_entrada(p_avl_linha arvore, int j)
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

p_avl_linha criar_matriz_arvore()
{
    p_avl_linha a = malloc(sizeof(AVL_Linha));
    a->j = -1;
    a->col = NULL;
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

p_avl_linha copiar(p_avl_linha a)
{
    p_avl_linha b = criar_matriz_arvore();
}

int somar(p_avl_linha a, p_avl_linha b)
{
    p_avl_linha c = criar_matriz_arvore();
}