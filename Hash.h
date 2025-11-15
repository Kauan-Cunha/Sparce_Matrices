typedef struct No_hash *p_no_hash;
typedef struct Matriz_esparsa *p_matriz_esparsa;

struct No_hash
{
    int i, j;       // posição
    int valor;      // valor não nulo
    p_no_hash prox; // ponteiro para o próximo nó em caso de colisão
};

struct Matriz_esparsa
{
    int n, m;               // dimensões da matriz
    int tamanho;            // tamanho da tabela hash
    p_no_hash *tabela_hash; // vetor de ponteiros
    p_no_hash *linhas;      // vetor de linhas
};

p_matriz_esparsa criar_matriz(int n, int m, int tamanho);

long int chave_hash(int i, int j);

int acessar(p_matriz_esparsa A, int i, int j);

void inserir_atualizar(p_matriz_esparsa A, int i, int j, int valor);

p_matriz_esparsa somar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B);

void multiplicar_por_escalar(p_matriz_esparsa A, int alpha);

p_matriz_esparsa multiplicar_matrizes(p_matriz_esparsa A, p_matriz_esparsa B);