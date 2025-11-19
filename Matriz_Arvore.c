#include <stdlib.h>
#include "Matriz_Arvore.h"
#include "Matriz_Arvore.h"
#include <stdlib.h>

p_avl_linha criar_linha()
{
    p_avl_linha a = malloc(sizeof(AVL_Linha));
    a->col = NULL;
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

/*
    Inicializa a matriz. Isso é a avl_linha para matriz e sua transposta.
 */
p_matriz_arvore criar_matriz(){
    p_matriz_arvore a = malloc(sizeof(Matriz_Arvore));

    a->matriz = criar_linha();
    a->transposta = criar_linha();

    return a;
}

/* 
    Inserir na matriz e na transposta. Invertendo apenas o indice dos elementos
*/
void inserir_matriz(p_matriz_arvore matriz, int i, int j, int valor){
    matriz->matriz = inserir_elemento(valor, i, j, matriz->matriz);

    matriz->transposta = inserir_elemento(valor, j, i, matriz->transposta);

    return;
}

/*
    Acessar Matriz atraves de um índice
*/
int acessar_matriz(p_matriz_arvore matriz, int i, int j){
    return acessar_elemento(i, j, matriz->matriz);
}

/*
    Realiza a função entre duas matrizes(container) e retorna uma matriz C (container)
*/
p_matriz_arvore multiplicacao_matriz(p_matriz_arvore A, p_matriz_arvore B){
    p_matriz_arvore C = criar_matriz();
    
    C->matriz = multiplicacao_matrizes(A->matriz, B->matriz);
    C->transposta = multiplicacao_matrizes(B->transposta, B->transposta);

    return C;
}

/*
    Retorna Transposta
 */
p_matriz_arvore transposta(p_matriz_arvore matriz){
    p_matriz_arvore transp = criar_matriz();
    transp->matriz = matriz->transposta;
    transp->transposta = matriz->matriz;

    return transp;
}

/*
    multiplica matriz por escalar
*/
void escalar(int escalar, p_matriz_arvore matriz){
    //zera todas as entradas e, portanto, não armazena nenhuma entrada
    if(escalar == 0){
        matriz->matriz = NULL;
        matriz->transposta = NULL;
        return;
    }

    mult_escalar(matriz->matriz, escalar);
    mult_escalar(matriz->transposta, escalar);
}

/*
    Retona a matriz resultado da soma de A e B
*/
p_matriz_arvore soma_matrizes(p_matriz_arvore A, p_matriz_arvore B){
    p_matriz_arvore C = criar_matriz();

    C->matriz = somar(A->matriz, B->matriz);
    C->transposta = somar(A->transposta, B->transposta);

    return C;
}

/*
    Retorna o maior inteiro entre 2.
*/
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

    // rotaciona
    x->dir = y;
    y->esq = aux;

    // atualiza a altura
    atualiza_altura_col(y);
    atualiza_altura_col(x);

    return x;
}

p_avl_coluna rotacao_esquerda_col(p_avl_coluna x)
{
    p_avl_coluna y = x->dir;
    p_avl_coluna aux = y->esq;

    // rotaciona
    y->esq = x;
    x->dir = aux;

    // atualiza a matriz
    atualiza_altura_col(x);
    atualiza_altura_col(y);

    return y;
}

p_avl_coluna inserir_avl_coluna(p_avl_coluna raiz, p_avl_coluna nova_entrada)
{
    if (raiz == NULL)
    {
        nova_entrada->alt = 1; // Altura de folha
        nova_entrada->esq = NULL;
        nova_entrada->dir = NULL;
        return nova_entrada;
    }
    // busca onde inserir
    if (nova_entrada->j < raiz->j)          // se maior, procura na arvore filha a direita.
    {
        raiz->esq = inserir_avl_coluna(raiz->esq, nova_entrada);    
    }
    else if (nova_entrada->j > raiz->j)
    {
        raiz->dir = inserir_avl_coluna(raiz->dir, nova_entrada); //se menor, procura na arvore filha a esquerda.
    }
    else
    {
        raiz->valor = nova_entrada->valor;          // se igual, significa que já existe um elemento onde queremos adicionar, então basta atualizar seu valor.
        return raiz;
    }

    // balanceia
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

    // busca onde inserir
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

    // balanceia
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

    else 
    {
        p_avl_coluna novo_elemento = calloc(1, sizeof(AVL_Coluna));
        novo_elemento->j = j;
        novo_elemento->valor = valor;

        no_linha->col = inserir_avl_coluna(no_linha->col, novo_elemento);
    }

    return raiz_linhas;
}

p_avl_coluna copiar_coluna(p_avl_coluna col)
{
    if (col == NULL)
    {
        return NULL;
    }

    p_avl_coluna copia = malloc(sizeof(AVL_Coluna));
    copia->j = col->j;
    copia->alt = col->alt;
    copia->valor = col->valor;
    copia->esq = copiar_coluna(col->esq);
    copia->dir = copiar_coluna(col->dir);

    return copia;
}

p_avl_linha copiar(p_avl_linha a)
{
    if (a == NULL)
    {
        return NULL;
    }

    p_avl_linha b = criar_linha();

    b->i = a->i;
    b->alt = a->alt;
    b->col = copiar_coluna(a->col);
    b->esq = copiar(a->esq);
    b->dir = copiar(a->dir);

    return b;
}

void mult_escalar_coluna(p_avl_coluna col, int alpha)
{
    if (col == NULL)
    {
        return;
    }

    col->valor *= alpha;
    mult_escalar_coluna(col->esq, alpha);
    mult_escalar_coluna(col->dir, alpha);
}

void mult_escalar(p_avl_linha a, int alpha)
{
    if (a == NULL)
    {
        return;
    }

    mult_escalar_coluna(a->col, alpha);
    mult_escalar(a->esq, alpha);
    mult_escalar(a->dir, alpha);

}

p_avl_linha somar_colunas(p_avl_coluna col_b, int i, p_avl_linha c)
{
    if (col_b == NULL)
    {
        return c;
    }

    c = somar_colunas(col_b->esq, i, c);

    int j = col_b->j;
    int valor_a = acessar_elemento(i, j, c);
    int valor_b = col_b->valor;

    c = inserir_elemento(valor_a + valor_b, i, j, c);
    c = somar_colunas(col_b->dir, i, c);
    return c;
}

p_avl_linha somar_linhas(p_avl_linha b, p_avl_linha c)
{
    if (b == NULL)
    {
        return c;
    }

    c = somar_linhas(b->esq, c);
    c = somar_colunas(b->col, b->i, c);
    c = somar_linhas(b->dir, c);

    return c;
}

p_avl_linha somar(p_avl_linha a, p_avl_linha b)
{
    p_avl_linha c = copiar(a);
    c = somar_linhas(b, c);
    return c;
}

void iterar_colunas_B_e_atualizar_C(p_avl_coluna no_B_col, p_avl_linha *p_C, int i_A, int val_A)             
{
    if (no_B_col == NULL)
    {
        return;
    }

    iterar_colunas_B_e_atualizar_C(no_B_col->esq, p_C, i_A, val_A);

    // Processa o nó B_lj atual
    int j_B = no_B_col->j;
    int val_B = no_B_col->valor;

    int produto = val_A * val_B;

    if (produto != 0)
    {
        // Acumula o produto em C[i_A][j_B]
        int val_atual_C = acessar_elemento(i_A, j_B, *p_C);

        // A função inserir_elemento retorna a nova raiz (caso haja rotação)
        // Por isso, precisamos atualizar a raiz C através do ponteiro *p_C
        *p_C = inserir_elemento(val_atual_C + produto, i_A, j_B, *p_C);
    }

    iterar_colunas_B_e_atualizar_C(no_B_col->dir, p_C, i_A, val_A);
}

// Esta função itera sobre as colunas da linha 'i' de A (os A_il)
void iterar_colunas_A(p_avl_coluna no_A_col, p_avl_linha B, p_avl_linha *p_C, int i_A)               
{
    if (no_A_col == NULL)
    {
        return;
    }

    // Travessia in-order
    iterar_colunas_A(no_A_col->esq, B, p_C, i_A);

    // Processa o nó A_il atual
    int l_A = no_A_col->j; // O 'j' da AVL_Coluna de A é o índice 'l'
    int val_A = no_A_col->valor;

    // Para este A_il, precisamos encontrar a linha 'l' (que é l_A) em B
    p_avl_linha no_linha_B = buscar_entrada_linhas(B, l_A);

    if (no_linha_B != NULL)
    {
        // Se a linha 'l' de B existe, itere sobre suas colunas (os B_lj)
        iterar_colunas_B_e_atualizar_C(no_linha_B->col, p_C, i_A, val_A);
    }

    iterar_colunas_A(no_A_col->dir, B, p_C, i_A);
}

// Esta função itera sobre as linhas 'i' de A
void iterar_linhas_A(p_avl_linha no_A_lin, // Nó atual da linha de A
                     p_avl_linha B,        // Raiz da matriz B
                     p_avl_linha *p_C)     // Ponteiro para a raiz de C
{
    if (no_A_lin == NULL)
    {
        return;
    }

    // Travessia in-order
    iterar_linhas_A(no_A_lin->esq, B, p_C);

    // Processa o nó da linha 'i' de A
    int i_A = no_A_lin->i;
    // Itera sobre todas as colunas (A_il) desta linha 'i'
    iterar_colunas_A(no_A_lin->col, B, p_C, i_A);

    iterar_linhas_A(no_A_lin->dir, B, p_C);
}

p_avl_linha multiplicacao_matrizes(p_avl_linha A, p_avl_linha B)
{
    p_avl_linha C = NULL;

    iterar_linhas_A(A, B, &C);

    return C;
}
