#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "write_asmfile.h"

//extern Node* root; 

/* Allocation dans un tableau en asm


; définition d'un tableau

section .bss
	TAB resb 64


section .text

global _start

extern show_registers

_start:
	mov rax, 60
	mov r13b, byte[TAB] ; récupérer 1ere valeur du tableauù
	mov r12, 0
	mov r13, 0
	;xor rdi, rdi ; code de retour 0
	;syscall

boucle:
	mov r13b, byte[TAB + r12]
	call show_registers
	inc r12
	cmp r12, 64
	jge fin
	jmp boucle

fin: 
	mov rax, 60
	mov rdi, 0
	syscall

*/

void declVarsGlobal(Node* root,int byte_length_glob_var){
    if(!root) return;
    if(root->label == type && !strcmp(root->word,"int")){
        printf("entier présent yay ! \n");

    }
    declVarsGlobal(root->nextSibling,byte_length_glob_var);

}

int parcours_var_globales(Node* root, int byte_length_glob_var) {
    if (!root) {
        printf("haha end of shit \n");
        return byte_length_glob_var;
    }
     // Vérification de root

    if (root->label == DeclVars) {
        printf("var globally yay \n");
        Node* branch = root->firstChild;
        while (branch) {
            // Exemple : chaque variable globale occupe 4 octets
            byte_length_glob_var += 4;
            declVarsGlobal(branch, byte_length_glob_var);
            branch = branch->nextSibling;
        }
    }

    // Parcours des frères
    return parcours_var_globales(root->nextSibling, byte_length_glob_var);
}

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


int parcours_arbre(Node* root, int* byte_length_glob_var) {
    if (!root) return 1;
    if(root->label == DeclVars){
        Node* branch = root->firstChild;
        while (branch) {
            // Exemple : chaque variable globale occupe 4 octets
            //*byte_length_glob_var += 4;
            declVarsGlobal(branch, *byte_length_glob_var);
            branch = branch->nextSibling;
        }
    }
    if (root->label == EnTeteFonct) {
        Node* branch = root->firstChild->nextSibling;
        if (!strcmp(branch->word, "main")) {
            printf("Main existe bel et bien \n");
            return 0;
        }
    } 
    if (parcours_arbre(root->firstChild,byte_length_glob_var) == 0) return 0;
    if (parcours_arbre(root->nextSibling,byte_length_glob_var) == 0) return 0;
    return 1;
}

/*void parcours_op(Node* root){
    if(root == NULL) return;

    if(root->label == ident){
        //printf("Présence d'un nombre %d\n", root->value);
        printf("ident yaaah \n");
        return;
        
    }
    if(root->label == Addsub || root->label == divstar){
        //printf("Opérateur %s existant\n", root->word);
        parcours_op(root->firstChild); // Fils
        parcours_op(root->firstChild->nextSibling);
        //fprintf(file,"  pop rcx\n");
        //fprintf(file, "  pop rax\n");
        //char* operator = asm_operator(root->word);
        //fprintf(file,"  %s rax, rcx\n",operator);
        //fprintf(file, "  push rax\n");
        return;

    } else {
        parcours_op(root->firstChild);
        parcours_op(root->nextSibling);
    }
    
}*/