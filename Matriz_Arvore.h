typedef AVL_Linha *p_avl_linha;
typedef AVL_Coluna *p_avl_coluna;

typedef struct
{
    int i;            // linha
    p_avl_coluna col; // AVL da coluna
    p_avl_linha esq;  // filho a esquerda
    p_avl_linha dir;  // filho a direita
} AVL_Linha;

typedef struct
{
    int j;            // coluna
    int valor;        // entrada não nula
    p_avl_coluna esq; // filho a esquerda
    p_avl_coluna dir; // filho a direita
} AVL_Coluna;

// typedef struct Matriz_Arvore
// {
//     p_avl_linha raiz;
// } Matriz_Arvore;

p_avl_linha criar_matriz_arvore();

// insere em log(k)
void inserir_avl(p_avl_linha raiz, p_avl_coluna entrada);

// acessa elemento em log(k)
int buscar_entrada(p_avl_linha arvore, int j);
