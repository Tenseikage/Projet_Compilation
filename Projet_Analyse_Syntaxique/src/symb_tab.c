#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"

#define INITIAL_SIZE 10
#define NBR_FUNCS 5
#define NB_VARS 2
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
            return vars[i].lineno; 
        }
    }
    return 0; 
}

void add_var(void* tab, TableType type, const char* name, char* word, int lineno,int state) {
    int* table_size;
    int* index_tab;
    Data** vars;
    int lineno_found;
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
    } else if (type == FUNCTION) {
        Symbol_table_functions* sym_tab = (Symbol_table_functions*)tab;
        table_size = &sym_tab->table_size;
        index_tab = &sym_tab->index_tab;
        funcs = &sym_tab->tab_funcs;
    } else {
        Symbol_table_function* func = (Symbol_table_function*)tab;
        table_size = &func->tabv_size;
        index_tab = &func->index_tabv;
        vars = &func->vars;
    }


    if(type == LOCAL || type == GLOBAL || type == VARS){
        if (*index_tab >= *table_size) {
            *table_size *= RESIZE_FACTOR;
            *vars = realloc(*vars, *table_size * sizeof(Data));
            if (!*vars) {
                fprintf(stderr, "Erreur d'allocation de mémoire 1\n");
                exit(EXIT_FAILURE);
            }
        }
        if ((lineno_found = is_var_in_table(tab, type, name))) {
            fprintf(stderr, "\033[1;31mErreur de sémantique\033[0m: le nom existe déjà en ligne : %d\n", lineno_found);
            exit(EXIT_FAILURE);
        }
        strcpy((*vars)[*index_tab].name, name);
        (*vars)[*index_tab].type = word;
        (*vars)[*index_tab].isStatic = state;
        (*vars)[*index_tab].lineno = lineno;
        (*index_tab)++;
    } else if(type == FUNCTION) {
        if(*index_tab >= *table_size){
            *table_size *= RESIZE_FACTOR;
            *funcs = realloc(*funcs,*table_size *  sizeof(Symbol_table_function));
            if(!*funcs){
                fprintf(stderr, "Erreur d'allocation de mémoire de 2\n");
                exit(EXIT_FAILURE);
            }
        }
        if ((lineno_found = is_var_in_table(tab, type, name))) {
            fprintf(stderr, "\033[1;31mErreur de sémantique\033[0m: le nom existe déjà en ligne : %d\n", lineno_found);
            return;
        }
        strcpy((*funcs)[*index_tab].name, name);
        (*funcs)[*index_tab].returnType = word;
        (*funcs)[*index_tab].local_tab = init_table(LOCAL);
        (*funcs)[*index_tab].vars = malloc(NB_VARS* sizeof(Data));
        (*funcs)[*index_tab].lineno = lineno;
        (*index_tab)++;


    }
}

void fill_param_funcs(Symbol_table_function* tab,TableType types, Node* root){
    if(!root) return;
    if(root->label == type){
        Node* branch = root->nextSibling;
        if (branch->label == ident){
            add_var(tab,types,branch->word,root->word,branch->lineno,0);
        }
        
    }  
    fill_param_funcs(tab, types, root->nextSibling);
}
    



void fill_vars_locale(void* tab, TableType types, Node* root) {
    if (!root) return;
    if (root->label == Static){
        if(root->nextSibling->label == type){
           Node* branch = root->nextSibling->firstChild;
            if (branch->label == ident){
                add_var(tab,types,branch->word,root->nextSibling->word,branch->lineno,1);
            }
        }   
    }if (root->label == NonStatic){
        if(root->nextSibling->label == type){
           Node* branch = root->nextSibling->firstChild;
            if (branch->label == ident){
                add_var(tab,types,branch->word,root->nextSibling->word,branch->lineno,0);
                //printf("Nom var %s, Nom func %s \n",branch->word,root->nextSibling->word);
                if(branch->nextSibling){
                    branch = branch->nextSibling;
                    //printf("Nom var %s, Nom func %s \n",branch->word,root->nextSibling->word);
                    add_var(tab,types,branch->word,root->nextSibling->word,branch->lineno,0);  
                 }
            }
        }
        
    }
    fill_vars_locale(tab, types, root->nextSibling);
}

void fill_vars_global(void* tab,TableType types, Node* root){
    if (!root) return;
    if(root->label == type){
        Node* branch = root->firstChild;
        if (branch->label == ident){
            add_var(tab,types,branch->word,root->word,branch->lineno,0);
            if(branch->nextSibling){
               branch = branch->nextSibling;
               add_var(tab,types,branch->word,root->word,branch->lineno,0);  
            }
        }

       
    } 
    fill_vars_global(tab,types,root->nextSibling);

}



void fill_symb_tab(void* tab, TableType type, Node* root) {
    if (!root) return;
    if (root->label == DeclVarsLocale && type == LOCAL) {
        // Replissage tableau variables locales fonction
        fill_vars_locale(tab, type, root->firstChild);
    }
	if (root->label == DeclVars && type == GLOBAL){
        // Replissage tableau globales
		fill_vars_global(tab, type, root->firstChild);

	}
    fill_symb_tab(tab, type, root->firstChild);
    fill_symb_tab(tab, type, root->nextSibling);
}

void fill_symb_tab_func(Symbol_table_functions* tab,TableType types, Node* root, int* index){
    if(!root) return;
    if(root->label == EnTeteFonct){
        //Remplit avec les noms de fonctions
        add_var(tab, types, root->firstChild->nextSibling->word, root->firstChild->word, root->lineno,0);
        (*index)++;
    }
    if (root->label == DeclVarsLocale) {
        //Replit la table de variables locales des fonctions
        if (*index > 0 && *index <= tab->index_tab) {
            fill_vars_locale(tab->tab_funcs[*index - 1].local_tab, LOCAL, root->firstChild);
        } else {
            fprintf(stderr, "Erreur : index hors limites\n");
            return;
        }
    } if(root->label == ListTypVar){
        if (*index > 0 && *index <= tab->index_tab) {
            fill_param_funcs(&tab->tab_funcs[*index -1],VARS,root->firstChild);
        }  else {
            fprintf(stderr, "Erreur : index hors limites\n");
            return;
        }
        
    }
    fill_symb_tab_func(tab, types, root->firstChild,index);
    fill_symb_tab_func(tab,types,root->nextSibling,index);
}

int check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab){
    int line_return;
    for(int i = 0; i < tab->index_tab; i++){
        if((line_return = is_var_in_table(global_tab,GLOBAL,tab->tab_funcs[i].name))){
            fprintf(stderr,"\033[1;31mErreur de sémantique\033[0m: Même définition variable globale ligne : %d / Nom de fonction ligne : %d\n",line_return,tab->tab_funcs[i].lineno);
            return 1;
        }
    }
    return 0;

}

int check_param_local_vars(Symbol_table_functions* tab){
    for(int j = 0; j < tab->index_tab; j++){
        for(int k = 0;k < tab->tab_funcs[j].index_tabv;k++){
            //printf("Nom de var %s \n", tab->tab_funcs[j].vars[k].name);
            if(is_var_in_table(tab->tab_funcs[j].local_tab,LOCAL, tab->tab_funcs[j].vars[k].name)){
                fprintf(stderr, "\033[1;31mErreur de sémantique\033[0m: Même définition variable locale / Paramètre de fonction. Nom : %s, Ligne : %d\n", tab->tab_funcs[j].vars[k].name, tab->tab_funcs[j].vars[k].lineno);
                return 1;
            }
        }
    }

    return 0;
}



void check_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    if (!root) return;

    if (root->label == ident) {
        int found = 0;
        if (is_var_in_table(global_tab, GLOBAL, root->word)) {
            found = 1;
        }
        for (int i = 0; i < tab_funks->index_tab; i++) {
            if (!strcmp(tab_funks->tab_funcs[i].name, funcname)) {
                if (is_var_in_table(tab_funks->tab_funcs[i].local_tab, LOCAL, root->word)) {
                    found = 1;
                }
                for (int j = 0; j < tab_funks->tab_funcs[i].index_tabv; j++) {
                    if (!strcmp(tab_funks->tab_funcs[i].vars[j].name, root->word)) {
                        found = 1;
                    }
                }
            }
        }
        if (!found) {
            fprintf(stderr, "\033[1;31mErreur\033[0m: Variable ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);
            return;
            
            
        }
    }

    // Parcourir les enfants et les frères
    check_instr(root->firstChild, global_tab, tab_funks, funcname);
    check_instr(root->nextSibling, global_tab, tab_funks, funcname);
}




const char* get_var_type(void* tab, TableType type, const char* name) {
    int index_tab;
    Data* vars;

    if (type == LOCAL) {
        Symbol_table_locale* sym_tab = (Symbol_table_locale*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    } else if (type == GLOBAL) {
        Symbol_table_global* sym_tab = (Symbol_table_global*)tab;
        index_tab = sym_tab->index_tab;
        vars = sym_tab->vars;
    } else {
        return NULL;
    }

    for (int i = 0; i < index_tab; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].type;
        }
    }
    return NULL; // Type non trouvé
}


const char* compute_expression_type(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
    if (!root) return NULL;

    if (root->label == ident) {
        // Vérifier dans les variables globales
        const char* type = get_var_type(global_tab, GLOBAL, root->word);
        if (type) return type;

        // Vérifier dans les variables locales et les paramètres
        for (int i = 0; i < tab_funcs->index_tab; i++) {
            if (!strcmp(tab_funcs->tab_funcs[i].name, funcname)) {
                type = get_var_type(tab_funcs->tab_funcs[i].local_tab, LOCAL, root->word);
                if (type) return type;

                for (int j = 0; j < tab_funcs->tab_funcs[i].index_tabv; j++) {
                    if (!strcmp(tab_funcs->tab_funcs[i].vars[j].name, root->word)) {
                        return tab_funcs->tab_funcs[i].vars[j].type;
                    }
                }
            }
        }

        fprintf(stderr, "\033[1;31mErreur\033[0m: Variable ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);
        return NULL;
    }

    if (root->label == Addsub || root->label == divstar) {
        // Calculer les types des opérandes gauche et droit
        const char* left_type = compute_expression_type(root->firstChild, global_tab, tab_funcs, funcname);
        const char* right_type = compute_expression_type(root->firstChild->nextSibling, global_tab, tab_funcs, funcname);

        // Vérifier la compatibilité des types
        if (!left_type || !right_type) return NULL;
        if (strcmp(left_type, right_type) != 0) {
            fprintf(stderr, "\033[1;31mErreur\033[0m: Incompatibilité des types dans l'expression (ligne %d).\n", root->lineno);
            return NULL;
        }

        return left_type; // Retourner le type résultant
    }

    return NULL;
}

void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
    if (!root) return;

    if(root->label == EnTeteFonct){
        funcname = root->firstChild->nextSibling->word;
        //printf("Nom de fonction %s \n",);
    }
    // Vérification des identifiants utilisés
    if (root->label ==  Instr) {
        //printf("Instruction présente : %d \n", root->lineno);
        //printf("Mot my %s \n", funcname);
        const char* expr_type = compute_expression_type(root->firstChild, global_tab, tab_funcs, funcname);
        if (expr_type) {
            printf("Type de l'expression (ligne %d) : %s\n", root->lineno, expr_type);
        }
        check_instr(root->firstChild,global_tab,tab_funcs,funcname);
        
    }

    // Parcourir les enfants et les frères
    check_variables(root->firstChild, global_tab, tab_funcs,funcname);
    check_variables(root->nextSibling, global_tab, tab_funcs,funcname);
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
        tab->tab_funcs[i].vars = malloc(sizeof(Data)* NB_VARS);
        tab->tab_funcs[i].tabv_size = NB_VARS;
        tab->tab_funcs[i].index_tabv = 0;
        if (!tab->tab_funcs[i].local_tab) {
            fprintf(stderr, "Erreur d'allocation de mémoire 9\n");
            // Libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(tab->tab_funcs[j].local_tab);
                free(tab->tab_funcs[j].vars);
            }
            free(tab->tab_funcs);
            free(tab);
            return NULL;
        } 
        if(!tab->tab_funcs[i].vars){
            fprintf(stderr, "Erreur d'allocation de mémoire 10\n");
            for (int j = 0; j < i; j++) {
                free(tab->tab_funcs[j].local_tab);
                free( tab->tab_funcs[i].vars);
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
    
   if(tab->index_tab > 0){
        printf("===Variables locales de la fonction=== \n");
        for (int i = 0; i < tab->index_tab; i++) {
            printf("Identifiant : %s, Type : %s, Statique : %d\n", vars[i].name, vars[i].type, vars[i].isStatic);
        }
   }
}

void display_params(Symbol_table_function* func){
    Data* vars = func->vars;
    if(func->index_tabv > 0){
        printf("==Paramètres de fonction==\n");
        for (int i = 0; i < func->index_tabv; i++) {
            printf("Identifiant : %s, Type : %s\n", vars[i].name, vars[i].type);
        }
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
        if(index_tab > 0){
            printf("===Variables Globales===\n");
            for (int i = 0; i < index_tab; i++) {
                printf("Nom : %s, Type : %s\n", vars[i].name, vars[i].type);
            }
            printf("\n");
        }

    } else {
        Symbol_table_functions* sym_tab = (Symbol_table_functions*)tab;
        index_tab = sym_tab->index_tab;
        funcs = sym_tab->tab_funcs;
        for(int i = 0; i < index_tab; i++){
            printf("\n");
            printf("Nom de fonction : %s, Type : %s\n", funcs[i].name, funcs->returnType);
            if(funcs[i].local_tab){
                display_params(&funcs[i]);

                display_local_tab(funcs[i].local_tab); 

            }  
        }

    }    
}


void free_local_table(Symbol_table_locale* tab) {
    if (tab) {
        if (tab->vars) {
            free(tab->vars);
        }
        free(tab);
    }
}

void free_global_table(Symbol_table_global* tab) {
    if (tab) {
        if (tab->vars) {
            free(tab->vars);
        }
        free(tab);
    }
}

void free_function_table(Symbol_table_function* func) {
    if (func) {
        if (func->vars) {
            free(func->vars);
        }
        if (func->local_tab) {
            free_local_table(func->local_tab);
        }
    }
}

void free_functions_table(Symbol_table_functions* tab) {
    if (tab) {
        if (tab->tab_funcs) {
            for (int i = 0; i < tab->index_tab; i++) {
                free_function_table(&tab->tab_funcs[i]);
            }
            free(tab->tab_funcs);
        }
        free(tab);
    }
}

void free_all_tables(Symbol_table_global* global_tab, Symbol_table_functions* funcs_tab) {
    free_global_table(global_tab);
    free_functions_table(funcs_tab);
}


