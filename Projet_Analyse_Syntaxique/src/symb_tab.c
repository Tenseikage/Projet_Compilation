#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

#define INITIAL_SIZE 10
#define RESIZE_FACTOR 2


void add_var(Symbol_table* tab,int index, const char* name, label_t type, int lineno){
	printf("name : %s cpt %d \n",name,index);
	if(index >= tab->table_size){
		tab->table_size *= RESIZE_FACTOR;
		tab->vars = realloc(tab->vars, tab->table_size * sizeof(Data));
        if (!tab->vars) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
	}
	for(int j = 0; j < index; j++){
		if(!strcmp(tab->vars[j].name,name)){
			fprintf(stderr,"Erreur sémantique \n");
			return;
		}
	}
	strcpy(tab->vars[index].name, name);
	tab->vars[index].type = type;
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
	return tab;

}



void display_symb_tab(Symbol_table* tab){
	printf("\n");
	if(!tab) return;
	for(int i = 0; i < tab->table_size; i++){
	    //fprintf(stdout,"oui\n");
		fprintf(stdout,"%s : %d \n",tab->vars[i].name,tab->vars[i].type);
	}
}

void fill_symb_tab(Symbol_table* tab,Node * root,int cpt){
	if(!root) return;
    if (root->label == ident){
		printf("Nom : %s  Type : %d \n",root->word,root->label);
		add_var(tab, cpt, root->word, root->label, root->lineno);
	} 
    fill_symb_tab(tab,root->firstChild,cpt + 1);
	fill_symb_tab(tab,root->nextSibling,cpt + 1);
}
