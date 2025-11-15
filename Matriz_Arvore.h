typedef Matriz_Arvore *p_matriz_arvore;
typedef Avl *p_avl;

typedef struct
{
<<<<<<< HEAD
    int i, j;        // posição
    int valor;       // entrada não nula
    int alt;
    p_entrada left;  // filho a esquerda
    p_entrada right; // filho a direita
} Entrada;

typedef struct Avl
{
    p_entrada raiz;
=======
    int i, j;  // posição
    int valor; // entrada não nula
    p_avl esq; // filho a esquerda
    p_avl dir; // filho a direita
>>>>>>> b9c3c575ccf4ce6128f147b60c90d414c56ce729
} Avl;

typedef struct Matriz_Arvore
{
    p_avl *lista;
} Matriz_Arvore;

// insere em log(k)
void inserir_avl(p_avl raiz, p_avl entrada);

// acessa elemento em log(k)
int buscar_entrada(p_avl arvore, int j);
