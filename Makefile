# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Arquivos Objetos
OBJ_ARVORE = Matriz_Arvore.o
OBJ_HASH = Hash.o

# Executáveis a serem gerados
TARGETS = main_hash main_avl

# --- Regra Principal (compila tudo) ---
all: $(TARGETS)


# --- Regra para 'main_hash' (Teste Hash) ---
main_hash: main_hash.o $(OBJ_HASH)
	$(CC) $(CFLAGS) -o main_hash main_hash.o $(OBJ_HASH)

# --- Regra para 'main_avl' (Teste avl O(1)) ---
main_avl: main_avl.o $(OBJ_ARVORE)
	$(CC) $(CFLAGS) -o main_avl main_avl.o $(OBJ_ARVORE)

# --- Compilação dos Objetos (.o) ---

# Matriz Arvore
Matriz_Arvore.o: Matriz_Arvore.c Matriz_Arvore.h
	$(CC) $(CFLAGS) -c Matriz_Arvore.c

# Hash
Hash.o: Hash.c Hash.h
	$(CC) $(CFLAGS) -c Hash.c

# Mains
main.o: main.c Matriz_Arvore.h
	$(CC) $(CFLAGS) -c main.c

main_hash.o: main_hash.c Hash.h
	$(CC) $(CFLAGS) -c main_hash.c

main_avl.o: main_avl.c Matriz_Arvore.h
	$(CC) $(CFLAGS) -c main_avl.c

# --- Limpeza ---
clean:
	rm -f *.o $(TARGETS)

run_avl: main_avl
	./main_avl

run_hash: main_hash
	./main_avl