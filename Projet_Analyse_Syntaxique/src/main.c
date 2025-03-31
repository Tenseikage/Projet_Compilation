#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "parser.tab.h"
#include "symb_tab.h"
#include "write_asmfile.h"

extern Node* root; 



int main(int argc, char *argv[]) {
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func();
    char* funcname = NULL;
    if (args_choice(argc, argv) == 1) {
        if (!yyparse()) {
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
                printf("============================================\n");
                display_symb_tab(global_tab, GLOBAL);
                printf("============================================\n");
                printf("Fonctions et variables locales \n");
                printf("============================================\n");
                display_symb_tab(tab_funcs, FUNCTION);
                printf("============================================\n");

                // Vérification des variables et paramètres utilisés
                check_variables(root, global_tab, tab_funcs,funcname);
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
}