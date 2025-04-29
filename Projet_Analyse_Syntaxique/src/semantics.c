#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb_tab.h"
#include "semantics.h"

int semantic_errors = 0; // Erreurs sémantiques



int check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab){
    int line_return;
    for(int i = 0; i < tab->index_tab; i++){
        if((line_return = is_var_in_table(global_tab,GLOBAL,tab->tab_funcs[i].name))){
            fprintf(stderr,"\033[1;31mErreur de sémantique\033[0m: Même définition variable globale ligne : %d / Nom de fonction ligne : %d\n",line_return,tab->tab_funcs[i].lineno);
            semantic_errors += 1;
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
                semantic_errors += 1;
                return 1;
            }
        }
    }

    return 0;
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
                    return 0; // Division par zéro
                }
                *result = left_result / right_result;
            }
            return 1;
        }
    }

    return 0; // L'expression ne peut pas être évaluée
}


const char* calculate_expression_type(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs, char* funcname) {
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
            const char* type_right = calculate_expression_type(root, global_tab, tab_funks, funcname);
            if(type_left){
                if(!strcmp(type_left,"char") && !strcmp(type_right,"int")){
                    fprintf(stderr, "\033[1;35mWarning\033[0m: Conversion implicite de 'int' en 'char' (ligne %d).\n", root->lineno); 
                }
            }
            if (branch) {
                int found = 0;
                if (branch->label == Arguments) {
                    char* word_func = root->word;
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (!strcmp(tab_funks->tab_funcs[i].name, word_func)) {
                            printf("retour fonction %s, type gauche %s \n",tab_funks->tab_funcs[i].returnType,type_left);
                            if(strcmp(tab_funks->tab_funcs[i].returnType,type_left)){
                                fprintf(stderr, "\033[1;31mErreur\033[0m: Affectation incompatible %s/%s (lingne %d)\n",type_left,tab_funks->tab_funcs[i].returnType,branch->lineno);
                                semantic_errors++;
                                return;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", word_func, branch->lineno);
                        semantic_errors += 1;
                        return;
                    }
                } else if (branch->label == Void){
                    char* word_func = root->word;
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (!strcmp(tab_funks->tab_funcs[i].name, word_func)) {
                            if(strcmp(tab_funks->tab_funcs[i].returnType,type_left)){
                                fprintf(stderr, "\033[1;31mErreur\033[0m: Affectation incompatible %s/%s (ligne %d)\n",type_left,tab_funks->tab_funcs[i].returnType,branch->lineno);
                                semantic_errors++;
                                return;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", word_func, branch->lineno);
                        semantic_errors += 1;
                        return;
                    }

                }
            } /// A voir
        } else if (root->label == Addsub || root->label == divstar) {
            Node* left = root->firstChild;
            Node* right = root->firstChild->nextSibling;
            if (!left || !right) {
                fprintf(stderr, "\033[1;31mErreur\033[0m: Opération incomplète (ligne %d).\n", root->lineno);
                semantic_errors += 1;
                return;
            }
            if (strcmp(root->word, "/") == 0) {
                int right_value = 0;
                // Vérifier si le membre droit est une constante ou une expression constante
                if (evaluate_constant_expression(right, &right_value)) {
                    if (right_value == 0) {
                        fprintf(stderr, "\033[1;35mWarning\033[0m: Division par zéro détectée dans une expression (ligne %d).\n", root->lineno);
                        semantic_errors += 1;
                        return;
                    }
                }
            }
            const char* rightleft_type = calculate_expression_type(left, global_tab, tab_funks, funcname);
            const char* rightright_type = calculate_expression_type(right, global_tab, tab_funks, funcname);
            if (rightleft_type){
                right_list->list[right_list->index] = rightleft_type;
                if(type_left){
                    if(!strcmp(type_left,"char") && !strcmp(rightleft_type,"int")){
                        fprintf(stderr, "\033[1;35mWarning\033[0m: Conversion implicite de 'int' en 'char' (ligne %d).\n", root->lineno); 
                    }
                }
               right_list->index++;
            }
            if (rightright_type){
                right_list->list[right_list->index] = rightright_type;
                if(type_left){
                    if(!strcmp(type_left,"char") && !strcmp(rightright_type,"int")){
                        fprintf(stderr, "\033[1;35mWarning\033[0m: Conversion implicite de 'int' en 'char' (ligne %d).\n", root->lineno); 
                    }
                }
                right_list->index++;
            }
            check_right_instr(left, global_tab, tab_funks, funcname,type_left,right_list);
            check_right_instr(right, global_tab, tab_funks, funcname,type_left,right_list);
            
        } else if(root->label == Num){
            const char* type_right = calculate_expression_type(root, global_tab, tab_funks, funcname);
            if(type_left){
                if(!strcmp(type_left,"char") && !strcmp(type_right,"int")){
                    fprintf(stderr, "\033[1;35mWarning\033[0m: Conversion implicite de 'int' en 'char' (ligne %d).\n", root->lineno); 
                }
            }
    
        }
}



void check_left_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname,int returnhere) {
    if (!root){
        if(!returnhere){
            fprintf(stderr, "\033[1;35mWarning\033[0m: Absence de return dans la fonction non void %s \n", funcname); 
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
    if (root->label == ident) {
        int found = 0;
        const char* left_type = calculate_expression_type(root, global_tab, tab_funks, funcname);
        if (is_var_in_table(global_tab, GLOBAL, root->word)) {
            found = 1;
        }
        Node * branch = root->firstChild;
        if (branch){
            if (branch->label == Arguments) {
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
                            fprintf(stderr, "\033[1;31mErreur\033[0m: Pas assez d'arguments dans la fonction %s appelée mais non déclarée (ligne %d).\n", word_func, branch->lineno);
                            semantic_errors += 1; 
                        } else if(tab_funks->tab_funcs[i].index_tabv < nb_params){
                            fprintf(stderr, "\033[1;31mErreur\033[0m: Beaucoup d'arguments dans la fonction %s appelée mais non déclarée (ligne %d).\n", word_func, branch->lineno);
                            semantic_errors += 1;
                        }
                        break;
                    }
                }
                if (!found) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", word_func, root->lineno);
                    semantic_errors += 1;
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
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Variable ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);  
                    semantic_errors += 1;
                }    
            }
        }if (root->firstChild){
            check_right_instr(root->firstChild,global_tab,tab_funks,funcname,left_type,right_list);
        }
        if (right_list->list) {
            free(right_list->list);
        }
        free(right_list);
    } if(root->label == Return){
        returnhere = 1;
        int index_tab = tab_funks->index_tab;
        Symbol_table_function *funcs = tab_funks->tab_funcs;
        for(int i = 0; i < index_tab; i++){
            if (!strcmp(funcs[i].name,funcname)){
                char* funcsignType = funcs[i].returnType;
                //if()
                Node* branch = root->firstChild;
                if(branch){
                    if(branch->label == Num){
                        if(!strcmp("char",funcsignType)){
                            fprintf(stderr, "\033[1;35mWarning\033[0m: Retour implicite de 'int' dans une fonction de retour 'char' (ligne %d).\n", root->lineno); 
                        } else if(!strcmp("void",funcsignType)){
                            fprintf(stderr, "\033[1;35mWarning\033[0m: Retour int dans une fonction de retour  %s (ligne %d).\n",funcsignType, root->lineno);   
                        }
                    } 
                } else {
                    if(strcmp(funcsignType,"void")){
                        fprintf(stderr, "\033[1;35mWarning\033[0m: Retour void dans une fonction de retour  %s (ligne %d).\n",funcsignType, root->lineno);  
                    }
                }

            }
        }

    }
    check_left_instr(root->nextSibling, global_tab, tab_funks, funcname,returnhere);    
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
        check_left_instr(root->firstChild,global_tab,tab_funcs,funcname,returnhere);
        
    }
    check_variables(root->firstChild, global_tab, tab_funcs,funcname);
    check_variables(root->nextSibling, global_tab, tab_funcs,funcname);
}