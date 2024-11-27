CC := gcc
CFLAGS := -Wall 
LDFLAGS := -lfl -ly
BIN := ./bin
BUILD := ./build
SRC := ./src
INC := ./inc
OBJ := ./obj
BISON := parser
LEX := lex
TREE := tree
OUTPUT := tpcas

# Cible par défaut
all: $(BIN) $(OBJ) $(BIN)/$(OUTPUT)

# Cible pour l'exécutable final
$(BIN)/$(OUTPUT): $(OBJ)/$(TREE).o $(OBJ)/$(BISON).tab.o $(OBJ)/$(LEX).yy.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation du fichier tree
./obj/tree.o: ./src/tree.c ./inc/tree.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Génération des fichiers Bison
$(SRC)/$(BISON).tab.c $(INC)/$(BISON).tab.h: $(SRC)/$(BISON).y
	bison -d -Wcounterexamples -o $(SRC)/$(BISON).tab.c $<

# Compilation du fichier Bison
$(OBJ)/$(BISON).tab.o: $(SRC)/$(BISON).tab.c $(INC)/$(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier Flex
$(OBJ)/$(LEX).yy.o: $(SRC)/$(LEX).yy.c $(INC)/$(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Génération du fichier Flex
$(SRC)/$(LEX).yy.c: $(SRC)/$(LEX).l $(INC)/$(BISON).tab.h
	flex -o $@ $<

# Nettoyage
clean:
	rm -f $(BIN)/$(OUTPUT) $(OBJ)/*.o $(SRC)/*.tab.c $(SRC)/*.tab.h $(SRC)/*.yy.c
