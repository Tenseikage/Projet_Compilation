#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

// Ajout
void add_var(Symbol_table* tab,int index, const char* name, label_t type, int lineno){
	for(int j = 0; j < index; j++){
		if(!strcmp(tab->vars[j].name,name)){
			fprintf(stderr,"Erreur sémantique \n");
			return;
		}
	}
	strcpy(tab->vars[index].name, name);
	tab->vars[index].type = type;
}

void fill_symb_tab(Symbol_table* tab, Node* var){
	tab->table_size = countLeaves(var);
	fprintf(stderr,"Nombre de feuilles : %d \n" ,tab->table_size);
	tab->vars = malloc(tab->table_size * sizeof(Data));
	if(!tab->vars){
		fprintf(stderr,"Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	int cpt = 0;
	Node* node =  FIRSTCHILD(var);
	while(node){
		add_var(tab,cpt,SECONDCHILD(node)->word,FIRSTCHILD(node)->label,FIRSTCHILD(node)->lineno);
		node = node->nextSibling;
		cpt++;
	}
	
}


/*void fill_symb_tab_global(Symbol_table_global* tab,Node* var){

}*/

void display_symb_tab(Symbol_table* tab){
	fprintf(stdout,"oui\n");
	if(!tab) return;
	for(int i = 0; i < tab->table_size; i++){
	    fprintf(stdout,"oui\n");
		fprintf(stdout,"%s : %d \n",tab->vars[i].name,tab->vars[i].type);
	}
}
