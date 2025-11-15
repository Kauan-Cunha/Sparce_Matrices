#include "Matriz_Arvore.h"
<<<<<<< HEAD
#include <stdlib.h>

int altura(p_avl Arv){
    if (Arv == NULL){
        return 0;
    }
    return 
}

void inserir_avl(p_avl raiz, p_avl entrada){
    
=======

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
>>>>>>> b9c3c575ccf4ce6128f147b60c90d414c56ce729
}