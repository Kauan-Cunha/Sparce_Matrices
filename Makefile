# Define o compilador e as flags
CC = gcc
# O -I aponta para 'source/' para resolver os includes (ex: #include "hash/Hash.h")
CFLAGS = -Wall -Wextra -g -Isource

# Diretório para os Arquivos Objeto (.o) e Executáveis
OBJ_DIR = bin

# Nomes dos Executáveis (localizados dentro de bin/)
EXEC_AVL = $(OBJ_DIR)/teste_avl
EXEC_HASH = $(OBJ_DIR)/teste_hash

# Fontes (Caminhos a partir do diretório raiz)
SRCS_AVL = source/main_avl.c source/arvore/Matriz_Arvore.c
SRCS_HASH = source/main_hash.c source/hash/Hash.c

# 1. Nomes dos Objetos sem caminho (ex: main_avl.o, Matriz_Arvore.o)
OBJ_NAMES_AVL = $(notdir $(SRCS_AVL:.c=.o))
OBJ_NAMES_HASH = $(notdir $(SRCS_HASH:.c=.o))

# 2. Objetos Finais (ex: bin/main_avl.o, bin/Matriz_Arvore.o)
OBJS_AVL = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES_AVL))
OBJS_HASH = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES_HASH))

# ----------------------------------------------------------------------
# Regras de Compilação
# ----------------------------------------------------------------------

# Regra para o Executável AVL
# Verifica/Cria bin antes de compilar o executável
$(EXEC_AVL): $(OBJS_AVL)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para o Executável HASH
# Verifica/Cria bin antes de compilar o executável
$(EXEC_HASH): $(OBJS_HASH)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra Genérica: Transforma .c em .o dentro de bin/
# Verifica/Cria bin antes de compilar cada objeto
$(OBJ_DIR)/%.o:
	@mkdir -p $(OBJ_DIR)
	@# Busca dinâmica: Encontra o .c correspondente em source/ pelo nome
	@SOURCE_C_FILE=$$(find source/ -name '$*.c' -print -quit); \
	$(CC) $(CFLAGS) -c "$$SOURCE_C_FILE" -o $@

# ----------------------------------------------------------------------
# Comandos de Execução
# ----------------------------------------------------------------------

# Atalho para rodar a implementação AVL
run_avl: $(EXEC_AVL)
	./$(EXEC_AVL)

# Atalho para rodar a implementação HASH
run_hash: $(EXEC_HASH)
	./$(EXEC_HASH)

# ----------------------------------------------------------------------
# Regras de Utilidade (Limpeza)
# ----------------------------------------------------------------------

# Limpeza: remove o diretório bin/ inteiro
clean:
	rm -rf $(OBJ_DIR)

all: $(EXEC_AVL) $(EXEC_HASH)