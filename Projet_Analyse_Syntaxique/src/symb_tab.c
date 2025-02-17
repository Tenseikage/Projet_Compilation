#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

#define INITIAL_SIZE 10
#define RESIZE_FACTOR 2

int is_var_in_table(void* tab, TableType type, const char* name) {
    int table_size = 0;
	int index_tab = 0;
	Data* vars;
	if (type == LOCAL){
		Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
		table_size = sym_tab->table_size;
		index_tab = sym_tab->index_tab;
		vars = sym_tab->vars;
   	} else {
		Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
		table_size = sym_tab->table_size;
		index_tab = sym_tab->index_tab;
		vars = sym_tab->vars;
    } 
	for (int i = 0; i < index_tab; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void add_var(void* tab, TableType type, const char* name, label_t label, int lineno) {
    int* table_size;
    int* index_tab;
    Data** vars;

    if (type == LOCAL) {
        Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        vars = &sym_tab->vars;
    } else {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        vars = &sym_tab->vars;
    }

    if (*index_tab >= *table_size) {
        *table_size *= RESIZE_FACTOR;
        *vars = realloc(*vars, *table_size * sizeof(Data));
        if (!*vars) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }
    if (is_var_in_table(tab, type, name)) {
        fprintf(stderr, "Erreur sémantique : le nom existe déjà\n");
        return;
    }
    strcpy((*vars)[*index_tab].name, name);
    (*vars)[*index_tab].type = label;
    (*index_tab)++;
}

void fill_vars(void* tab, TableType type, Node* root) {
    if (!root) return;
    if (root->label == ident) {
        add_var(tab, type, root->word, root->label, root->lineno);
    }
    fill_vars(tab, type, root->firstChild);
    fill_vars(tab, type, root->nextSibling);
}

void fill_symb_tab(void* tab, TableType type, Node* root) {
    if (!root) return;
    if (root->label == DeclVarsLocale && type == LOCAL) {
        fill_vars(tab, type, root->firstChild);
    }
	if (root->label == DeclVars && type == GLOBAL){
		fill_vars(tab, type, root->firstChild);

	}
    fill_symb_tab(tab, type, root->firstChild);
    fill_symb_tab(tab, type, root->nextSibling);
}


void* init_table(TableType type) {
    void* tab;
    if (type == LOCAL) {
        tab = malloc(sizeof(Symbol_table_locale));
        if (!tab) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
        ((Symbol_table_locale*)tab)->table_size = INITIAL_SIZE;
        ((Symbol_table_locale*)tab)->index_tab = 0;
        ((Symbol_table_locale*)tab)->vars = malloc(INITIAL_SIZE * sizeof(Data));
        if (!((Symbol_table_locale*)tab)->vars) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    } else {
        tab = malloc(sizeof(Symbol_table_global));
        if (!tab) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
        ((Symbol_table_global*)tab)->table_size = INITIAL_SIZE;
        ((Symbol_table_global*)tab)->index_tab = 0;
        ((Symbol_table_global*)tab)->vars = malloc(INITIAL_SIZE * sizeof(Data));
        if (!((Symbol_table_global*)tab)->vars) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }
    return tab;
}

/*void free_table(void* tab, TableType type) {
    int index_tab;
    Data* vars;

    if (type == LOCAL) {
        Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    } else {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    }

    for (int i = 0; i < index_tab; i++) {
        free(vars[i].name);
    }
    free(vars);
    free(tab);
}*/

void display_symb_tab(void* tab, TableType type) {
    int index_tab;
    Data* vars;

    if (type == LOCAL) {
        Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    } else {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    }

    for (int i = 0; i < index_tab; i++) {
        printf("Nom : %s, Type : %d\n", vars[i].name, vars[i].type);
    }
}


