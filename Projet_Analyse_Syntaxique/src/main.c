#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "parser.tab.h"
#include "symb_tab.h"
#include "semantics.h"
#include "sem_errors_warns.h"
#include "write_asmfile.h"
//#include "write_asmfile.h"

extern Node* root;



/*int main(int argc, char *argv[]) {
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func();
    char* funcname = NULL;
    if (args_choice(argc, argv) == 1) {
        if (!yyparse()) {
            root_copy = root;
            //printf("Word : %d \n", root_copy->lineno);
            printTree(root);
            int index = 0;
            printf("\n");
            fill_symb_tab_func(tab_funcs, FUNCTION, root, &index);
            fill_symb_tab(global_tab, GLOBAL, root);

            // Stocker les résultats des fonctions de vérification
            int param_error = check_param_local_vars(tab_funcs);
            int name_error = check_name_func_global(tab_funcs, global_tab);

            // Vérifiez si l'une des deux fonctions retourne 1 (indiquant une erreur)
            if (param_error || name_error) {
                if (param_error) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Conflit entre les paramètres et les variables locales.\n");
                }
                if (name_error) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Conflit entre les noms de fonctions et les variables globales.\n");
                }
            } else {
                // Partie table des symboles
                printf("========Table des Symboles=====================\n");
                printf("\n");
                display_symb_tab(global_tab, GLOBAL);
                printf("============================================\n");
                printf("Fonctions et variables locales \n");
                printf("============================================\n");
                display_symb_tab(tab_funcs, FUNCTION);
                printf("============================================\n");

                // Vérification des variables et paramètres utilisés
                check_variables(root, global_tab, tab_funcs,funcname);
                printf("length var globales %d \n", parcours_var_globales(root,0));
            }
            deleteTree(root);
            free_all_tables(global_tab, tab_funcs);
            return 0;
        } else {
            fprintf(stderr, "Affichage de l'arbre impossible ! \n");
            free_all_tables(global_tab, tab_funcs);
            return 1;
        }
    } else {
        int parse_result = yyparse();
        free_all_tables(global_tab, tab_funcs);
        return parse_result;
    }
}*/
 

/*int main(int argc, char *argv[]) {
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func();
    char* funcname = NULL;
    //int byte_global = 0;
    if (args_choice(argc, argv) == 1){
        if(!yyparse()){
            printTree(root);
            deleteTree(root);
            free_all_tables(global_tab, tab_funcs);
            return 0;

        } else {
            fprintf(stderr, "Affichage de l'arbre impossible ! \n");
            free_all_tables(global_tab, tab_funcs);
            return 1;
        }
    } else {
        if(!yyparse()){
            int index = 0;
            fill_symb_tab_func(tab_funcs, FUNCTION, root, &index);
            fill_symb_tab(global_tab, GLOBAL, root);
            // Stocker les résultats des fonctions de vérification
            is_main_in_code(tab_funcs) ;
            check_param_local_vars(tab_funcs);
            check_name_func_global(tab_funcs, global_tab);
            check_variables(root, global_tab, tab_funcs,funcname);
            check_unitialized_vars(tab_funcs,global_tab);
            if (semantic_errors > 0){
                free_all_tables(global_tab, tab_funcs);
                return 2;
            }
            free_all_tables(global_tab, tab_funcs);
            return 0;
        } else {
            free_all_tables(global_tab, tab_funcs);
            return 1;
        }
    
    }
}*/

int main(int argc,char *argv[]) {
    // Afficher l'arbre fait planter le bac à sable
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func();
    char* funcname = NULL;
    if(!yyparse()){
        int index = 0;
        fill_symb_tab_func(tab_funcs, FUNCTION, root, &index);
        fill_symb_tab(global_tab, GLOBAL, root);
        printTree(root);
        /*printf("========Table des Symboles=====================\n");
        printf("\n");
        display_symb_tab(global_tab, GLOBAL);
        printf("============================================\n");
        printf("Fonctions et variables locales \n");
        printf("============================================\n");
        display_symb_tab(tab_funcs, FUNCTION);
        printf("============================================\n");
        */
        same_var_name_func(tab_funcs);
        is_main_in_code(tab_funcs);
        check_param_local_vars(tab_funcs);
        check_name_func_global(tab_funcs, global_tab);
        check_variables(root, global_tab, tab_funcs,funcname);
        check_unitialized_vars(tab_funcs,global_tab);
        if(semantic_errors > 0){
            deleteTree(root);
            free_all_tables(global_tab, tab_funcs);
            return 2;
        }
        FILE* file = fopen("./src/_anonymous2.asm", "w");
        if (!file) {
                fprintf(stderr, "Erreur à l'ouverture du fichier\n");
                return 3;
        }
        write_asm_tab_global(file,global_tab);
        write_asm_file_and_built_funcs(file);
        parcours_arbre(root,file,global_tab,tab_funcs);
        write_end_asm_file(file);
        fclose(file);
        free_all_tables(global_tab, tab_funcs);
        deleteTree(root);
        return 0;
    } else {
        free_all_tables(global_tab, tab_funcs);
        return 1;
    }
}

