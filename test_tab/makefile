CC := gcc
CFLAGS := -Wall 
LDFLAGS := -lfl
BIN := ./bin
SRC := ./src
INC := ./inc
OBJ := ./obj
BISON := parser
LEX := lex
OUTPUT := tpcas


# Cible pour l'exécutable final
$(BIN)/$(OUTPUT): $(OBJ)/$(BISON).tab.o $(OBJ)/$(LEX).yy.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Génération des fichiers Bison
$(SRC)/$(BISON).tab.c $(SRC)/$(BISON).tab.h: $(SRC)/$(BISON).y
	bison -d -o $(SRC)/$(BISON).tab.c $<

# Compilation du fichier Bison
$(OBJ)/$(BISON).tab.o: $(SRC)/$(BISON).tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier Flex
$(OBJ)/$(LEX).yy.o: $(SRC)/$(LEX).yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Génération du fichier Flex
$(SRC)/$(LEX).yy.c: $(SRC)/$(LEX).l $(SRC)/$(BISON).tab.h
	flex -o $@ $<

# Nettoyage
clean:
	rm -f $(BIN)/$(OUTPUT) $(OBJ)/*.o $(SRC)/*.tab.c $(SRC)/*.tab.h $(SRC)/*.yy.c
