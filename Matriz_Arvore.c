#include "Matriz_Arvore.h"
#include <stdlib.h>

int max()

int altura(p_avl Arv){
    if (Arv == NULL){
        return 0;
    }
    return Arv->alt
}

int f_balanceamento(p_avl Arv){
    if (Arv == NULL){
        return 0;
    }
    return altura(Arv->left) - altura(Arv->right);
}



void inserir_avl(p_avl raiz, p_avl entrada){
    return;
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