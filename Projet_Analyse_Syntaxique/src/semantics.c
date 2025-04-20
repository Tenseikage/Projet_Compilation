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
                /*Node* branch = root->firstChild;
                if (branch){
                    if (branch->label == Num){
                        printf("Ceci est un entier : ligne %d\n",root->lineno);
                    } else if (branch->label == Character){
                        printf("Ceci est un char : ligne %d\n",root->lineno);  
                    }
                }*/
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
        //printf("NUMMMMERRRO : Ligne %d \n", root->lineno);
        return "int";
    } if (root->label == Character){
        //printf("CHARAAAACTERR \n");
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
                if (branch->label == Arguments) {
                    char* word_func = root->word;
                    int found = 0;
                    for (int i = 0; i < tab_funks->index_tab; i++) {
                        if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", word_func, root->lineno);
                        return;
                    }
                } 
            }
        } else if (root->label == Addsub || root->label == divstar) {
            // Vérifier les opérandes gauche et droite
            Node* left = root->firstChild;
            Node* right = root->firstChild->nextSibling;
    
            if (!left || !right) {
                fprintf(stderr, "\033[1;31mErreur\033[0m: Opération incomplète (ligne %d).\n", root->lineno);
                return;
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
    
            //printf("Type gauche : %s, Type droite : %s (ligne %d)\n", rightleft_type, rightright_type, root->lineno);
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



void check_left_instr(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    if (!root) return;
    //const char** tab_right_types = NULL; 
    List_Right* right_list = malloc(sizeof(List_Right));
    if(!right_list){
       fprintf(stderr,"Erreur d'allocation de mémoire");
       return;
    }
    right_list->list = NULL;
    right_list->index = 0;
    if (root->label == ident) {
        int found = 0;
        //printf("Mot trouvé %s \n", root->word);
        const char* left_type = calculate_expression_type(root, global_tab, tab_funks, funcname);
        /*if (left_type) {
            printf("Type de la partie gauche (ligne %d) : %s\n", root->lineno, left_type);
        }*/
        if (is_var_in_table(global_tab, GLOBAL, root->word)) {
            //printf("yyyyyeeaaah \n");
            found = 1;
        }
        Node * branch = root->firstChild;
        if (branch){
            if (branch->label == Arguments) {
                char* word_func = root->word;
                //printf("Word func %s\n", word_func);
                found = 0;
                    //printf("index  %d \n",tab_funks->index_tab);
                for (int i = 0; i < tab_funks->index_tab; i++) {
                        //printf(" Fonction  %s \n",tab_funks->tab_funcs[i].name);
                    if (strcmp(tab_funks->tab_funcs[i].name, word_func) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    //printf("Word func frr \n %s", word_func);
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Déclaration implicite de fonction %s  (ligne %d).\n", word_func, root->lineno);
                    //return;
                }  
            } else {

                /*for(int i = 0; i < global_tab->index_tab; i++){
                    //printf("Mot %s \n", root->word);
                    if(is_var_in_table(global_tab,GLOBAL,root->word)){
                        found = 1;
                    }
                }*/
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
                //printf("Variable found %d : %s \n", found,root->word);
                if (!found) {
                    //printf("Mot écrit %s \n", root->word);
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Variable ou paramètre '%s' utilisé mais non déclaré (ligne %d).\n", root->word, root->lineno);  
                    //return;
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
        int index_tab = tab_funks->index_tab;
        Symbol_table_function *funcs = tab_funks->tab_funcs;
        for(int i = 0; i < index_tab; i++){
            if (!strcmp(funcs[i].name,funcname)){
                char* funcsignType = funcs[i].returnType;
                Node* branch = root->firstChild;
                if(branch){
                    if(branch->label == Num){
                        //char* returnType = "int";
                        if(!strcmp("char",funcsignType)){
                            fprintf(stderr, "\033[1;35mWarning\033[0m: Retour implicite de 'int' dans une fonction de retour  'char' (ligne %d).\n", root->lineno); 
                        }
                    }    
                }

            }
            //printf("Nom de fonction : %s, Type : %s\n", funcs[i].name, funcs->returnType);
        }

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