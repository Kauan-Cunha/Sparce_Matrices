typedef entrada *p_entrada; 
typedef matrix_a *matrix_a;
typedef avl *a

typedef struct Entrada
{
    int i;          //linha
    int j;          //coluna
    int valor;      //entrada não 
    p_entrada left; //filho a esquerda
    p_entrada right;//filho a direita
}entrada;

typedef struct Avl
{
    p_entrada raiz;
}avl;

typedef struct Matrix_Arvore
{
    p_entrada *lista;
} matrix_a;

void inserir_avl()