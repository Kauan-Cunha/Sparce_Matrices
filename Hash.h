#define MAX 2003 // bom tamanho de hash para k = 1000

#include <stdlib.h>
#include "stdio.h"

typedef struct No_hash *p_no_hash;
typedef struct Matriz_esparsa *p_matriz_esparsa;
typedef struct Matrizes *p_matrizes;

struct No_hash
{
    int i, j;            // posição
    int valor;           // valor não nulo
    p_no_hash prox_hash; // ponteiro para o próximo nó em caso de colisão
    p_no_hash prox_linha;
};

struct Matriz_esparsa
{
    int n, m;               // dimensões da matriz
    int tamanho;            // tamanho da tabela hash
    p_no_hash *tabela_hash; // vetor de ponteiros
    p_no_hash *linhas;      // vetor de linhas
};

struct Matrizes
{
    p_matriz_esparsa normal;
    p_matriz_esparsa transposta;
};

//////////////////////////////////// HASH //////////////////////////////////////
long int chave_hash(int i, int j);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////// ACESSAR /////////////////////////////////////
int acessar(p_matriz_esparsa A, int i, int j);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////// CRIAR MATRIZES //////////////////////////////////
p_matriz_esparsa criar_matriz(int n, int m, int tamanho);
p_matrizes criar_matrizes(int n, int m, int tamanho);
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////// INSERÇÃO //////////////////////////////////////
void inserir_atualizar(p_matriz_esparsa A, int i, int j, int valor);
void inserir_atualizar_matrizes(p_matrizes matrizes, int i, int j, int valor);
////////////////////////////////////////////////////////////////////////////////

///////////////////////////// SOMAR MATRIZES ///////////////////////////////////
p_matriz_esparsa somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B);
p_matrizes atualiza_soma_matrizes(p_matrizes matrizesA, p_matrizes matrizesB);
////////////////////////////////////////////////////////////////////////////////

/////////////////////// MULTIPLICAÇÃO POR ESCALAR //////////////////////////////
void multiplicar_por_escalar(p_matriz_esparsa A, int alpha);
void multiplicar_por_escalar_matrizes(p_matrizes matrizes, int alpha);
////////////////////////////////////////////////////////////////////////////////

/////////////////////// MULTIPLICAÇÃO DE MATRIZES //////////////////////////////
p_matriz_esparsa multiplicar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B);
p_matrizes atualiza_multiplicacao_matrizes(p_matrizes matrizesA, p_matrizes matrizesB);
////////////////////////////////////////////////////////////////////////////////
