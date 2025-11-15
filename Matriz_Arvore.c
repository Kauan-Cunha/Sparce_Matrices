#include <stdlib.h>
#include "Matriz_Arvore.h"
#include <stdlib.h>

p_avl_linha criar_matriz_arvore()
{
    p_avl_linha a = malloc(sizeof(AVL_Linha));
    a->j = -1;
    a->col = NULL;
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

/*
FUNÇÕES PARA AVL COLUNA
*/
int altura_col(p_avl_coluna no)
{
    if (no == NULL)
    return 0;
    return no->alt;
}

void atualiza_altura_col(p_avl_coluna no)
{
    if (no != NULL)
    {
        no->alt = 1 + max(altura_col(no->esq), altura_col(no->dir));
    }
}

int f_balanceamento_col(p_avl_coluna no)
{
    if (no == NULL)
    return 0;
    return altura_col(no->esq) - altura_col(no->dir);
}

p_avl_coluna rotacao_direita_col(p_avl_coluna y)
{
    p_avl_coluna x = y->esq;
    p_avl_coluna aux = x->dir;
    
    //rotaciona
    x->dir = y;
    y->esq = aux;
    
    //atualiza a altura
    atualiza_altura_col(y);
    atualiza_altura_col(x);
    
    return x;
}

p_avl_coluna rotacao_esquerda_col(p_avl_coluna x)
{
    p_avl_coluna y = x->dir;
    p_avl_coluna aux = y->esq;
    
    //rotaciona
    y->esq = x;
    x->dir = aux;
    
    //atualiza a matriz
    atualiza_altura_col(x);
    atualiza_altura_col(y);
    
    return y;
}

p_avl_coluna inserir_avl_coluna(p_avl_coluna raiz, p_avl_coluna nova_entrada)
{
    //caso base
    if (raiz == NULL)
    {
        nova_entrada->alt = 1; // Altura de folha
        nova_entrada->esq = NULL;
        nova_entrada->dir = NULL;
        return nova_entrada;
    }
    //busca onde inserir
    if (nova_entrada->j < raiz->j)
    {
        raiz->esq = inserir_avl_coluna(raiz->esq, nova_entrada);
    }
    else if (nova_entrada->j > raiz->j)
    {
        raiz->dir = inserir_avl_coluna(raiz->dir, nova_entrada);
    }
    else
    {
        raiz->valor = nova_entrada->valor;
        return raiz;
    }
    
    //balanceia
    atualiza_altura_col(raiz);
    
    int fb = f_balanceamento_col(raiz);
    
    if (fb > 1 && nova_entrada->j < raiz->esq->j)
    {
        return rotacao_direita_col(raiz);
    }
    
    if (fb < -1 && nova_entrada->j > raiz->dir->j)
    {
        return rotacao_esquerda_col(raiz);
    }
    
    if (fb > 1 && nova_entrada->j > raiz->esq->j)
    {
        raiz->esq = rotacao_esquerda_col(raiz->esq);
        return rotacao_direita_col(raiz);
    }
    
    if (fb < -1 && nova_entrada->j < raiz->dir->j)
    {
        raiz->dir = rotacao_direita_col(raiz->dir);
        return rotacao_esquerda_col(raiz);
    }
    
    return raiz;
}

/*-------------------------------------
FUNÇÕES AVL DA LINHA
--------------------------------------*/
int altura_lin(p_avl_linha no)
{
    if (no == NULL)
        return 0;
    return no->alt;
}

void atualiza_altura_lin(p_avl_linha no)
{
    if (no != NULL)
    {
        no->alt = 1 + max(altura_lin(no->esq), altura_lin(no->dir));
    }
}

int f_balanceamento_lin(p_avl_linha no)
{
    if (no == NULL)
        return 0;
    return altura_lin(no->esq) - altura_lin(no->dir);
}

p_avl_linha rotacao_direita_lin(p_avl_linha y)
{
    p_avl_linha x = y->esq;
    p_avl_linha aux = x->dir;

    x->dir = y;
    y->esq = aux;

    atualiza_altura_lin(y);
    atualiza_altura_lin(x);

    return x;
}

p_avl_linha rotacao_esquerda_lin(p_avl_linha x)
{
    p_avl_linha y = x->dir;
    p_avl_linha aux = y->esq;

    y->esq = x;
    x->dir = aux;

    atualiza_altura_lin(x);
    atualiza_altura_lin(y);

    return y;
}

p_avl_linha inserir_avl_linha(p_avl_linha raiz, p_avl_linha nova_entrada)
{
    // caso base
    if (raiz == NULL)
    {
        nova_entrada->alt = 1;
        nova_entrada->esq = NULL;
        nova_entrada->dir = NULL;
        // nova_entrada->col já deve estar definido (provavelmente NULL)
        return nova_entrada;
    }

    //busca onde inserir
    if (nova_entrada->i < raiz->i)
    {
        raiz->esq = inserir_avl_linha(raiz->esq, nova_entrada);
    }
    else if (nova_entrada->i > raiz->i)
    {
        raiz->dir = inserir_avl_linha(raiz->dir, nova_entrada);
    }
    else
    {
        return raiz;
    }
    
    //balanceia 
    atualiza_altura_lin(raiz);
    
    int fb = f_balanceamento_lin(raiz);
    
    if (fb > 1 && nova_entrada->i < raiz->esq->i)
    {
        return rotacao_direita_lin(raiz);
    }
    
    if (fb < -1 && nova_entrada->i > raiz->dir->i)
    {
        return rotacao_esquerda_lin(raiz);
    }
    
    if (fb > 1 && nova_entrada->i > raiz->esq->i)
    {
        raiz->esq = rotacao_esquerda_lin(raiz->esq);
        return rotacao_direita_lin(raiz);
    }
    
    if (fb < -1 && nova_entrada->i < raiz->dir->i)
    {
        raiz->dir = rotacao_direita_lin(raiz->dir);
        return rotacao_esquerda_lin(raiz);
    }
    
    return raiz;
}

p_avl_linha buscar_entrada_linhas(p_avl_linha arvore, int i)
{
    if (arvore == NULL)
    {
        return NULL;
    }
    
    if (arvore->i == i)
    {
        return arvore;
    }
    else if (arvore->i < i)
    {
        return buscar_entrada_linhas(arvore->dir, i);
    }
    
    return buscar_entrada_linhas(arvore->esq, i);
}

p_avl_coluna buscar_entrada_colunas(p_avl_coluna arvore, int j)
{
    if (arvore == NULL)
    {
        return NULL;
    }
    
    if (arvore->j == j)
    {
        return arvore;
    }
    else if (arvore->j < j)
    {
        return buscar_entrada_colunas(arvore->dir, j);
    }
    
    return buscar_entrada_colunas(arvore->esq, j);
}

int acessar_elemento(int i, int j, p_avl_linha raiz_linhas)
{
    p_avl_linha no_linha = buscar_entrada_linhas(raiz_linhas, i);
    
    if (no_linha == NULL)
    {
        return 0;
    }
    
    p_avl_coluna elemento = buscar_entrada_colunas(no_linha->col, j);

    if (elemento == NULL)
    {
        return 0;
    }

    return elemento->valor;
}

p_avl_linha inserir_elemento(int valor, int i, int j, p_avl_linha raiz_linhas)
{
    p_avl_linha no_linha = buscar_entrada_linhas(raiz_linhas, i);
    
    if (no_linha == NULL)
    {
        p_avl_linha nova_linha = calloc(1, sizeof(AVL_Linha));
        nova_linha->i = i;
        nova_linha->col = NULL; 
        
        raiz_linhas = inserir_avl_linha(raiz_linhas, nova_linha);
        
        no_linha = buscar_entrada_linhas(raiz_linhas, i);
    }
    
    if (no_linha != NULL) 
    {
        p_avl_coluna novo_elemento = calloc(1, sizeof(AVL_Coluna));
        novo_elemento->j = j;
        novo_elemento->valor = valor;

        no_linha->col = inserir_avl_coluna(no_linha->col, novo_elemento);
    }
    
    return raiz_linhas;
}

p_avl_linha copiar(p_avl_linha a)
{
    p_avl_linha b = criar_matriz_arvore();
}

int somar(p_avl_linha a, p_avl_linha b)
{
    p_avl_linha c = criar_matriz_arvore();
}