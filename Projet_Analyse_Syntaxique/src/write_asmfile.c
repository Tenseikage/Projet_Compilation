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

/*FILE* file = fopen("./src/_anonymous2.asm", "w");
        write_asm_tab_global(file,global_tab);
        write_asm_file(file);
        parcours_arbre(root,file,global_tab);
        write_end_asm_file(file);
        fclose(file);*/


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

void write_asm_getchar(FILE* file) {
    fprintf(file,
        "getchar:\n"
        "    sub rsp, 8\n"
        "    mov rax, 0          ; syscall read\n"
        "    mov rdi, 0          ; stdin\n"
        "    mov rsi, rsp        ; buffer\n"
        "    mov rdx, 1\n"
        "    syscall\n"
        "    pop rax             ; récupérer caractère\n"
        "    ret\n");
}

void write_asm_putchar(FILE* file) {
    fprintf(file,
        "putchar:\n"
        "    sub rsp, 8\n"
        "    mov [rsp], dil      ; écrire 1 octet\n"
        "    mov rax, 1          ; syscall write\n"
        "    mov rdi, 1          ; stdout\n"
        "    mov rsi, rsp        ; adresse du caractère\n"
        "    mov rdx, 1          ; taille (1 octet)\n"
        "    syscall\n"
        "    add rsp, 8\n"
        "    ret\n");
}

void write_asm_getint(FILE* file) {
    fprintf(file,
        "getint:\n"
        "    mov rbx, 0          ; accumulateur\n"
        "    mov r8, 1           ; signe positif par défaut\n"
        ".boucle_getint:\n"
        "    call getchar\n"
        "    mov rcx, rax\n"
        "    cmp rcx, 10         ; saut de ligne ?\n"
        "    je .fin_getint\n"
        "    cmp rcx, '-'\n"
        "    je .negatif_getint\n"
        "    cmp rcx, '0'\n"
        "    jl .erreur_getint\n"
        "    cmp rcx, '9'\n"
        "    jg .erreur_getint\n"
        "    sub rcx, '0'\n"
        "    imul rbx, 10\n"
        "    add rbx, rcx\n"
        "    jmp .boucle_getint\n"
        ".negatif_getint:\n"
        "    mov r8, -1\n"
        "    jmp .boucle_getint\n"
        ".fin_getint:\n"
        "    imul rbx, r8\n"
        "    mov rax, rbx\n"
        "    ret\n"
        ".erreur_getint:\n"
        "    mov rdi, 5\n"
        "    call exit\n");
}


void write_asm_putint(FILE* file) {
    fprintf(file,
        "putint:\n"
        "    push rbx\n"
        "    push r12\n"
        "    mov rax, rdi\n"
        "    mov rcx, 10\n"
        "    xor rbx, rbx        ; compteur de chiffres\n"
        "    mov r12, rsp        ; sauvegarde pile\n"
        "    cmp rax, 0\n"
        "    jge .convert\n"
        "    mov rdi, '-'\n"
        "    call putchar\n"
        "    neg rax\n"
        ".convert:\n"
        ".convert_loop:\n"
        "    xor rdx, rdx\n"
        "    div rcx             ; rax / 10, reste dans rdx\n"
        "    add dl, '0'\n"
        "    push rdx\n"
        "    inc rbx\n"
        "    test rax, rax\n"
        "    jnz .convert_loop\n"
        ".print_loop:\n"
        "    pop rdi\n"
        "    call putchar\n"
        "    dec rbx\n"
        "    jnz .print_loop\n"
        "    pop r12\n"
        "    pop rbx\n"
        "    ret\n");
}






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
        //printf("mehhh %s\n", global_tab->vars[i].name);
        if (!strcmp(global_tab->vars[i].name, str_ident)) {
            return global_tab->vars[i].offset;
        }
    } 
    return -1;
    //fprintf(stderr, "Erreur : Variable globale '%s' non trouvée dans la table des symboles.\n", str_ident);
    //exit(EXIT_FAILURE);
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

void parcours_expr_droite(Node* root, FILE* file, Symbol_table_global* global_tab) {
    //printf("I'm here yaaa \n");
    if (!root) {
        //printf("Nigga u loose !!! \n");
        return;

    }
    if (root->label == Num) {
        //printf("Num !!\n");
        //printf("Root value %d \n", root->value);
        fprintf(file, "  push %d\n", root->value); 
        return;
    }

    if(root->label == Character){
        fprintf(file, "  mov al, %s \n", root->word);
        fprintf(file, "  push rax \n");
    }

    if (root->label == ident) {
        //printf("mot cherché %s \n",root->word);
        Node* branch = root->firstChild;
        if(!branch){
            int offset = get_var_global_offset(root->word, global_tab);
            fprintf(file, "  mov eax, dword [TAB_GLOBAL + %d]\n", offset);
            fprintf(file, "  push rax \n");
            return;
        } else if(branch->label == Void){
            //printf("oui yaah %s\n", root->word);
            fprintf(file, "  sub rsp, 8\n");
            fprintf(file, "  call %s\n", root->word);
            fprintf(file, "  add rsp, 8\n");
            fprintf(file, "  push rax\n"); 
        }
        
    }

    if (root->label == divstar) {
        parcours_expr_droite(root->firstChild, file, global_tab);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab);
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
        parcours_expr_droite(root->firstChild, file, global_tab); // Opérande gauche
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab); // Opérande droite

        // Dépilez les deux opérandes et effectuez l'opération
        fprintf(file, "  pop rcx\n"); // Deuxième opérande
        fprintf(file, "  pop rax\n"); // Première opérande

        if (strcmp(root->word, "+") == 0) {
            fprintf(file, "  add rax, rcx\n"); // Addition
        } else if (strcmp(root->word, "-") == 0) {
            fprintf(file, "  sub rax, rcx\n"); // Soustraction
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
void write_asm_file_and_built_funcs(FILE *file) {
    if (!file) {
        fprintf(stderr, "Erreur : fichier non existant\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "global _start\n");
    fprintf(file, "section .text\n");
    fprintf(file, "extern show_registers\n");
    fprintf(file, "extern exit\n");
    fprintf(file,"\n");
    fprintf(file,"\n");
    fprintf(file,"\n");
    write_asm_getchar(file);
    write_asm_getint(file);
    write_asm_putchar(file);
    write_asm_putint(file);
    //fprintf(file, "extern getint")
    
    
}

void write_asm_main(FILE* file){
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
    //fprintf(file, "  sub rsp, 8\n");     // Aligner la pile sur 16 octets
    fprintf(file, "  mov rax, 60\n");    // syscall: exit
    fprintf(file, "  xor rdi, rdi\n");   // Code de retour 0
    fprintf(file, "  syscall\n");        // Appel système
    //fprintf(file, "  add rsp, 8\n");     // Restaurer la pile
}


char decode_escape_sequence(const char* s) {
    if (s[1] == '\\') {
        switch (s[2]) {
            case 'n': return '\n';
            case 't': return '\t';
            case 'r': return '\r';
            case '\\': return '\\';
            case '\'': return '\'';
            case '\"': return '\"';
            default: return '?'; // ou gérer d'autres cas
        }
    } else {
        return s[0];
    }
}

void parcours_corps_func(Node* root, FILE* file,Symbol_table_global* global_tab){
    //cas main 
    if(!root) return;
    if(root->label == Instr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                Node* ident_branch = branch_instr->firstChild;
                char* str_ident = branch_instr->word;
                //printf("word instr %s \n", branch_instr->word);
                if(ident_branch->label != Arguments){
                    int offset_ident = get_var_global_offset(str_ident,global_tab);
                    //printf("Mot global var %s offset : %d \n",str_ident,offset_ident);
                    Node* right_expr = branch_instr->firstChild;
                    //parcours_operators(rig)
                    if(right_expr){
                        parcours_expr_droite(right_expr,file,global_tab);
                        fprintf(file,"\n");
                        fprintf(file, "  pop rax\n");
                        //fprintf(file, "%s \n", str_ident);
                        fprintf(file, "  mov [TAB_GLOBAL + %d], eax\n", offset_ident);
                        fprintf(file,"\n");
                    }
                    
                } else if(ident_branch->label == Arguments){
                    //printf("word instr %s \n", branch_instr->word);
                    //printf("oui yaaah \n");
                    Node* arg = ident_branch->firstChild;
                    int nb_args = 0;
                    while(arg){
                        if(nb_args == 0 && arg->label == Character && !strcmp("putchar",branch_instr->word)){
                            printf(" arg word %ld\n", strlen(arg->word));
                            fprintf(file, "  mov rdi, %d\n",decode_escape_sequence(arg->word));
                            fprintf(file, "  call putchar\n");
                        }
                        arg = arg->nextSibling;
                    }
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
            //Cas du main // var globales
            if(!strcmp(branch_func_name->word,"main")){
                write_asm_main(file);
                parcours_corps_func(corps_fonc,file,global_tab);
            }
            // Autres fonctions à venir
            //parcours_corps_func(corps_fonc,file,global_tab);
        }
    } 
    parcours_arbre(root->firstChild,file,global_tab);
    parcours_arbre(root->nextSibling,file,global_tab);
}


