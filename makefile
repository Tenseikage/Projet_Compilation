CC := gcc
CFLAGS := -Wall -g
LDFLAGS := -lfl -ly
BIN := ./bin
BUILD := ./build
SRC := ./src
INC := ./inc
OBJ := ./obj
BISON := parser
LEX := lex
TREE := tree
ARGS := args
OUTPUT := tpcas

# Cible par défaut
all: $(BIN) $(OBJ) $(BIN)/$(OUTPUT)

# Cible pour l'exécutable final
$(BIN)/$(OUTPUT): $(OBJ)/$(TREE).o $(OBJ)/$(BISON).tab.o $(OBJ)/$(LEX).yy.o $(OBJ)/$(ARGS).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation du fichier tree
$(OBJ)/$(TREE).o: $(SRC)/$(TREE).c $(SRC)/$(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier args
$(OBJ)/$(ARGS).o: $(SRC)/$(ARGS).c $(SRC)/$(ARGS).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation des fichiers générés par Bison
$(OBJ)/$(BISON).tab.o: $(SRC)/$(BISON).tab.c $(SRC)/$(BISON).tab.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation des fichiers générés par Lex
$(OBJ)/$(LEX).yy.o: $(SRC)/$(LEX).yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Nettoyage des fichiers générés
clean:
	rm -rf $(OBJ)/*.o $(BIN)/$(OUTPUT)