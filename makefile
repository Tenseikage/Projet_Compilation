CC := gcc
CFLAGS := -Wall 
LDFLAGS := -lfl -ly
BISON := parser
LEX := lex
TREE := tree
OUTPUT := out

# Cible par défaut
all: $(OUTPUT)

# Cible pour l'exécutable final
$(OUTPUT): $(TREE).o $(BISON).tab.o $(LEX).yy.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation du fichier tree
$(TREE).o: $(TREE).c $(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Génération des fichiers Bison
$(BISON).tab.c $(BISON).tab.h: $(BISON).y
	bison -d -Wcounterexamples $(BISON).y

# Compilation du fichier Bison
$(BISON).tab.o: $(BISON).tab.c $(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation du fichier Flex
$(LEX).yy.o: $(LEX).yy.c $(TREE).h
	$(CC) $(CFLAGS) -c -o $@ $<


# Génération du fichier Flex
$(LEX).yy.c: $(LEX).l $(BISON).tab.h
	flex -o $@ $<

# Nettoyage
clean:
	rm -f $(OUTPUT) $(TREE).o $(BISON).tab.* $(LEX).yy.* *.o


