typedef struct AVL_Linha AVL_Linha;
typedef struct AVL_Coluna AVL_Coluna;
typedef struct Matriz_Arvore Matriz_Arvore;


typedef AVL_Linha *p_avl_linha;
typedef AVL_Coluna *p_avl_coluna;
typedef Matriz_Arvore *p_matriz_arvore;

struct AVL_Linha
{
    int i;            // linha
    int alt;
    p_avl_coluna col; // AVL da coluna
    p_avl_linha esq;  // filho a esquerda
    p_avl_linha dir;  // filho a direita
};

struct AVL_Coluna
{
    int j;            // coluna
    int alt;
    int valor;        // entrada não nula
    p_avl_coluna esq; // filho a esquerda
    p_avl_coluna dir; // filho a direita
};

struct  Matriz_Arvore
{
    p_avl_linha matriz;
    p_avl_linha transposta;
};


// typedef struct Matriz_Arvore
// {
//     p_avl_linha raiz;
// } Matriz_Arvore;

/**
 * Funções para o contâiner de Matriz (usar ela como FrameWork)
 */
void inserir_matriz(p_matriz_arvore matriz, int i, int j, int valor);

int acessar_matriz(p_matriz_arvore matriz, int i, int j);

p_matriz_arvore transposta(p_matriz_arvore matriz);

p_matriz_arvore multiplicacao_matriz(p_matriz_arvore A, p_matriz_arvore B);


/**
 *  IMPLEMENTAM A AVL PARA COLUNAS
 */

// insere em log(k)
p_avl_coluna inserir_avl(p_avl_coluna raiz, p_avl_coluna nova_entrada);

// acessa elemento em log(k)
int buscar_entrada(p_avl_linha arvore, int j);

// retorna max entre 2 inteiros
int max(int a, int b);

// retorna a altua de uma arvore coluna
int altura_col(p_avl_coluna no);

// atualiza a altura dado um balanceamento
void atualiza_altura_col(p_avl_coluna no);

// balanceia a arvore coluna
int f_balanceamento_col(p_avl_coluna no);

// rotaciona avl coluna para direita
p_avl_coluna rotacao_direita_col(p_avl_coluna y);

// rotaciona avl coluna para esquerda
p_avl_coluna rotacao_esquerda_col(p_avl_coluna x);

// inseri elemento em avl coluna
p_avl_coluna inserir_avl_coluna(p_avl_coluna raiz, p_avl_coluna nova_entrada);

int altura_lin(p_avl_linha no);

// atualiza a altura avl linha 
void atualiza_altura_lin(p_avl_linha no);

int f_balanceamento_lin(p_avl_linha no);

p_avl_linha rotacao_direita_lin(p_avl_linha y);

p_avl_linha rotacao_esquerda_lin(p_avl_linha x);

p_avl_linha inserir_avl_linha(p_avl_linha raiz, p_avl_linha nova_entrada);

p_avl_linha buscar_entrada_linhas(p_avl_linha arvore, int i);

p_avl_coluna buscar_entrada_colunas(p_avl_coluna arvore, int j);

int acessar_elemento(int i, int j, p_avl_linha raiz_linhas);

p_avl_linha inserir_elemento(int valor, int i, int j, p_avl_linha raiz_linhas);

p_avl_coluna copiar_coluna(p_avl_coluna col);

p_avl_linha copiar(p_avl_linha a);

p_avl_linha somar_colunas(p_avl_coluna col_b, int i, p_avl_linha c);

p_avl_linha somar_linhas(p_avl_linha b, p_avl_linha c);

p_avl_linha somar(p_avl_linha a, p_avl_linha b);

void iterar_colunas_B_e_atualizar_C(p_avl_coluna no_B_col, p_avl_linha *p_C, int i_A, int val_A);

void iterar_colunas_A(p_avl_coluna no_A_col, p_avl_linha B, p_avl_linha *p_C, int i_A);

void iterar_linhas_A(p_avl_linha no_A_lin, p_avl_linha B, p_avl_linha *p_C);

p_avl_linha multiplicacao_matrizes(p_avl_linha A, p_avl_linha B);
