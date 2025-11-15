#include <stdlib.h>
#include "Matriz_Arvore.h"

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