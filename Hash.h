typedef struct
{
    int i;                  // linha
    int j;                  // coluna
    int valor;              // valor não nulo
    struct No_hash *prox;   // ponteiro para o próximo nó em caso de colisão
} No_hash;

typedef struct {
    int n, m;               // dimensões da matriz
    int trasposta;          // flag
    int tamanho;            // tamanho da tabela hash
    No_hash **hash;         // vetor de ponteiros

} Matriz_esparsa;