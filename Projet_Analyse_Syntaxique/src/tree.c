/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
extern int lineno;       /* from lexer */

/// Fonction qui alloue de manière dynmique la table de symboles

static const char *StringFromLabel[] = {
    "Divstar",
    "Prog",
    "DeclVars",
    "Declarateurs",
    "DeclVarsLocale",
    "DeclFoncts",
    "DeclFonct",
    "EnTeteFonct",
    "Parametres",
    "ListTypeVar",
    "Corps",
    "SuiteInstr",
    "Instr",
    "Exp",
    "Arguments",
    "ListExp",
    "type",
    "identifiant",
    "Void",
    "If",
    "Else",
    "While",
    "Return",
    "Or",
    "And",
    "Egalité",
    "Order",
    "Addsub",
    "valeur",
    "Character",
    "Static",
    "Not",
    "NonStatic"  
};


/*int countLeaves(Node *node) {
    if (node == NULL) {
        return 0;
    }

  // Si le nœud n'a pas d'enfants, c'est une feuille
    if (!FIRSTCHILD(node) || ! SECONDCHILD(node) || !THIRDCHILD(node)) {
        return 1;
    }

    // Compter les feuilles des enfants et des frères
    int count = 0;
    count += countLeaves(FIRSTCHILD(node));
    count += countLeaves(SECONDCHILD(node));
    count += countLeaves(THIRDCHILD(node));

    return count;
}*/

int countLeaves(Node *node) {
    if (node == NULL) {
        return 0;
    }
    if(!node->firstChild && !node->nextSibling){
        return 1;
    } else {
        return countLeaves(node->firstChild) + countLeaves(node->nextSibling);
    }

    


    
}


Node *makeNode(label_t label) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    printf("Run out of memory\n");
    exit(1);
  }
  node->label = label;
  node-> firstChild = node->nextSibling = NULL;
  node->lineno=lineno;
  return node;
}

void addSibling(Node *node, Node *sibling) {
  Node *curr = node;
  while (curr->nextSibling != NULL) {
    curr = curr->nextSibling;
  }
  curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
  if (parent->firstChild == NULL) {
    parent->firstChild = child;
  }
  else {
    addSibling(parent->firstChild, child);
  }
}

void deleteTree(Node *node) {
  if (node->firstChild) {
    deleteTree(node->firstChild);
  }
  if (node->nextSibling) {
    deleteTree(node->nextSibling);
  }
  free(node);
}

void printTree(Node *node) {
	static bool rightmost[128]; // tells if node is rightmost sibling
	static int depth = 0;       // depth of current node
	for (int i = 1; i < depth; i++) { // 2502 = vertical line
		printf(rightmost[i] ? "    " : "\u2502   ");
	}
	if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
		printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
	}

	if (node->word!= NULL)  printf("%s: %s", StringFromLabel[node->label], node->word);
	else {
	if (node->value) printf("%s: %d", StringFromLabel[node->label], node->value);
	else printf("%s", StringFromLabel[node->label]);
	}
	printf("\n");
	depth++;
	for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
		rightmost[depth] = (child->nextSibling) ? false : true;
		printTree(child);
	}
	depth--;
}
