#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "write_asmfile.h"
#include "symb_tab.h"

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


/*Old parcours_arbre_main
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


*/

int get_total_global_size(Symbol_table_global* global_tab){
    int total_global_size = 0;
    //printf("mehhh %d\n", global_tab->index_tab);
    for (int i = 0; i < global_tab->index_tab; i++) {
        //printf("offset %d, mot %s \n",global_tab->vars[i].offset,global_tab->vars[i].name);
        total_global_size += global_tab->vars[i].size;  
    }
    //printf("Var global length : %d \n", total_global_size);
    return total_global_size;
}

int get_var_global_offset(const char* str_ident, Symbol_table_global* global_tab) {
    for (int i = 0; i < global_tab->index_tab; i++) {
        //printf("mehhh %d\n", global_tab->index_tab);
        if (!strcmp(global_tab->vars[i].name, str_ident)) {
            return global_tab->vars[i].offset;
        }
    }
    fprintf(stderr, "Erreur : Variable globale '%s' non trouvée dans la table des symboles.\n", str_ident);
    exit(EXIT_FAILURE);
}

void declVarsGlobal(Node* root,int *byte_length_glob_var){
    if(!root) return;
    if(root->label == type && !strcmp(root->word,"int")){
        Node* branch = root->firstChild;
        while(branch){
            //printf("entier présent yay ! %s\n", branch->word);
            *byte_length_glob_var += 4;
            branch = branch->nextSibling;
    
        }
        return;
        //printf("entier présent yay ! %s\n", branch->word);
        //*byte_length_glob_var += 4;

    } if(root->label == type && !strcmp(root->word,"char")){
        Node* branch = root->firstChild;
        while(branch){
            //printf("char présent yay ! %s\n", branch->word); 
            *byte_length_glob_var += 1; 
            branch = branch->nextSibling;
        }
        return;
    }
    declVarsGlobal(root->nextSibling,byte_length_glob_var);

}

void parcours_operators(Node* root, FILE* file, Symbol_table_global* global_tab) {
    //printf("I'm here yaaa \n");
    if (!root) {
        //printf("Nigga u loose !!! \n");
        return;

    }
    if (root->label == Num) {
        //printf("Num !!\n");
        fprintf(file, "  push %d\n", root->value); 
        return;
    }

    if (root->label == ident) {
        int offset = get_var_global_offset(root->word, global_tab);
        fprintf(file, "  mov eax, [TAB_GLOBAL + %d]\n", offset);
        fprintf(file, "  push rax \n");
        return;
    }

    if (root->label == divstar) {
        parcours_operators(root->firstChild, file, global_tab);
        parcours_operators(root->firstChild->nextSibling, file, global_tab);
        fprintf(file, "  pop rcx\n"); 
        fprintf(file, "  pop rax\n");

        if (strcmp(root->word, "*") == 0) {
            fprintf(file, "  imul rax, rcx\n");
        } else if (strcmp(root->word, "/") == 0) {
            fprintf(file, "  xor rdx, rdx\n"); // Nettoyer rdx pour la division
            fprintf(file, "  div rcx\n");      // Division
        }

        // Empiler le résultat
        fprintf(file, "  push rax\n");
        return;
    }

    // Si le nœud est un opérateur d'addition ou soustraction
    if (root->label == Addsub) {
        // Générer le code pour les opérandes gauche et droite
        parcours_operators(root->firstChild, file, global_tab); // Opérande gauche
        parcours_operators(root->firstChild->nextSibling, file, global_tab); // Opérande droite

        // Dépilez les deux opérandes et effectuez l'opération
        fprintf(file, "  pop rcx\n"); // Deuxième opérande
        fprintf(file, "  pop rax\n"); // Première opérande

        if (strcmp(root->word, "+") == 0) {
            fprintf(file, "  add rax, rcx\n"); // Addition
        } else if (strcmp(root->word, "-") == 0) {
            fprintf(file, "  sub rax, rcx"); // Soustraction
        }

        // Empiler le résultat
        fprintf(file, "  push rax\n");
        return;
    }
}
void write_asm_tab_global(FILE* file,Symbol_table_global* global_tab){
    if (!file) {
        fprintf(stderr, "Erreur : fichier non existant\n");
        exit(EXIT_FAILURE);
    }
    int byte_global = get_total_global_size(global_tab);
    fprintf(file,"section .bss\n");
    fprintf(file, "  TAB_GLOBAL resb %d\n",byte_global);

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

/*void write_end_asm_file(FILE *file){
    fprintf(file,"  mov rbx, rcx \n");
    fprintf(file,"  mov r12, rax \n");
    fprintf(file, "  call show_registers\n");
    fprintf(file, "  pop rdi\n");
    fprintf(file, "  mov rax, 60\n");
    fprintf(file, "  syscall\n");
}*/

void write_end_asm_file(FILE *file) {
    fprintf(file, "  sub rsp, 8\n");     // Aligner la pile sur 16 octets
    fprintf(file, "  mov rax, 60\n");    // syscall: exit
    fprintf(file, "  xor rdi, rdi\n");   // Code de retour 0
    fprintf(file, "  syscall\n");        // Appel système
    fprintf(file, "  add rsp, 8\n");     // Restaurer la pile
}


void parcours_corps_func(Node* root, FILE* file,Symbol_table_global* global_tab){
    //cas main 
    if(!root) return;
    if(root->label == Instr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                //printf("Instr b \n");
                char* str_ident = branch_instr->word;
                //printf("Mot global var %s \n",str_ident);
                int offset_ident = get_var_global_offset(str_ident,global_tab);
                //printf("Mot global var %s offset : %d \n",str_ident,offset_ident);
                Node* right_expr = branch_instr->firstChild;
                //parcours_operators(rig)
                if(right_expr){
                    parcours_operators(right_expr,file,global_tab);
                    fprintf(file,"\n");
                    fprintf(file, "  pop rax\n");
                    fprintf(file, "  mov [TAB_GLOBAL + %d], rax\n", offset_ident);
                    fprintf(file,"\n");
                }
            }
            branch_instr = branch_instr->nextSibling;

        }
        
    }
    parcours_corps_func(root->firstChild,file,global_tab);
    parcours_corps_func(root->nextSibling,file,global_tab);
}



void parcours_arbre(Node* root,FILE* file,Symbol_table_global* global_tab) {
    if (!root) return;
    /*if(root->label == DeclVars){
        Node* branch = root->firstChild;
        while (branch) {
            Exemple : chaque variable globale occupe 4 octets
            byte_length_glob_var += 4;
            declVarsGlobal(branch, byte_length_glob_var);
            branch = branch->nextSibling;
        }
    }*/
    if(root->label == DeclFonct){
        Node* branch_func_name = root->firstChild->firstChild->nextSibling;
        Node* corps_fonc = root->firstChild->nextSibling->nextSibling;
        if(branch_func_name){
            //printf("présence de fonction hehe %s\n", branch_func_name->word);
            if(!strcmp(branch_func_name->word,"main")){
                //printf("ouii yaaaa !!! \n");
                if(!corps_fonc){
                    //printf("Non fdp !!! \n");
                } else {
                    //printf("C'est bon yaaa !! \n");
                    parcours_corps_func(corps_fonc,file,global_tab);
                }
                //parcours_corps_func(corps_fonc,file,global_tab);


            }
        }
    } 
    parcours_arbre(root->firstChild,file,global_tab);
    parcours_arbre(root->nextSibling,file,global_tab);
}


/*void parcours_operators(Node* root, FILE * file){
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
*/