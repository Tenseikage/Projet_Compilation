#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "parser.tab.h"
#include "symb_tab.h"
extern Node* root; 


int main(int argc,char *argv[]) {
    // Afficher l'arbre fait planter le bac à sable
	//Symbol_table_locale* local_tab = init_table(LOCAL);
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func(); // Table symboles fonctions et variables locales
    if (args_choice(argc, argv) == 1){
        if(!yyparse()){
            int index = 0;
            fprintf(stdout, "Affichage de l'arbre : \n");
            printTree(root);
            fill_symb_tab_func(tab_funcs,FUNCTION,root,&index);
            fill_symb_tab(global_tab,GLOBAL,root);
            printf("Variables Globales :  \n");
            display_symb_tab(global_tab,GLOBAL);
            printf("Fonctions et variables locales");
            display_symb_tab(tab_funcs,FUNCTION);
            deleteTree(root);
            return 0;

        } else {
            fprintf(stderr, "Affichage de l'arbre impossible ! \n");
            return 1;
        }
    } else {
        return yyparse();
    }
	//display_symb_tab(tab);
}