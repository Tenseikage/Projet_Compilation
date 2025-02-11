#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

#define INITIAL_SIZE 10
#define RESIZE_FACTOR 2

int is_var_in_table(Symbol_table* tab, const char* name) {
    for (int i = 0; i < tab->table_size; i++) {
        if (strcmp(tab->vars[i].name, name) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void add_var(Symbol_table* tab,const char* name, label_t type, int lineno){
	if(tab->index_tab >= tab->table_size){
		tab->table_size *= RESIZE_FACTOR;
		tab->vars = realloc(tab->vars, tab->table_size * sizeof(Data));
        if (!tab->vars) {
            fprintf(stderr, "Erreur d'allkocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
	}
	if (is_var_in_table(tab, name)) {
        fprintf(stderr, "Erreur sémantique : le nom existe déjà\n");
        return;
    }
	strcpy(tab->vars[tab->index_tab].name, name);
	tab->vars[tab->index_tab].type = type;
	tab->index_tab++;
}

Symbol_table* init_table(void){
	Symbol_table* tab = malloc(sizeof(Symbol_table));
	if(!tab) {
		fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
	tab->table_size = INITIAL_SIZE;
    tab->vars = malloc(tab->table_size * sizeof(Data));
    if (!tab->vars) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
	tab->table_size = 0;
	tab->index_tab = 0;
	return tab;

}



void display_symb_tab(Symbol_table* tab){
	printf("\n");
	if(!tab) return;
	for(int i = 0; i < tab->index_tab; i++){
	    //fprintf(stdout,"oui\n");
		fprintf(stdout,"%s : %d \n",tab->vars[i].name,tab->vars[i].type);
	}
}

void fill_symb_tab(Symbol_table* tab,Node * root){
	if(!root) return;
    if (root->label == ident){
		printf("Nom : %s  Type : %d \n",root->word,root->label);
		add_var(tab,root->word, root->label, root->lineno);
	} 
    fill_symb_tab(tab,root->firstChild);
	fill_symb_tab(tab,root->nextSibling);
}
