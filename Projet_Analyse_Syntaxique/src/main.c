#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "parser.tab.h"
#include "symb_tab.h"

extern Node* root; 


void write_asm_file(FILE *file) {
    if (!file) {
        fprintf(stderr, "Erreur : fichier non existant\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "global _start\n");
    fprintf(file, "section .text\n");
    fprintf(file, "extern show_registers\n");
    fprintf(file, "_start:\n");
    
}



void write_end_asm_file(FILE *file){
    fprintf(file, "  call show_registers\n");
    fprintf(file, "  pop rdi\n");
    fprintf(file, "  mov rax, 60\n");
    fprintf(file, "  syscall\n");
}

char* asm_operator(char* op){
    if(!strcmp(op,"+")){
        return "add";
    } else if(!strcmp(op,"-")){
        return "sub";
    }
    return NULL;
}
void parcours_operators(Node* root, FILE * file){
    if(root == NULL) return;

    if(root->label == Num){
        printf("Présence d'un nombre %d\n", root->value);
        fprintf(file,"  push %d\n",root->value);
        return;
        
    }
    if(root->label == Addsub){
        //printf("Opérateur %s existant\n", root->word);
        parcours_operators(root->firstChild,file); // Fils
        parcours_operators(root->firstChild->nextSibling,file);
        fprintf(file,"  pop r12\n");
        fprintf(file, "  pop rbx\n");
        char* operator = asm_operator(root->word);
        fprintf(file,"  %s rbx, r12\n",operator);
        fprintf(file, "  push rbx\n");
        return;

    } else {
        parcours_operators(root->firstChild,file);
        parcours_operators(root->nextSibling,file);
    }
    
}


int parcours_arbre_main(Node* root) {
    if (!root) return 1;
    if (root->label == EnTeteFonct) {
        Node* branch = root->firstChild->nextSibling;
        if (!strcmp(branch->word, "main")) {
            printf("Main existe bel et bien \n");
            return 0;
        }
    } 
    if (parcours_arbre_main(root->firstChild) == 0) return 0;
    if (parcours_arbre_main(root->nextSibling) == 0) return 0;
    return 1;
}


int main(int argc, char *argv[]) {
    Symbol_table_global* global_tab = init_table(GLOBAL);
    Symbol_table_functions* tab_funcs = init_symb_tab_func();
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
                    fprintf(stderr, "Erreur : Conflit entre les paramètres et les variables locales.\n");
                }
                if (name_error) {
                    fprintf(stderr, "Erreur : Conflit entre les noms de fonctions et les variables globales.\n");
                }
            } else {
                printf("============================================\n");
                display_symb_tab(global_tab, GLOBAL);
                printf("============================================\n");
                printf("Fonctions et variables locales \n");
                printf("============================================\n");
                display_symb_tab(tab_funcs, FUNCTION);
                printf("============================================\n");
            }
            FILE* file = fopen("./src/_anonymous2.asm", "w");
            if (!file) {
                fprintf(stderr, "Erreur à l'ouverture du fichier\n");
                return 1;
            }
            if (!parcours_arbre_main(root)) {
                write_asm_file(file);
            }
            parcours_operators(root,file);
            write_end_asm_file(file);
            fclose(file);
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

