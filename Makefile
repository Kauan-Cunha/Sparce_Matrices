# Define o compilador e as flags
CC = gcc
# O -I agora aponta para 'source/' para resolver os includes (ex: #include "hash/Hash.h")
CFLAGS = -Wall -Wextra -g -Isource

# Nomes dos Executáveis
EXEC_AVL = teste_avl
EXEC_HASH = teste_hash

# Diretório para os Arquivos Objeto (.o)
OBJ_DIR = bin

# Fontes (Caminhos a partir do diretório raiz)
SRCS_AVL = source/main_avl.c source/arvore/Matriz_Arvore.c
SRCS_HASH = source/main_hash.c source/hash/Hash.c

# Objetos (Mapeia as fontes para o diretório bin/)
# Ex: source/main_avl.c -> bin/source/main_avl.o
OBJS_AVL = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_AVL))
OBJS_HASH = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_HASH))

# ----------------------------------------------------------------------
# Regras de Compilação
# ----------------------------------------------------------------------

# Regra Principal (compila tudo)
all: $(EXEC_AVL) $(EXEC_HASH)

# Regra para o Executável AVL
$(EXEC_AVL): $(OBJS_AVL)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para o Executável HASH
$(EXEC_HASH): $(OBJS_HASH)
	$(CC) $(CFLAGS) -o $@ $^

# Regra Genérica para transformar .c em .o no diretório $(OBJ_DIR)
$(OBJ_DIR)/%.o: %.c
	# Cria o subdiretório dentro de bin/ se ele não existir (ex: bin/source/)
	@mkdir -p $(@D) 
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------
# Regras de Limpeza e Execução
# ----------------------------------------------------------------------

# Limpeza: remove executáveis e o diretório bin/ inteiro
clean:
	rm -f $(EXEC_AVL) $(EXEC_HASH)
	rm -rf $(OBJ_DIR)

# Atalho para rodar a implementação AVL (main_avl.c)
run_avl: $(EXEC_AVL)
	./$(EXEC_AVL)

# Atalho para rodar a implementação HASH (main_hash.c)
run_hash: $(EXEC_HASH)
	./$(EXEC_HASH)

# Atalho para rodar ambas as implementações
run_all: $(EXEC_AVL) $(EXEC_HASH)
	@echo "================================="
	@echo "--- Executando Teste AVL (Arvores) ---"
	@echo "================================="
	./$(EXEC_AVL)
	@echo "================================="
	@echo "--- Executando Teste HASH (Tabela Hash) ---"
	@echo "================================="
	./$(EXEC_HASH)
	@echo "================================="