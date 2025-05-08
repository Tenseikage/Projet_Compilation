#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"
#include "semantics.h"
#include "sem_errors_warns.h"

void is_main_in_code(Symbol_table_functions* tab_funks) {
    if (!tab_funks) {
        fprintf(stderr, "\033[1;31mErreur\033[0m: La table des fonctions est NULL.\n");
        return;
    }

    for (int i = 0; i < tab_funks->index_tab; i++) {
        if (strcmp(tab_funks->tab_funcs[i].name, "main") == 0) {
            if (strcmp(tab_funks->tab_funcs[i].returnType, "int") != 0) {
                error_diff_main_ret(tab_funks->tab_funcs[i].lineno);
                return; // Erreur : fonction main avec un type incorrect
            }
            return; 
        }
    }

    error_no_main(); // fonction absente
}


void same_var_name_func(Symbol_table_functions*tab){
    for(int i = 0; i < tab->index_tab; i++){
        for(int j = i + 1; j < tab->index_tab; j++){
            if(!strcmp(tab->tab_funcs[i].name, tab->tab_funcs[j].name)){
                error_same_var_func(tab->tab_funcs[i].lineno);
            }
        }
    }
}

void check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab){
    int line_return;
    for(int i = 0; i < tab->index_tab; i++){
        if((line_return = is_var_in_table(global_tab,GLOBAL,tab->tab_funcs[i].name))){
            error_global_var_func(line_return,tab->tab_funcs[i].lineno);
        }
    }

}

void check_param_local_vars(Symbol_table_functions* tab){
    for(int j = 0; j < tab->index_tab; j++){
        for(int k = 0;k < tab->tab_funcs[j].index_tabv;k++){
            //printf("Nom de var %s \n", tab->tab_funcs[j].vars[k].name);
            if(is_var_in_table(tab->tab_funcs[j].local_tab,LOCAL, tab->tab_funcs[j].vars[k].name)){
                error_same_var_param_func(tab->tab_funcs[j].vars[k].name, tab->tab_funcs[j].vars[k].lineno);
            }
        }
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
            vars[i].is_affected = 1;
            return vars[i].type;
        }
    }
    return NULL; 
}
int evaluate_constant_expression(Node* root, int* result) {
    if (!root) return 0;

    if (root->label == Num) {
        *result = root->value;
        return 1;
    }

    if (root->label == Addsub || root->label == divstar) {
        int left_result = 0, right_result = 0;
        if (evaluate_constant_expression(root->firstChild, &left_result) &&
            evaluate_constant_expression(root->firstChild->nextSibling, &right_result)) {
            if (strcmp(root->word, "+") == 0) {
                *result = left_result + right_result;
            } else if (strcmp(root->word, "-") == 0) {
                *result = left_result - right_result;
            } else if (strcmp(root->word, "*") == 0) {
                *result = left_result * right_result;
            } else if (strcmp(root->word, "/") == 0) {
                if (right_result == 0) {
                    return 0;
                }
                *result = left_result / right_result;
            }
            return 1;
        }
    }

    return 0; 
}


/*const char* calculate_expression_type(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname, int isleft_var) {
    if (!root) return NULL;
    if (root->label == ident) {

        const char* type = get_var_type(global_tab, GLOBAL, root->word);
        if (type) return type;
        for (int i = 0; i < tab_funcs->index_tab; i++) {
            if (!strcmp(tab_funcs->tab_funcs[i].name, funcname)) {
                type = get_var_type(tab_funcs->tab_funcs[i].local_tab, LOCAL, root->word);
                if (type) return type;
                for (int j = 0; j < tab_funcs->tab_funcs[i].index_tabv; j++) {
                    if (!strcmp(tab_funcs->tab_funcs[i].vars[j].name, root->word)) {
                        if(isleft_var == 0){
                            //printf("oui yaaa %s\n", root->word);
                            tab_funcs->tab_funcs[i].vars[j].is_affected = 1;
                        }
                        return tab_funcs->tab_funcs[i].vars[j].type;
                    }
                }
            }
        }

        //fprintf(stderr, "\033[1;31mErreur\033[0m: Variabless ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);
        return NULL;
    }

    if(root->label == Num){
        return "int";
    } if (root->label == Character){
        return "char";
    }
    return NULL;
}*/


const char* calculate_expression_type(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname, int isleft_var) {
    if (!root) return NULL;
    if (root->label == ident) {
        Node* branch = root->firstChild;
        if (branch) {
            if (branch->label == Arguments) {
                //printf("func \n");
                char* word_func = root->word;
                for (int i = 0; i < tab_funcs->index_tab; i++) {
                    if (!strcmp(tab_funcs->tab_funcs[i].name, word_func)) {
                        return tab_funcs->tab_funcs[i].returnType;
                    }
                }
            } else if (branch->label == Void){
                char* word_func = root->word;
                for (int i = 0; i < tab_funcs->index_tab; i++) {
                    if (!strcmp(tab_funcs->tab_funcs[i].name, word_func)) {
                        return tab_funcs->tab_funcs[i].returnType;
                    }
                }
            }
        }
        const char* global_type = get_var_type(global_tab, GLOBAL, root->word);
        //if (global_type) return global_type;
        for (int i = 0; i < tab_funcs->index_tab; i++) {
            if (!strcmp(tab_funcs->tab_funcs[i].name, funcname)) {
                const char* local_type = get_var_type(tab_funcs->tab_funcs[i].local_tab, LOCAL, root->word);
                if (global_type && !local_type) {
                    return global_type;
                } else if ((global_type || !global_type) &&local_type) {
                    return local_type;
                }
                for (int j = 0; j < tab_funcs->tab_funcs[i].index_tabv; j++) {
                    if (!strcmp(tab_funcs->tab_funcs[i].vars[j].name, root->word)) {
                        if(isleft_var == 0){
                            //printf("oui yaaa %s\n", root->word);
                            tab_funcs->tab_funcs[i].vars[j].is_affected = 1;
                        }
                        return tab_funcs->tab_funcs[i].vars[j].type;
                    }
                }
            }
        }

        //fprintf(stderr, "\033[1;31mErreur\033[0m: Variabless ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);
        return NULL;
    }

    if(root->label == Num){
        return "int";
    } if (root->label == Character){
        return "char";
    }
    return NULL;
}

void check_right_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname, const char* type_left,List_Right* right_list) {    
    if (!root) return;
        if (!right_list->list) {
            right_list->list = malloc(2 * sizeof(const char*));
            if (!right_list->list) {
                fprintf(stderr, "Erreur d'allocation de mémoire right tab \n");
                return;
            }
        } else {
            const char** temp = realloc(right_list->list, 2 * sizeof(const char*));
            if (!temp) {
                fprintf(stderr, "Erreur d'allocation de mémoire right tab \n");
                return;
            }
            right_list->list = temp;
        }
        if (root->label == ident) {
            Node* branch = root->firstChild;
            if (branch) {
                int found = 0;
                if (branch->label == Arguments) {
                    //printf("func \n");
                    int nb_params = 0;
                    Node* branch_args = branch->firstChild;
                    while(branch_args){
                        nb_params++;
                        branch_args = branch_args->nextSibling;
                    }
                    char* word_func = root->word;
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (!strcmp(tab_funks->tab_funcs[i].name, word_func)) {
                            //printf("retour fonction %s, type gauche %s \n",tab_funks->tab_funcs[i].returnType,type_left);
                            if (nb_params < tab_funks->tab_funcs[i].index_tabv) {
                                error_func_toofewargs(word_func, branch->lineno);
                            } else if (nb_params > tab_funks->tab_funcs[i].index_tabv) {
                                error_func_toomanyargs(word_func, branch->lineno);
                            } else if(strcmp(tab_funks->tab_funcs[i].returnType,type_left)){
                                //printf("pipi");
                                error_incomp_affect(type_left,tab_funks->tab_funcs[i].returnType,branch->lineno);
                                return;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        warn_implicit_func_declare(word_func, branch->lineno);
                        return;
                    }
                } else if (branch->label == Void){
                    char* word_func = root->word;
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (!strcmp(tab_funks->tab_funcs[i].name, word_func)) {
                            if(strcmp(tab_funks->tab_funcs[i].returnType,type_left)){
                                //printf("caca")
                                error_incomp_affect(type_left,tab_funks->tab_funcs[i].returnType,branch->lineno);
                                return;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        warn_implicit_func_declare(word_func, branch->lineno);
                        return;
                    }

                }
            } else {
                //printf("ident %s \n", root->word);
                // Node* branch = root->firstChild;
                 const char* type_right = calculate_expression_type(root, global_tab, tab_funks, funcname,1);
                 if(type_left){
                     if(!strcmp(type_left,"char") && !strcmp(type_right,"int")){
                         warn_implicit_conv_int_char(root->lineno);
                     }
                 }
            }
        } else if (root->label == Addsub || root->label == divstar) {
            Node* left = root->firstChild;
            Node* right = root->firstChild->nextSibling;
            //printf("oui right \n");
            if (!left || !right) {
                //fprintf(stderr, "\033[1;31mErreur\033[0m: Opération incomplète (ligne %d).\n", root->lineno);
                //semantic_errors += 1;
                return;
            }
            if (strcmp(root->word, "/") == 0) {
                int right_value = 0;
                // Vérifier si le membre droit est une constante ou une expression constante
                if (evaluate_constant_expression(right, &right_value)) {
                    if (right_value == 0) {
                        warn_div_by_zero(root->lineno);
                        return;
                    }
                }
            }
            const char* rightleft_type = calculate_expression_type(left, global_tab, tab_funks, funcname,1);
            const char* rightright_type = calculate_expression_type(right, global_tab, tab_funks, funcname,1);
            if (rightleft_type){
                right_list->list[right_list->index] = rightleft_type;
                if(type_left){
                    if(!strcmp(type_left,"char") && !strcmp(rightleft_type,"int")){
                        warn_implicit_conv_int_char(root->lineno);
                    }
                }
               right_list->index++;
            }
            if (rightright_type){
                right_list->list[right_list->index] = rightright_type;
                if(type_left){
                    if(!strcmp(type_left,"char") && !strcmp(rightright_type,"int")){
                        warn_implicit_conv_int_char(root->lineno);

                    }
                }
                right_list->index++;
            }
            check_right_instr(left, global_tab, tab_funks, funcname,type_left,right_list);
            check_right_instr(right, global_tab, tab_funks, funcname,type_left,right_list);
            
        } else if(root->label == Num){
            const char* type_right = calculate_expression_type(root, global_tab, tab_funks, funcname,1);
            if(type_left){
                if(!strcmp(type_left,"char") && !strcmp(type_right,"int")){
                    warn_implicit_conv_int_char(root->lineno);
                    
                }
            }
    
        }
}

void evaluate_condexp(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    if (!root) return;
    if (root->label == Addsub || root->label == divstar || root->label == Or || root->label == And || root->label == Eq || root->label == Order) {
        Node* left = root->firstChild;
        Node* right = root->firstChild->nextSibling;
        if (left) {
            evaluate_condexp(left, global_tab, tab_funks, funcname);
        }

        if (right) {
            evaluate_condexp(right, global_tab, tab_funks, funcname);
        }
    } else if (root->label == ident) {
        //printf("esos \n");
        Node* branch = root->firstChild;
        if(branch){
            if(branch->label == Arguments){
                int nb_params = 0;
                Node* branch_args = branch->firstChild;
                while(branch_args){
                    nb_params++;
                    branch_args = branch_args->nextSibling;
                }
                char* func_returntype = is_func_in_tab(tab_funks,root->word);
                int func_params = nb_params_func(tab_funks,root->word);
                if(func_returntype){
                    if(!strcmp(func_returntype,"void")){
                       
                       error_void_cond(root->lineno);
                    } else if (nb_params < func_params){
                        error_func_toofewargs(root->word, branch->lineno);
                    } else if (nb_params > func_params) {
                        error_func_toomanyargs(root->word, branch->lineno);
                    }
                } else {
                    warn_implicit_func_declare(root->word,root->lineno);
                }  
            }
            if (branch->label == Void){
                //printf("oui func void \n");
                char* func_returntype = is_func_in_tab(tab_funks,root->word);
                    if(func_returntype){
                        if(!strcmp(func_returntype,"void")){
                           error_void_cond(root->lineno);
                        }

                    } else {
                        warn_implicit_func_declare(root->word,root->lineno);
                    }
            }

        } else {
            const char* type = calculate_expression_type(root, global_tab, tab_funks, funcname, 0);
            if (!type) {
                error_undeclare_var(root->word, root->lineno);
            }
        }
    } 
}


void add_to_return_list(List_Right* return_list, const char* type) {
    if (!return_list->list) {
        return_list->list = malloc(sizeof(const char*));
        if (!return_list->list) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour return_list->list.\n");
            return;
        }
    } else {
        const char** temp = realloc(return_list->list, (return_list->index + 1) * sizeof(const char*));
        if (!temp) {
            fprintf(stderr, "Erreur de réallocation de mémoire pour return_list->list.\n");
            return;
        }
        return_list->list = temp;
    }
    return_list->list[return_list->index] = type;
    return_list->index++;
}

void check_return_func(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    if (!root) return;

    int index_tab = tab_funks->index_tab;
    Symbol_table_function* funcs = tab_funks->tab_funcs;

    for (int i = 0; i < index_tab; i++) {
        if (!strcmp(funcs[i].name, funcname)) {
            // funcSignType = retour de la fonction
            char* funcsignType = funcs[i].returnType;
            //printf("func %s \n", funcsignType);
            Node* branch = root->firstChild;

            if (branch) {
                // Gestion des expressions complexes
                if (branch->label == Addsub || branch->label == divstar || branch->label == Or || branch->label == And || branch->label == Eq || branch->label == Order) {
                    Node* left = branch->firstChild;
                    Node* right = branch->firstChild->nextSibling;

                    // Vérifier les opérandes gauche et droit
                    if (left) {
                        const char* left_type = calculate_expression_type(left, global_tab, tab_funks, funcname, 0);
                        printf("left type %s \n", left_type);
                        if(left_type){
                            if(!strcmp("void",left_type)){
                                error_void_non_ignore(left->lineno);
                            }
                           
                        } 
                        check_return_func(left, global_tab, tab_funks, funcname);
                        
                        
                    }
                    if (right) {
                        const char* right_type = calculate_expression_type(right, global_tab, tab_funks, funcname, 0);
                        printf("right type %s \n", right_type);
                        if(right_type){
                            if(!strcmp("void",right_type)){
                                error_void_non_ignore(right->lineno);
                            }

                        } 
                        check_return_func(right, global_tab, tab_funks, funcname);
                    }
                }

                // Gestion des constantes numériques
                if (branch->label == Num) {
                    if (!strcmp("char", funcsignType)) {
                        warn_ret_int_func_char(root->lineno);
                    } else if (!strcmp("void", funcsignType)) {
                        warn_ret_int_func_void(root->lineno);
                    }
                }

                // Gestion des identifiants
                else if (branch->label == ident) {
                    int found = 0;
                    const char* left_type = calculate_expression_type(branch, global_tab, tab_funks, funcname, 0);

                    if (is_var_in_table(global_tab, GLOBAL, branch->word)) {
                        found = 1;
                    }
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (!strcmp(tab_funks->tab_funcs[i].name, funcname)) {
                            if (is_var_in_table(tab_funks->tab_funcs[i].local_tab, LOCAL, branch->word)) {
                                found = 1;
                            }
                            for (int j = 0; j < tab_funks->tab_funcs[i].index_tabv; j++) {
                                if (!strcmp(tab_funks->tab_funcs[i].vars[j].name, branch->word)) {
                                    found = 1;
                                    left_type = tab_funks->tab_funcs[i].vars[j].type;
                                }
                            }
                        }
                    }

                    Node* minibranch = branch->firstChild;
                    if (minibranch) {
                        if (minibranch->label == Arguments) {
                            int nb_params = 0;
                            Node* branch_args = minibranch->firstChild;
                            while (branch_args) {
                                nb_params++;
                                branch_args = branch_args->nextSibling;
                            }
                            char* func_returntype = is_func_in_tab(tab_funks, branch->word);
                            int func_params = nb_params_func(tab_funks, branch->word);

                            if (func_returntype) {
                                if (nb_params < func_params) {
                                    error_func_toofewargs(branch->word, minibranch->lineno);
                                } else if (nb_params > func_params) {
                                    error_func_toomanyargs(branch->word, minibranch->lineno);
                                }
                            } else {
                                warn_implicit_func_declare(branch->word, minibranch->lineno);
                            }
                        } else if (minibranch->label == Void) {
                            char* func_returntype = is_func_in_tab(tab_funks, branch->word);
                            char* func_returntype_body = is_func_in_tab(tab_funks, funcname); // retour fonction
                            if (func_returntype) {
                                if (strcmp(func_returntype, func_returntype_body) == 0) {
                                    // Rien à signaler
                                } else {
                                    error_retour_incomp(func_returntype_body, func_returntype, minibranch->lineno);
                                }
                            } else {
                                warn_implicit_func_declare(branch->word, minibranch->lineno);
                            }
                        }
                    } else {
                        if (!found) {
                            error_undeclare_var(branch->word, branch->lineno);
                        } else {
                            if (strcmp(left_type, funcsignType) != 0) {
                                //fprintf(stderr, "\033[1;31mErreur\033[0m: Type de retour incorrect pour la fonction '%s' (attendu : %s, trouvé : %s) (ligne %d).\n" funcname, funcsignType, left_type, root->lineno);
                                //semantic_errors++;
                            }
                        }
                    }
                }
            } else {
                // Cas où le return est vide
                if (strcmp(funcsignType, "void") != 0) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Retour vide dans une fonction de type '%s' (ligne %d).\n", funcsignType, root->lineno);
                    semantic_errors++;
                }
            }
        }
    }
}


void check_left_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname,int returnhere,List_Right* return_list) {
    if (!root){
        if(!returnhere){
            warn_no_return(funcname);
            return;
            
        } else {
            return;
        }
    }
    List_Right* right_list = malloc(sizeof(List_Right));
    if(!right_list){
       fprintf(stderr,"Erreur d'allocation de mémoire");
       return;
    }
    // Vérifier les if fonction

    right_list->list = NULL;
    right_list->index = 0;
    if(root->label == If){
        //check_if(root,global_tab,tab_funks,funcname,returnhere);
        Node* condition = root->firstChild;
        if(condition->label == Exp){
            evaluate_condexp(condition->firstChild,global_tab,tab_funks,funcname);  
        }
        
    } 
    if (root->label == While){
        Node* condition = root->firstChild;
        if(condition->label == Exp){
            evaluate_condexp(condition->firstChild,global_tab,tab_funks,funcname);  
        }
    }
    if (root->label == ident) {
        int found = 0;
        const char* left_type = calculate_expression_type(root, global_tab, tab_funks, funcname,0);
        if (is_var_in_table(global_tab, GLOBAL, root->word)) {
            found = 1;
        }
        Node * branch = root->firstChild;
        //Node * branch = branch->firstChild;
        if (branch){
            if (branch->label == Arguments || branch->label == Void) {
                int nb_params = 0;
                Node* branch_args = branch->firstChild;
                while(branch_args){
                    nb_params++;
                    branch_args = branch_args->nextSibling;
                }
                //printf("Nb params %d \n", nb_params);

                char* word_func = root->word;
                found = 0;
                for (int i = 0; i < tab_funks->index_tab; i++) {
                        //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                    if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                        found = 1;
                        //printf("Nb params func %d \n", tab_funks->tab_funcs[i].index_tabv);
                        if(tab_funks->tab_funcs[i].index_tabv > nb_params){
                            error_func_toofewargs(word_func, branch->lineno);
                        } else if(tab_funks->tab_funcs[i].index_tabv < nb_params){
                            error_func_toomanyargs(word_func, branch->lineno);
                        }
                        break;
                    }
                }
                if (!found) {
                    warn_implicit_func_declare(word_func,root->lineno);
                }  
            } else {

                for(int i = 0; i < global_tab->index_tab; i++){
                    //printf("Mot %s \n", root->word);
                    if(is_var_in_table(global_tab,GLOBAL,root->word)){
                        found = 1;
                    }
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
                    error_undeclare_var(root->word, root->lineno); 
                }    
            }
        }if (root->firstChild){
            check_right_instr(root->firstChild,global_tab,tab_funks,funcname,left_type,right_list);
        }
    } if(root->label == Return){
        Node* return_next = root->nextSibling;
        returnhere = 1;
        check_return_func(root,global_tab,tab_funks,funcname);
        if(return_next){
            return; // ignore la suite;
        }
        if (right_list->list) {
            free(right_list->list);
        }
        free(right_list);

    }
    check_left_instr(root->nextSibling, global_tab, tab_funks, funcname,returnhere,return_list);
    /*for(int i = 0; i < return_list->index;i++){
        printf("type retenu %s\n",return_list->list[i]);

    }*/    
}


void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
    if (!root) return;
    if(root->label == DeclFonct){
        Node* branch_func = root->firstChild;
        if(branch_func->label == EnTeteFonct){
            funcname = branch_func->firstChild->nextSibling->word;
        } else if (branch_func->label == Void){
            funcname = branch_func->firstChild->word;
        }
    }
    if (root->label ==  Instr) {
        int returnhere = 0;
        //printf("instr here \n");
        List_Right* return_list = malloc(sizeof(List_Right));
        if(!return_list){
        fprintf(stderr,"Erreur d'allocation de mémoire");
        return;
        }
        // Vérifier les if fonction

        return_list->list = NULL;
        return_list->index = 0;
        check_left_instr(root->firstChild,global_tab,tab_funcs,funcname,returnhere,return_list);

        
    }
    check_variables(root->firstChild, global_tab, tab_funcs,funcname);
    check_variables(root->nextSibling, global_tab, tab_funcs,funcname);


}


void check_unitialized_vars(Symbol_table_functions* tab_funk, Symbol_table_global* global_tab) {
    for (int i = 0; i < global_tab->index_tab; i++) {
        //printf("var globale affectée %d \n",global_tab->vars[i].is_affected);
        if (!global_tab->vars[i].is_affected) {
            warn_global_unitialized(global_tab->vars[i].name, global_tab->vars[i].lineno);
        }
    }
    for (int j = 0; j < tab_funk->index_tab; j++) {
        Symbol_table_function* func = &tab_funk->tab_funcs[j];
        for (int l = 0; l < func->local_tab->index_tab; l++) {
            if (!func->local_tab->vars[l].is_affected) {
                warn_local_unitialized(func->local_tab->vars[l].name, func->name, func->local_tab->vars[l].lineno);
            }
        }
    }
}