#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"
#include "semantics.h"


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


void check_right_instr(Node* root,Symbol_table_functions* tab_funks, char* funcname) {    
    if (!root) return;

    if (root->label == ident) {
        Node* branch = root->firstChild;
        printf("Identifiant à droite %s \n", root->word);
        if (branch) {
            if (branch->label == Arguments) {
                char* word_func = root->word;
                int found = 0;
                //printf("index  %d \n",tab_funks->index_tab);
                for (int i = 0; i < tab_funks->index_tab; i++) {
                    //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                    if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s' appelée mais non déclarée (ligne %d).\n", word_func, root->lineno);
                    return;
                }
                
            } 
        }
    } else if (root->label == Addsub || root->label == divstar) {
        // Vérifier les opérandes gauche et droit
        Node* left = root->firstChild;
        Node* right = root->firstChild->nextSibling;

        if (!left || !right) {
            fprintf(stderr, "\033[1;31mErreur\033[0m: Opération incomplète (ligne %d).\n", root->lineno);
            return;
        }

        // Vérification de l'opérande gauche
        if (left->label == ident) {
            int found = 0;
            Node* branch = root->firstChild;
            if (branch) {
                if (branch->label == Arguments) {
                    char* word_func = root->word;
                    int found = 0;
                    //printf("index  %d \n",tab_funks->index_tab);
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                        if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "\033[1;31mErreur\033[0m: Déclaration implicite de fonction %s  (ligne %d).\n", word_func, root->lineno);
                        return;
                    }
                    
                } 
            }
            // Vérifier dans les variables locales et les paramètres
            for (int i = 0; i < tab_funks->index_tab; i++) {
                if (!strcmp(tab_funks->tab_funcs[i].name, funcname)) {
                    if (is_var_in_table(tab_funks->tab_funcs[i].local_tab, LOCAL, left->word)) {
                        found = 1;
                        break;
                    }
                    for (int j = 0; j < tab_funks->tab_funcs[i].index_tabv; j++) {
                        if (!strcmp(tab_funks->tab_funcs[i].vars[j].name, left->word)) {
                            found = 1;
                            break;
                        }
                    }
                }
            }

            if (!found) {
                fprintf(stderr, "\033[1;31mErreur\033[0m: Identifiant '%s' utilisé à gauche mais non déclaré (ligne %d).\n", left->word, left->lineno);
            } else {
                printf("Identifiant '%s' à gauche est déclaré (ligne %d).\n", left->word, left->lineno);
            }
        }
        // Vérification de l'opérande droite
        if (right->label == ident) {
            int found = 0;

            // Vérifier dans les variables globales
            //printf("Nom var à droite présente %s\n", right->word);
            Node* branch = right->firstChild;
            if (branch) {
                if (branch->label == Arguments) {
                    char* word_func = right->word;
                    int found = 0;
                        //printf("index  %d \n",tab_funks->index_tab);
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                            //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                        if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "\033[1;31mErreur\033[0m: Déclaration implicite de fonction %s  (ligne %d).\n\n", word_func, root->lineno);
                        return;
                    }  
                } 
            } else {
                for (int i = 0; i < tab_funks->index_tab; i++) {
                    if (!strcmp(tab_funks->tab_funcs[i].name, funcname)) {
                        if (is_var_in_table(tab_funks->tab_funcs[i].local_tab, LOCAL, right->word)) {
                            found = 1;
                            break;
                        }
                        for (int j = 0; j < tab_funks->tab_funcs[i].index_tabv; j++) {
                            if (!strcmp(tab_funks->tab_funcs[i].vars[j].name, right->word)) {
                                found = 1;
                                break;
                            }
                        }
                    }
                }
                if (!found) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Identifiant'%s' utilisé à droite mais non déclaré (ligne %d).\n", right->word, right->lineno);
                } else {
                    printf("Identifiant '%s' à droite est déclaré (ligne %d).\n", right->word, right->lineno);
                }
        }
            }

        // Vérification récursive des sous-arbres gauche et droit
        check_right_instr(left, tab_funks, funcname);
        check_right_instr(right,tab_funks, funcname);
    }
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


const char* calculate_expression_type(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
    if (!root) return NULL;


    if (root->label == ident) {
        // Vérifier dans les variables globales
        const char* type = get_var_type(global_tab, GLOBAL, root->word);
        if (type) return type;

        // Vérifier dans les variables locales et les paramètres
        for (int i = 0; i < tab_funcs->index_tab; i++) {
            if (!strcmp(tab_funcs->tab_funcs[i].name, funcname)) {
                type = get_var_type(tab_funcs->tab_funcs[i].local_tab, LOCAL, root->word);
                Node* branch = root->firstChild;
                if (branch){
                    if (branch->label == Num){
                        printf("Ceci est un entier \n");
                    } else if (branch->label == Character){
                        printf("Ceci est un char \n");  
                    }
                }
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
        const char* left_type = calculate_expression_type(root->firstChild, global_tab, tab_funcs, funcname);
        const char* right_type = calculate_expression_type(root->firstChild->nextSibling, global_tab, tab_funcs, funcname);

        if (!left_type || !right_type) {
            fprintf(stderr, "\033[1;31mErreur\033[0m: Impossible de déterminer les types des opérandes (ligne %d).\n", root->lineno);
            return NULL;
        }

        if (strcmp(left_type, right_type) != 0) {
            fprintf(stderr, "\033[1;31mErreur\033[0m: Incompatibilité des types dans l'expression (ligne %d).\n", root->lineno);
            return NULL;
        }

        return left_type; // Retourner le type résultant


    }

    return NULL;
}


void check_left_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    if (!root) return;

    if (root->label == ident) {
        int found = 0;
        //printf("Mot trouvé %s \n", root->word);
        const char* expr_type = calculate_expression_type(root, global_tab, tab_funks, funcname);
        if (expr_type) {
            printf("Type de l'expression (ligne %d) : %s\n", root->lineno, expr_type);
        }
        if (is_var_in_table(global_tab, GLOBAL, root->word)) {
            found = 1;
        }
        Node * branch = root->firstChild;
        if (branch){
            if (branch->label == Arguments) {
                char* word_func = root->word;
                int found = 0;
                    //printf("index  %d \n",tab_funks->index_tab);
                for (int i = 0; i < tab_funks->index_tab; i++) {
                        //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                    if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Déclaration implicite de fonction %s  (ligne %d).\n", word_func, root->lineno);
                    //return;
                }  
            } else {
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
                    //printf("Mot écrit %s \n", root->word);
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Variable ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);  
                }
            }
        }
        check_right_instr(root->firstChild,tab_funks,funcname);
    }
    check_left_instr(root->nextSibling, global_tab, tab_funks, funcname);

    
}




void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
    if (!root) return;

    if(root->label == EnTeteFonct){
        funcname = root->firstChild->nextSibling->word;
        //printf("Nom de fonction %s \n",);
    }
    // Vérification des identifiants utilisés
    if (root->label ==  Instr) {
        check_left_instr(root->firstChild,global_tab,tab_funcs,funcname);
        
    }

    // Parcourir les enfants et les frères
    check_variables(root->firstChild, global_tab, tab_funcs,funcname);
    check_variables(root->nextSibling, global_tab, tab_funcs,funcname);
}