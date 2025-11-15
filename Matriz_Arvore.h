typedef Entrada *p_entrada;
typedef Matriz_Arvore *p_matriz_arvore;
typedef Avl *p_avl;

typedef struct Entrada
{
    int i;           // linha
    int j;           // coluna
    int valor;       // entrada não
    p_entrada left;  // filho a esquerda
    p_entrada right; // filho a direita
} Entrada;

typedef struct Avl
{
    p_entrada raiz;
} Avl;

typedef struct Matriz_Arvore
{
    p_entrada *lista;
} Matriz_Arvore;

// insere em log(k)
void inserir_avl(p_avl arvore, p_entrada entrada);

// acessa elemento em log(k)
int buscar_entrada(p_avl arvore, int j);
