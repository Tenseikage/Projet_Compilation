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
	Symbol_table_locale* local_tab = init_table(LOCAL);
    Symbol_table_global* global_tab = init_table(GLOBAL);
    if (args_choice(argc, argv) == 1){
        if(!yyparse()){
            fprintf(stdout, "Affichage de l'arbre : \n");
            printTree(root);
            // Libérer la mémoire allouée
            //free_table(local_tab, LOCAL);
            //free_table(global_tab, GLOBAL);
            fill_symb_tab(local_tab, LOCAL, root);
            fill_symb_tab(global_tab, GLOBAL, root);
            printf("Table des symboles locales:\n");
            display_symb_tab(local_tab, LOCAL);
            printf("Table des symboles globales:\n");
            display_symb_tab(global_tab, GLOBAL);
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