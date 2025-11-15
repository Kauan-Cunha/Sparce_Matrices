#include "Matriz_Arvore.h"

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