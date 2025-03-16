#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "parser.tab.h"
#include "write_asmfile.h"

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
    fprintf(file,"  mov rbx, rcx \n");
    fprintf(file,"  mov r12, rax \n");
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
        //printf("Présence d'un nombre %d\n", root->value);
        fprintf(file,"  push %d\n",root->value);
        return;
        
    }
    if(root->label == Addsub){
        //printf("Opérateur %s existant\n", root->word);
        parcours_operators(root->firstChild,file); // Fils
        parcours_operators(root->firstChild->nextSibling,file);
        fprintf(file,"  pop rcx\n");
        fprintf(file, "  pop rax\n");
        char* operator = asm_operator(root->word);
        fprintf(file,"  %s rax, rcx\n",operator);
        fprintf(file, "  push rax\n");
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
