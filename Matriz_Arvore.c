#include <stdlib.h>
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