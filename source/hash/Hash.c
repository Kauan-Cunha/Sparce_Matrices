#include "Hash.h"

p_matriz_esparsa criar_matriz(int n, int m, int tamanho)
{
    p_matriz_esparsa A = malloc(sizeof(struct Matriz_esparsa)); // aloca espaço
    A->n = n;
    A->m = m;
    A->tamanho = tamanho;
    A->usados = 0;
    A->lista_todos = NULL;                               // inicializa a lista encadeada
    A->tabela_hash = calloc(tamanho, sizeof(p_no_hash)); // aloca espaço e inicializa com NULL
    return A;
}

p_matrizes criar_matrizes(int n, int m, int tamanho)
{
    p_matrizes matrizes = malloc(sizeof(struct Matrizes));
    matrizes->normal = criar_matriz(n, m, tamanho);     // cria A normal
    matrizes->transposta = criar_matriz(m, n, tamanho); // cria A transposta
    return matrizes;
}

unsigned long long chave_hash(int i, int j)
{
    // funcao hash baseada em MurmurHash3
    unsigned long long key = ((unsigned long long)i << 32) | (unsigned long long)j;

    const unsigned long long C1 = 0xff51afd7ed558ccdULL;
    const unsigned long long C2 = 0xc4ceb9fe1a85ec53ULL;

    key ^= key >> 33;
    key *= C1;
    key ^= key >> 33;
    key *= C2;
    key ^= key >> 33;

    return key;
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

void rehash(p_matriz_esparsa A)
{
    int novo_tamanho = A->tamanho * 2 + 1; // gera novo tamanho para a tabela
    p_no_hash *novo_hash = calloc(novo_tamanho, sizeof(p_no_hash));

    p_no_hash atual = A->lista_todos;
    while (atual)
    {
        int chave = chave_hash(atual->i, atual->j) % novo_tamanho;
        atual->prox_hash = novo_hash[chave];
        novo_hash[chave] = atual;
        atual = atual->prox_todos; // percorre na lista com todos os nós
    }

    free(A->tabela_hash);       // libera a tabela antiga
    A->tabela_hash = novo_hash; // atualiza
    A->tamanho = novo_tamanho;  // atualiza
}

void inserir_atualizar(p_matriz_esparsa A, int i, int j, int valor)
{
    if (valor == 0) // se o valor é 0 nao faz nada
        return;

    int chave = chave_hash(i, j) % A->tamanho;
    p_no_hash atual = A->tabela_hash[chave]; // acessa o nó atual através do hash em auxo esperado O(1)

    while (atual)
    {
        if (atual->i == i && atual->j == j)
        {
            atual->valor = valor; // atualiza
            return;
        }
        atual = atual->prox_hash;
    }

    // cria novo no
    p_no_hash novo_no = malloc(sizeof(struct No_hash));
    novo_no->i = i;
    novo_no->j = j;
    novo_no->valor = valor;
    novo_no->prox_hash = A->tabela_hash[chave];
    A->tabela_hash[chave] = novo_no; // insere na tabela hash

    novo_no->prox_todos = A->lista_todos; // insere na lista de todos
    A->lista_todos = novo_no;

    A->usados++;

    if ((double)A->usados / A->tamanho > FATOR_CARGA) // checa se precisa de rehash
        rehash(A);
}

void inserir_atualizar_matrizes(p_matrizes matrizes, int i, int j, int valor)
{
    inserir_atualizar(matrizes->normal, i, j, valor);     // O(1) esperado
    inserir_atualizar(matrizes->transposta, j, i, valor); // O(1) esperado
}

p_matriz_esparsa somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B)
{
    // O(ka + kb esperao)
    p_matriz_esparsa C = criar_matriz(A->n, A->m, A->tamanho); // cria matriz C

    // percorre todos os elementos nao nulos de A
    p_no_hash x = A->lista_todos;
    while (x)
    {
        inserir_atualizar(C, x->i, x->j, x->valor);
        x = x->prox_todos;
    }

    // percorre todos os elementos nao nulos de B
    p_no_hash y = B->lista_todos;
    while (y)
    {
        int novo_valor = acessar(C, y->i, y->j) + y->valor;
        inserir_atualizar(C, y->i, y->j, novo_valor);
        y = y->prox_todos;
    }

    return C;
}

p_matrizes atualiza_soma_matrizes(p_matrizes matrizesA, p_matrizes matrizesB)
{
    p_matrizes C = malloc(sizeof(struct Matrizes));
    C->normal = somar_matrizes(matrizesA->normal, matrizesB->normal);
    C->transposta = somar_matrizes(matrizesA->transposta, matrizesB->transposta);
    return C;
}

void multiplicar_por_escalar(p_matriz_esparsa A, int alpha)
{
    if (alpha == 0)
    {
        // destroi lista existente
        p_no_hash atual = A->lista_todos;
        while (atual)
        {
            p_no_hash aux = atual;
            atual = atual->prox_todos;
            free(aux);
        }

        A->lista_todos = NULL;
        A->usados = 0;
        A->tamanho = INICIAL;

        // limpa tabela
        for (int k = 0; k < A->tamanho; k++)
            A->tabela_hash[k] = NULL;

        return;
    }

    // multiplica cada nó existente por alpha
    p_no_hash x = A->lista_todos;
    while (x)
    {
        x->valor *= alpha;
        x = x->prox_todos;
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

    // percorre os elementos de A
    p_no_hash a = A->lista_todos;
    while (a)
    {
        int i = a->i;
        int k = a->j;
        int Aik = a->valor;

        p_no_hash b = B->lista_todos;
        while (b)
        // percorre os elementos de B
        {
            if (b->i == k)
            {
                // Cij += Aik + Bkj
                int j = b->j;
                int valor = acessar(C, i, j) + Aik * b->valor;
                inserir_atualizar(C, i, j, valor);

                // vai pro proximo elemento nao nulo de B
                b = b->prox_todos;
            }
            // vai pro proximo elemento nao nulo de A
            a = a->prox_todos;
        }
    }
    return C;
}

p_matrizes atualiza_multiplicacao_matrizes(p_matrizes matrizesA, p_matrizes matrizesB)
{
    p_matrizes C = malloc(sizeof(struct Matrizes));
    C->normal = multiplicar_matrizes(matrizesA->normal, matrizesB->normal);
    C->transposta = multiplicar_matrizes(matrizesB->transposta, matrizesA->transposta);
    return C;
}
