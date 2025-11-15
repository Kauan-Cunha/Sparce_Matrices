typedef struct entrada
{
    int i;      //linha
    int j;      //coluna
    int valor;  //entrada não nula
}entrada;

typedef struct Matrix_Arvore
{
    int **lista;
} matrix_a;

typedef entrada *p_entrada; 
typedef matrix_a *matrix_a;