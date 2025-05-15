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

int main(int argc, char *argv[])
{

    int choice = args_choice(argc,argv);
    switch (choice){
        case 0:
            return 0;
        break;

        case 1:
            if(!yyparse()){
                printTree(root);
                deleteTree(root);
                return 0;
            } else {
                return 1;
            }
        break;

        case 2:
            if(!yyparse()){
                Symbol_table_global* global_tab = init_table(GLOBAL);
                Symbol_table_functions* tab_funcs = init_symb_tab_func();
                int index = 0;
                fill_symb_tab_func(tab_funcs, FUNCTION, root, &index);
                fill_symb_tab(global_tab, GLOBAL, root);
                display_final_symtab(global_tab,tab_funcs);
                free_all_tables(global_tab,tab_funcs);
                return 0;

            } else {
                return 1;
            }
    
    default:
           if(!yyparse()){
                Symbol_table_global* global_tab = init_table(GLOBAL);
                Symbol_table_functions* tab_funcs = init_symb_tab_func();
                char* funcname = NULL;
                int index = 0;
                fill_symb_tab_func(tab_funcs, FUNCTION, root, &index);
                fill_symb_tab(global_tab, GLOBAL, root);
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
                FILE* file = fopen("./src/_anonymous.asm", "w");
                if (!file) {
                        fprintf(stderr, "Erreur à l'ouverture du fichier\n");
                        return 3;
                }
                write_asm_tab_global_static(file,global_tab,tab_funcs);
                write_asm_file_and_built_funcs(file);
                parcours_arbre(root,file,global_tab,tab_funcs);
                write_end_asm_file(file);
                fclose(file);
                free_all_tables(global_tab, tab_funcs);
                return 0;

            } else {
                return 1;
            }
        break;
    }
}
