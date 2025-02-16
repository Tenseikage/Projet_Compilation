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
	Symbol_table_locale* tab = init_table();
    if (args_choice(argc, argv) == 1){
        if(!yyparse()){
            fprintf(stdout, "Affichage de l'arbre : \n");
			fill_symb_tab(tab,root);
            //printTree(root);
            display_symb_tab(tab);
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