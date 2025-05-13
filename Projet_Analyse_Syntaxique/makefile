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
OUTPUT := tpcc
EXE := asmtest
AFLAGS := -nostartfiles -no-pie
EXE := asmtest
NASM := nasm
ASM_SRCS := $(wildcard $(SRC)/*.asm)
ASM_OBJS := $(patsubst $(SRC)/%.asm, $(OBJ)/%.o, $(ASM_SRCS))
TARGET := $(EXE)

.PHONY: all asm clean


# Cible par défaut
all: $(BIN) $(OBJ) $(BIN)/$(OUTPUT)

# Cible pour l'exécutable final
$(BIN)/$(OUTPUT): $(OBJ)/$(TREE).o $(OBJ)/$(BISON).tab.o $(OBJ)/$(LEX).yy.o $(OBJ)/$(ARGS).o $(OBJ)/main.o $(OBJ)/symb_tab.o $(OBJ)/semantics.o $(OBJ)/write_asmfile.o $(OBJ)/sem_errors_warns.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Génération des fichiers Bison
$(SRC)/$(BISON).tab.c $(SRC)/$(BISON).tab.h: $(SRC)/$(BISON).y
	bison -d -o $(SRC)/$(BISON).tab.c $<

# Compilation du fichier tree
$(OBJ)/$(TREE).o: $(SRC)/$(TREE).c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier args
$(OBJ)/$(ARGS).o: $(SRC)/$(ARGS).c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation des fichiers générés par Bison
$(OBJ)/$(BISON).tab.o: $(SRC)/$(BISON).tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier Flex
$(OBJ)/$(LEX).yy.o: $(SRC)/$(LEX).yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier main.c
$(OBJ)/main.o: $(SRC)/main.c #$(SRC)/write_asmfile.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation table des symboles
$(OBJ)/symb_tab.o: $(SRC)/symb_tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Compilation sémantique
$(OBJ)/semantics.o : $(SRC)/semantics.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Compilation erreurs sémantiques
$(OBJ)/sem_errors_warns.o : $(SRC)/sem_errors_warns.c
	$(CC) $(CFLAGS) -c -o $@ $<


# Compilation création fichier asm opérations
$(OBJ)/write_asmfile.o: $(SRC)/write_asmfile.c 
	$(CC) $(CFLAGS) -c -o $@ $<

	
# Génération du fichier Flex
$(SRC)/$(LEX).yy.c: $(SRC)/$(LEX).l
	flex -o $@ $<


# Partie asm

asm: $(TARGET)

$(TARGET): $(ASM_OBJS)
	$(CC) $(CFLAGS) $(ASM_OBJS) -o $(TARGET) $(AFLAGS)

$(OBJ)/%.o: $(SRC)/%.asm
	$(NASM) -f elf64 $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(BIN)/$(OUTPUT) $(OBJ)/*.o $(SRC)/*.tab.c $(SRC)/*.tab.h $(SRC)/*.yy.c
