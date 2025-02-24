#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

#define INITIAL_SIZE 10
#define NBR_FUNCS 5
#define RESIZE_FACTOR 2

int is_var_in_table(void* tab, TableType type, const char* name) {
    int index_tab;
	Data* vars;
	if (type == LOCAL){
		Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
		index_tab = sym_tab->index_tab;
		vars = sym_tab->vars;
   	} else {
		Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
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

void add_var(void* tab, TableType type, const char* name, label_t label, int lineno,int state) {
    int* table_size;
    int* index_tab;
    Data** vars;
    Symbol_table_function ** funcs = NULL;

    if (type == LOCAL) {
        Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        vars = &sym_tab->vars;
    } else if (type == GLOBAL) {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        vars = &sym_tab->vars;
    } else {
        Symbol_table_functions* sym_tab = (Symbol_table_functions*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        funcs = &sym_tab->tab_funcs;
    }


    if(type == LOCAL || type == GLOBAL){
        if (*index_tab >= *table_size) {
            *table_size *= RESIZE_FACTOR;
            *vars = realloc(*vars, *table_size * sizeof(Data));
            if (!*vars) {
                fprintf(stderr, "Erreur d'allocation de mémoire 1\n");
                exit(EXIT_FAILURE);
            }
        }
        if (is_var_in_table(tab, type, name)) {
            fprintf(stderr, "Erreur sémantique : le nom existe déjà\n");
            return;
        }
        strcpy((*vars)[*index_tab].name, name);
        (*vars)[*index_tab].type = label;
        (*vars)[*index_tab].isStatic = state;
        (*index_tab)++;
    } else {
        if(*index_tab >= *table_size){
            *table_size *= RESIZE_FACTOR;
            *funcs = realloc(*funcs,*table_size *  sizeof(Symbol_table_function));
            if(!*funcs){
                fprintf(stderr, "Erreur d'allocation de mémoire de 2\n");
                exit(EXIT_FAILURE);
            }
        }
        if (is_var_in_table(tab, type, name)) {
            fprintf(stderr, "Erreur sémantique : le nom existe déjà\n");
            return;
        }
        strcpy((*funcs)[*index_tab].name, name);
        (*funcs)[*index_tab].returnType = label;
        (*funcs)[*index_tab].local_tab = init_table(LOCAL);
        (*index_tab)++;


    }
}

void fill_vars(void* tab, TableType types, Node* root) {
    if (!root) return;
    if (root->label == ident) {
        add_var(tab, types, root->word, root->label, root->lineno,0);
    } if (root->label == Static){
        if(root->nextSibling->label == type){
           Node* branch = root->nextSibling->nextSibling;
            if (branch->label == ident){
                add_var(tab,types,branch->word,branch->label,branch->lineno,1);
            }
        }

    }
    fill_vars(tab, types, root->firstChild);
    fill_vars(tab, types, root->nextSibling);
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

void fill_symb_tab_func(Symbol_table_functions* tab,TableType types, Node* root, int* index){
    if(!root) return;
    if(root->label == EnTeteFonct){
        add_var(tab, types, root->firstChild->nextSibling->word, root->label, root->lineno,0);
        (*index)++;
    }
    if (root->label == DeclVarsLocale) {
        if (*index > 0 && *index <= tab->index_tab) {
            fill_vars(tab->tab_funcs[*index - 1].local_tab, LOCAL, root->firstChild);
        } else {
            fprintf(stderr, "Erreur : index hors limites\n");
            return;
        }
    }
    fill_symb_tab_func(tab, types, root->firstChild,index);
    fill_symb_tab_func(tab,types,root->nextSibling,index);
}


void* init_table(TableType type) {
    //Tables de symboles locales / globales
    void* tab;
    if (type == LOCAL) {
        tab = malloc(sizeof(Symbol_table_locale));
        if (!tab) {
            fprintf(stderr, "Erreur d'allocation de mémoire 2\n");
            exit(EXIT_FAILURE);
        }
        ((Symbol_table_locale*)tab)->table_size = INITIAL_SIZE;
        ((Symbol_table_locale*)tab)->index_tab = 0;
        ((Symbol_table_locale*)tab)->vars = malloc(INITIAL_SIZE * sizeof(Data));
        if (!((Symbol_table_locale*)tab)->vars) {
            fprintf(stderr, "Erreur d'allocation de mémoire 3\n");
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
            fprintf(stderr, "Erreur d'allocation de mémoire 4\n");
            exit(EXIT_FAILURE);
        }
    }
    return tab;
}

Symbol_table_functions* init_symb_tab_func(void) {
    // Allocation pour une seule table de symboles pour une fonction
    Symbol_table_functions* tab = malloc(sizeof(Symbol_table_functions));
    if (!tab) {
        fprintf(stderr, "Erreur d'allocation de mémoire 7\n");
        return NULL;
    }
    tab->tab_funcs = malloc(NBR_FUNCS * sizeof(Symbol_table_function));
    if (!tab->tab_funcs) {
        fprintf(stderr, "Erreur d'allocation de mémoire 8\n");
        free(tab);
        return NULL;
    }
    tab->table_size = NBR_FUNCS;
    tab->index_tab = 0;
    for (int i = 0; i < NBR_FUNCS; i++) {
        tab->tab_funcs[i].local_tab = init_table(LOCAL);
        if (!tab->tab_funcs[i].local_tab) {
            fprintf(stderr, "Erreur d'allocation de mémoire 9\n");
            // Libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(tab->tab_funcs[j].local_tab);
            }
            free(tab->tab_funcs);
            free(tab);
            return NULL;
        }
    }

    return tab;

}
void display_local_tab(Symbol_table_locale* tab) {
    if (!tab) {
        fprintf(stderr, "Erreur : la table locale est NULL\n");
        return;
    }

    Data* vars = tab->vars;
    for (int i = 0; i < tab->index_tab; i++) {
        printf("Nom : %s, Type : %d, Statique : %d\n", vars[i].name, vars[i].type, vars[i].isStatic);
    }
}

void display_symb_tab(void* tab, TableType type) {
    int index_tab;
    Data* vars;
    Symbol_table_function* funcs;

    
    if(type == GLOBAL) {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
        for (int i = 0; i < index_tab; i++) {
            printf("Nom : %s, Type : %d\n", vars[i].name, vars[i].type);
        }

    } else {
        Symbol_table_functions* sym_tab = (Symbol_table_functions*)tab;
        index_tab = sym_tab->index_tab;
        funcs = sym_tab->tab_funcs;
        for(int i = 0; i < index_tab; i++){
            printf("Nom : %s, Type : %d\n", funcs[i].name, funcs->returnType);
            if(funcs[i].local_tab){
                //printf("Nom : %s", funcs[i].name);
                display_local_tab(funcs[i].local_tab);
            }  
        }

    }    
}






