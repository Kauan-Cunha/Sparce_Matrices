#include "Hash.h"

p_matriz_esparsa criar_matriz(int n, int m, int tamanho)
{
    p_matriz_esparsa A = malloc(sizeof(struct Matriz_esparsa)); // aloca espaço
    A->n = n;
    A->m = m;
    A->tamanho = tamanho;

    A->tabela_hash = calloc(tamanho, sizeof(p_no_hash)); // aloca espaço e inicializa com NULL
    A->linhas = calloc(n, sizeof(p_no_hash));            // aloca espaço e inicaliza com NULL

    return A;
}

p_matrizes criar_matrizes(int n, int m, int tamanho)
{
    p_matrizes matrizes = malloc(sizeof(struct Matrizes));
    matrizes->normal = criar_matriz(n, m, tamanho);
    matrizes->transposta = criar_matriz(m, n, tamanho);
    return matrizes;
}

long int chave_hash(int i, int j)
{
    return i * 10007 + j * 50021; // função hash utilizando primos de magnitude intermediária
}

int acessar(p_matriz_esparsa A, int i, int j)
{
    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave]; // acessa o nó atual através do hash em tempo esperado O(1)

    while (atual)
    {
        if (atual->i == i && atual->j == j) // percorre a lista ligada se tiver conflito
            return atual->valor;

        atual = atual->prox_hash;
    }

    return 0;
}

void inserir_atualizar(p_matriz_esparsa A, int i, int j, int valor)
{
    if (valor == 0)
        return;

    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave]; // acessa o nó atual através do hash em tempo esperado O(1)

    while (atual)
    {
        if (atual->i == i && atual->j == j)
        {
            atual->valor = valor; // atualiza
            return;
        }
        atual = atual->prox_hash;
    }

    p_no_hash novo_no = malloc(sizeof(struct No_hash));
    novo_no->i = i;
    novo_no->j = j;
    novo_no->valor = valor;
    novo_no->prox_hash = A->tabela_hash[chave];
    A->tabela_hash[chave] = novo_no; // insere na tabela hash

    novo_no->prox_linha = A->linhas[i]; // insere nas linhas da tabela hash
    A->linhas[i] = novo_no;
}

void inserir_atualizar_matrizes(p_matrizes matrizes, int i, int j, int valor)
{
    inserir_atualizar(matrizes->normal, i, j, valor);
    inserir_atualizar(matrizes->transposta, j, i, valor);
}

p_matriz_esparsa somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    p_matriz_esparsa C = criar_matriz(A->n, A->m, A->tamanho); // cria matriz C

    /* Insere os valores da matriz A em C*/
    for (int a = 0; a < A->tamanho; ++a)
    {
        p_no_hash atual = A->tabela_hash[a];

        while (atual)
        {
            int i = atual->i;
            int j = atual->j;
            int valor = atual->valor;

            inserir_atualizar(C, i, j, valor);
            atual = atual->prox_hash;
        }
    }

    /* Soma os valores da matriz B com os valores existentes da matriz C*/
    for (int a = 0; a < B->tamanho; ++a)
    {
        p_no_hash atual = B->tabela_hash[a];

        while (atual)
        {
            int i = atual->i;
            int j = atual->j;
            int valor = atual->valor + acessar(C, i, j);

            inserir_atualizar(C, i, j, valor);
            atual = atual->prox_hash;
        }
    }

    return C;
}

p_matrizes atualiza_soma_matrizes(p_matrizes matrizesA, p_matrizes matrizesB)
{
    p_matrizes C = criar_matrizes(matrizesA->normal->n, matrizesA->normal->m, matrizesA->normal->tamanho);
    C->normal = somar_matrizes(matrizesA->normal, matrizesB->normal);
    C->transposta = somar_matrizes(matrizesA->transposta, matrizesB->transposta);
    return C;
}

void multiplicar_por_escalar(p_matriz_esparsa A, int alpha)
{
    for (int a = 0; a < A->tamanho; ++a)
    {
        p_no_hash atual = A->tabela_hash[a];

        while (atual)
        {
            atual->valor *= alpha; // multiplica os valores da matriz A por um escalar
            atual = atual->prox_hash;
        }
    }
}

void multiplicar_por_escalar_matrizes(p_matrizes matrizes, int alpha)
{
    multiplicar_por_escalar(matrizes->normal, alpha);
    multiplicar_por_escalar(matrizes->transposta, alpha);
}

p_matriz_esparsa multiplicar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    p_matriz_esparsa C = criar_matriz(A->n, B->m, A->tamanho);

    for (int a = 0; a < A->tamanho; ++a)
    {
        p_no_hash atual = A->tabela_hash[a];

        while (atual)
        {
            int i = atual->i;
            int k = atual->j;
            int Aik = atual->valor;

            p_no_hash aux = B->linhas[k];

            while (aux)
            {
                int j = aux->j;
                int Bkj = aux->valor;

                int valor = Aik * Bkj + acessar(C, i, j);
                inserir_atualizar(C, i, j, valor);
                aux = aux->prox_linha;
            }
            atual = atual->prox_hash;
        }
    }
    return C;
}

p_matrizes atualiza_multiplicacao_matrizes(p_matrizes matrizesA, p_matrizes matrizesB)
{
    p_matrizes C = criar_matrizes(matrizesA->normal->n, matrizesA->normal->m, matrizesA->normal->tamanho);
    C->normal = multiplicar_matrizes(matrizesA->normal, matrizesB->normal);
    C->transposta = multiplicar_matrizes(matrizesB->transposta, matrizesA->transposta);
    return C;
}
