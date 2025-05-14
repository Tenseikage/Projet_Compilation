#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "write_asmfile.h"
#include "symb_tab.h"

//extern Node* root; 

static int _if_label = 0;
static int _else_label = 0;
static int _false_label = 0;
static int _true_label = 0;
static int cond_elem_count = 0;
//Fonctions s'appelant mutuellement
void write_asm_condexp(Node* root, FILE* file, Symbol_table_global* global_tab);

void write_asm_getchar(FILE* file) {
    fprintf(file,
        "getchar:\n"
        "    sub rsp, 8\n"
        "    mov rax, 0\n"
        "    mov rdi, 0\n"
        "    mov rsi, rsp\n"
        "    mov rdx, 1\n"
        "    syscall\n"
        "    movzx rax, byte [rsp]\n"
        "    add rsp, 8\n"
        "    ret\n");
}

void write_asm_putchar(FILE* file) {
    fprintf(file,
        "putchar:\n"
        "    sub rsp, 8\n"
        "    mov [rsp], dil\n"
        "    mov rax, 1\n"
        "    mov rdi, 1\n"
        "    mov rsi, rsp\n"
        "    mov rdx, 1\n"
        "    syscall\n"
        "    add rsp, 8\n"
        "    ret\n");
}

void write_asm_getint(FILE *file) {
    fprintf(file,
        "getint:\n"
        "    xor rbx, rbx\n"
        "    mov r8, 1\n"
        "    call getchar\n"
        "    cmp rax, -1\n"
        "    je .erreur_getint\n"
        "    cmp rax, '-'\n"
        "    je .set_neg\n"
        "    cmp rax, '0'\n"
        "    jb .erreur_getint\n"
        "    cmp rax, '9'\n"
        "    ja .erreur_getint\n"
        "    jmp .read_digits_first_char\n"
        ".set_neg:\n"
        "    mov r8, -1\n"
        "    call getchar\n"
        "    cmp rax, -1\n"
        "    je .erreur_getint\n"
        "    cmp rax, '0'\n"
        "    jb .erreur_getint\n"
        "    cmp rax, '9'\n"
        "    ja .erreur_getint\n"
        ".read_digits_first_char:\n"
        "    sub rax, '0'\n"
        "    mov rbx, rax\n"
        ".read_digits_loop:\n"
        "    call getchar\n"
        "    cmp rax, '0'\n"
        "    jb .end_read_digits\n"
        "    cmp rax, '9'\n"
        "    ja .end_read_digits\n"
        "    sub rax, '0'\n"
        "    imul rbx, 10\n"
        "    add rbx, rax\n"
        "    jmp .read_digits_loop\n"
        ".end_read_digits:\n"
        "    imul rbx, r8\n"
        "    mov rax, rbx\n"
        "    ret\n"
        ".erreur_getint:\n"
        "    mov rdi, 5\n"
        "    call exit\n"
    );
}

void write_asm_putint(FILE* file) {
    fprintf(file,
        "putint:\n"
        "    push rbx\n"
        "    push r12\n"
        "    mov rax, rdi\n"
        "    mov rcx, 10\n"
        "    xor rbx, rbx\n"
        "    mov r12, rsp\n"
        "    cmp rax, 0\n"
        "    jge .convert\n"
        "    mov rdi, '-'\n"
        "    call putchar\n"
        "    neg rax\n"
        ".convert:\n"
        ".convert_loop:\n"
        "    xor rdx, rdx\n"
        "    div rcx\n"
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




void parcours_expr_droite(Node* root, FILE* file, Symbol_table_global* global_tab,int push_result) {
    //printf("I'm here yaaa \n");
    if (!root) {
        //printf("Nigga u loose !!! \n");
        return;

    }
    if (root->label == Num) {
        //printf("Num !!\n");
        //printf("Root value %d \n", root->value);
        fprintf(file, "  mov rax, %d\n", root->value);
        if (push_result)
            fprintf(file, "  push rax\n");
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
        parcours_expr_droite(root->firstChild, file, global_tab,1);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,1);
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
        parcours_expr_droite(root->firstChild, file, global_tab,1); // Opérande gauche
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,1); // Opérande droite

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
    } else if (root->label == And || root->label == Or || root->label == Not ||
        root->label == Eq || root->label == Order) {
        write_asm_condexp(root, file, global_tab);
        fprintf(file, "  push rax\n"); // Empile la valeur 0 ou 1
        return;
    } else if (root->label == ident && root->firstChild && root->firstChild->label == Void) {
        // Appel de fonction sans arguments
        fprintf(file, "  sub rsp, 8\n"); // Alignement pile si besoin
        fprintf(file, "  call %s\n", root->word);
        fprintf(file, "  add rsp, 8\n");
        fprintf(file, "  push rax\n"); // Empile le résultat pour une expression
        return;
    }
}

void write_asm_cmp_expr(Node* root, FILE* file, Symbol_table_global* global_tab) {
    int lbl_true  = _true_label++;
    int lbl_false = _false_label++;
    int lbl_end   = _if_label++;
    //int lbl_else  = _else_label++;


    // 1) Générer le code pour les deux opérandes (arithmétiques simples)
    parcours_expr_droite(root->firstChild, file, global_tab,1);
    parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,1);

    // 2) Dépiler et comparer
    fprintf(file,
        "  pop rcx            ; rhs\n"
        "  pop rax            ; lhs\n"
        "  cmp rax, rcx       ; comparer lhs vs rhs\n"
    );

    // 3) Sauter selon l’opérateur
    if (strcmp(root->word, "==") == 0)
        fprintf(file, "  je .Ltrue_%d\n",  lbl_true);
    else if (strcmp(root->word, "!=") == 0)
        fprintf(file, "  jne .Ltrue_%d\n",  lbl_true);
    else if (strcmp(root->word, "<") == 0)
        fprintf(file, "  jl .Ltrue_%d\n",  lbl_true);
    else if (strcmp(root->word, "<=") == 0)
        fprintf(file, "  jle .Ltrue_%d\n",  lbl_true);
    else if (strcmp(root->word, ">") == 0)
        fprintf(file, "  jg .Ltrue_%d\n",  lbl_true);
    else if (strcmp(root->word, ">=") == 0)
        fprintf(file, "  jge .Ltrue_%d\n",  lbl_true);

    // 4) Faux sinon
    fprintf(file, "  jmp .Lfalse_%d\n", lbl_false);

    // 5) Etiquette vrai : mettre 1 dans rax, sauter à la fin
    fprintf(file, ".Ltrue_%d:\n", lbl_true);
    fprintf(file, "  mov rax, 1\n");
    fprintf(file, "  jmp .Lend_%d\n", lbl_end);

    // 6) Etiquette faux : mettre 0 dans rax
    fprintf(file, ".Lfalse_%d:\n", lbl_false);
    fprintf(file, "  mov rax, 0\n");
    //int label_cond = _if_label++;
    fprintf(file,
        "  cmp rax, 0\n"
        "  je  .Lelse_%d\n\n", _else_label);
    fprintf(file, ".Lend_%d:\n", lbl_end);
}


void write_asm_condexp(Node* root, FILE* file, Symbol_table_global* global_tab) {
    if (!root) return;
    // Cas opérateurs booléens
    if (root->label == And) {
        int lbl_false = _false_label++;
        int lbl_end = _if_label++;

        // Générer la première condition
        if(root->firstChild){
            write_asm_condexp(root->firstChild, file, global_tab);
            fprintf(file,
                "  cmp rax, 0\n"
                "  je .Lfalse_%d\n", lbl_false);
        }
        

        // Générer la deuxième condition
        if(root->firstChild->nextSibling){
            write_asm_condexp(root->firstChild->nextSibling, file, global_tab);
            fprintf(file,
                "  cmp rax, 0\n"
                "  je .Lfalse_%d\n", lbl_false);
        }
        // Si les deux sont vraies
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);

        // Sinon
        fprintf(file, ".Lfalse_%d:\n", lbl_false);
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }
    if (root->label == Or) {
        int lbl_true = _true_label++;
        int lbl_end = _if_label++;

        // Générer la première condition
        write_asm_condexp(root->firstChild, file, global_tab);
        fprintf(file,
            "  cmp rax, 0\n"
            "  jne .Ltrue_%d\n", lbl_true);

        // Générer la deuxième condition
        write_asm_condexp(root->firstChild->nextSibling, file, global_tab);
        fprintf(file,
            "  cmp rax, 0\n"
            "  jne .Ltrue_%d\n", lbl_true);

        // Si aucune n'est vraie
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);

        // Si au moins une est vraie
        fprintf(file, ".Ltrue_%d:\n", lbl_true);
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }
    if (root->label == Not) {
        int lbl_true = _true_label++;
        int lbl_end = _if_label++;

        write_asm_condexp(root->firstChild, file, global_tab);
        fprintf(file,
            "  cmp rax, 0\n"
            "  je .Ltrue_%d\n", lbl_true);
        // Si c'est vrai (non 0)
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);
        // Si c'est faux (0)
        fprintf(file, ".Ltrue_%d:\n", lbl_true);
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }

    // Comparaisons
    if (root->label == Eq || root->label == Order) {
        printf("oui rrr \n");
        write_asm_cmp_expr(root, file, global_tab);
        return;
    }

    // Expressions arithmétiques simples
    if (root->label == Addsub || root->label == divstar) {
        parcours_expr_droite(root->firstChild, file, global_tab,1);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,1);
        //fprintf(file, "  push rax\n"); // Empile le résultat gauche
        fprintf(file, "  pop rcx\n");
        fprintf(file, "  pop rax\n");
        if (strcmp(root->word, "+") == 0)
            fprintf(file, "  add rax, rcx\n");
        else if (strcmp(root->word, "-") == 0)
            fprintf(file, "  sub rax, rcx\n");
        else if (strcmp(root->word, "*") == 0)
            fprintf(file, "  imul rax, rcx\n");
        else if (strcmp(root->word, "/") == 0) {
            fprintf(file, "  xor rdx, rdx\n");
            fprintf(file, "  div rcx\n");
        }
        return;
    }
    if (root->label == ident) {
        int global_offset = get_var_global_offset(root->word, global_tab);
        fprintf(file, "  mov eax, dword [TAB_GLOBAL + %d]\n", global_offset);
        return;
    }
    if (root->label == Num) {
        fprintf(file, "  mov rax, %d\n", root->value);
        return;
    }
}


void write_asm_if_test(Node* root, FILE* file, Symbol_table_global* global_tab) {
    //printf("label cond blea %d \n", label_cond);
    // 1) On évalue l’expression conditionnelle
    cond_elem_count = 0;
    int else_label = _else_label;
    write_asm_condexp(root, file, global_tab);
    // 2) On dépile et compare à zéro
    fprintf(file,
        "  cmp rax, 0\n"
        "  je  .Lelse_%d\n\n",  else_label);

    //fprintf(file, ".Lif_%d:\n", label_cond);
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
    fprintf(file, "main:\n");
}

void write_asm_func(FILE*  file, const char* funcname){
    if(funcname){
        fprintf(file,"%s:\n",funcname);
    }
}



void write_end_asm_file(FILE *file) {
    //fprintf(file, "  sub rsp, 8\n");     // Aligner la pile sur 16 octets
    fprintf(file, "_start:\n");
    fprintf(file, "  sub rsp, 8\n");
    fprintf(file, "  call main\n");
    fprintf(file, "  add rsp, 8\n");
    fprintf(file, "  mov rdi, rax\n");
    fprintf(file, "  mov rax, 60\n");    // syscall: exit
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
        return s[1];
    }
}

void parcours_instr_cond(Node* root, FILE* file,Symbol_table_global* global_tab){
    if(!root) return;
    if(root->label == SuiteInstr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                Node* ident_branch = branch_instr->firstChild;
                char* str_ident = branch_instr->word;
                //printf("word instr %s \n", branch_instr->word);
                if(ident_branch->label != Arguments && ident_branch->label != Void){
                    int offset_ident = get_var_global_offset(str_ident,global_tab);
                    //printf("Mot global var %s offset : %d \n",str_ident,offset_ident);
                    Node* right_expr = branch_instr->firstChild;
                    //parcours_operators(rig)
                    if(right_expr){
                        parcours_expr_droite(right_expr,file,global_tab,1);
                        fprintf(file,"\n");
                        fprintf(file, "  pop rax\n");
                        //fprintf(file, "%s \n", str_ident);
                        fprintf(file, "  mov [TAB_GLOBAL + %d], eax\n", offset_ident);
                        fprintf(file,"\n");
                    }
                    
                } else if(ident_branch->label == Arguments){
                    //printf("oui yaaah \n");
                    Node* arg = ident_branch->firstChild;
                    int nb_args = 0;
                    while(arg){
                        //printf("nombre args %d \n",nb_args);
                        //printf("word instr %s \n", arg->word);
                        if(nb_args == 0 && arg->label == Character && !strcmp("putchar",branch_instr->word)){
                            //printf(" arg word %ld\n", strlen(arg->word));
                            fprintf(file, "  mov rdi, %d\n",decode_escape_sequence(arg->word));
                            fprintf(file, "  call putchar\n");
                        } else if(nb_args == 0 && arg->label == Character && !strcmp("putint",branch_instr->word)){
                            fprintf(file, "  mov rdi, %d\n",decode_escape_sequence(arg->word));
                            fprintf(file, "  call putint\n");

                        } else if(nb_args == 0 && arg->label == Num && !strcmp("putint",branch_instr->word)){
                            //printf("oui yayya \n");
                            //printf("ttrrress 4 \n");
                            fprintf(file, "  mov edi, %d\n",arg->value);
                            fprintf(file, "  call putint\n");
                        } else if(nb_args == 0 && arg->label == ident && !strcmp("putint",branch_instr->word)){
                            //printf(" word %s , of")
                            int offset_ident = get_var_global_offset(arg->word,global_tab);
                            fprintf(file, "  mov edi, [TAB_GLOBAL + %d]\n",offset_ident);
                            fprintf(file, "  call putint\n");
                        } 
                        arg = arg->nextSibling;
                        nb_args++;
                        
                    }
                    
                }
            } else if (branch_instr->label == If) {
                // 1) écrire le test
                _if_label++;
                _else_label++;
                Node* cond = branch_instr->firstChild;
                Node* then_block  = branch_instr->firstChild->nextSibling;
                Node* else_block = branch_instr->nextSibling;
                if(cond->label == Exp){
                    //printf("frfr \n");
                    write_asm_if_test(cond, file, global_tab);
                }
                
            
                // 2) code du then
                //Node* then_block = branch_instr->nextSibling;
                if(then_block->label == SuiteInstr){
                    parcours_instr_cond(then_block, file, global_tab);
                    //return;
                }

            
                // 3) fin du if / else
                //int cur = _if_label - 1;
                //int cur_else = _else_label - 1;
                //printf("Number if label %d \n", _if_label);
                fprintf(file, "  jmp .Lend_if_%d\n\n", _if_label);
                fprintf(file, ".Lelse_%d:\n",_else_label);
                if (else_block->label == Else && else_block) {
                    parcours_instr_cond(else_block, file, global_tab);
                    //return;
                }
                fprintf(file, ".Lend_if_%d:\n\n", _if_label);
            
                // passer au suivant
                //branch_instr = branch_instr->nextSibling;
                //continue;
            } else if (branch_instr->label == Return) {
                Node* expr = branch_instr->firstChild;
                if (expr) {
                    parcours_expr_droite(expr, file, global_tab,0); // calcule Exp, résultat sur la pile
                    fprintf(file, "  pop rax\n"); // place le résultat dans rax (convention d'appel)
                }
                fprintf(file, "  ret\n");
                // Optionnel : return ici si tu veux arrêter le parcours après un return
                return;
            }
            branch_instr = branch_instr->nextSibling;

        }
        
    }
    parcours_instr_cond(root->firstChild,file,global_tab);
    parcours_instr_cond(root->nextSibling,file,global_tab);
}



void parcours_corps_func(Node* root, FILE* file,Symbol_table_global* global_tab){
    //cas main 
    if(!root) return;
    if(root->label == SuiteInstr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                Node* ident_branch = branch_instr->firstChild;
                if(ident_branch->label == Arguments || ident_branch->label == Void){
                    //char* str_ident = branch_instr->word;
                    Node* arg = ident_branch->firstChild;
                    int nb_args = 0;
                    while(arg){
                        //printf("nombre args %d \n",nb_args);
                        //printf("word instr %s \n", branch_instr->word);
                        if(nb_args == 0 && arg->label == Character && !strcmp("putchar",branch_instr->word)){
                            printf(" arg word %ld\n", strlen(arg->word));
                            fprintf(file, "  mov rdi, %d\n",decode_escape_sequence(arg->word));
                            fprintf(file, "  call putchar\n");
                        } else if(nb_args == 0 && arg->label == Character && !strcmp("putint",branch_instr->word)){
                            fprintf(file, "  mov rdi, %d\n",decode_escape_sequence(arg->word));
                            fprintf(file, "  call putint\n");

                        } else if(nb_args == 0 && arg->label == Num && !strcmp("putint",branch_instr->word)){
                            //printf("ttrrress 1 \n");
                            //printf("oui yayya \n");
                            //fprintf(file, "  mov edi, %d\n",arg->value);
                            //fprintf(file, "  call putint\n");
                        } else if(nb_args == 0 && arg->label == ident && !strcmp("putint",branch_instr->word)){
                            //printf(" word %s , of")
                            int offset_ident = get_var_global_offset(arg->word,global_tab);
                            fprintf(file, "  mov edi, [TAB_GLOBAL + %d]\n",offset_ident);
                            fprintf(file, "  call putint\n");
                        } else if((nb_args == 0 && arg->label == ident && !strcmp("putchar",branch_instr->word))){
                            int offset_ident = get_var_global_offset(arg->word,global_tab);
                            fprintf(file, "  mov edi, [TAB_GLOBAL + %d]\n",offset_ident);
                            fprintf(file, "  call putchar\n");
                        }
                        arg = arg->nextSibling;
                        nb_args++;
                        
                    }
                    
                } else {
                    char* str_ident = branch_instr->word;
                    //printf("word instr %s \n", branch_instr->word);
                    int offset_ident = get_var_global_offset(str_ident,global_tab);
                    Node* right_expr = branch_instr->firstChild;
                    if(right_expr){
                        parcours_expr_droite(right_expr,file,global_tab,1);
                        fprintf(file,"\n");
                        fprintf(file, "  pop rax\n");
                        //fprintf(file, "%s \n", str_ident);
                        fprintf(file, "  mov [TAB_GLOBAL + %d], eax\n", offset_ident);
                        fprintf(file,"\n");
                    }
                }
                
            } else if (branch_instr->label == If) {
                // 1) écrire le test
                _else_label++;
                _if_label++;
                Node* cond = branch_instr->firstChild;
                Node* then_block  = branch_instr->firstChild->nextSibling;
                Node* else_block = branch_instr->nextSibling;
                if(cond->label == Exp){
                    //printf("Yaa exp \n");
                    write_asm_if_test(cond->firstChild, file, global_tab);
                }
                // 2) code du then
                //Node* then_block = branch_instr->nextSibling;
                if(then_block->label == SuiteInstr){
                    //printf("ouii papar \n");
                    parcours_instr_cond(then_block, file, global_tab);
                    //return;
                }
                // 3) fin du if / else
                //printf("Number if label %d \n", _if_label);
                fprintf(file, "  jmp .Lend_if_%d\n\n", _if_label);
                fprintf(file, ".Lelse_%d:\n", _else_label);
                if (else_block->label == Else && else_block) {
                    parcours_instr_cond(else_block, file, global_tab);
                    //return;
                }
                fprintf(file, ".Lend_if_%d:\n\n", _if_label);
            } else if (branch_instr->label == Return) {
                Node* expr = branch_instr->firstChild;
                if (expr) {
                    parcours_expr_droite(expr, file, global_tab,0); // calcule Exp, résultat sur la pile
                    fprintf(file, "  pop rax\n"); // place le résultat dans rax (convention d'appel)
                }
                fprintf(file, "  ret\n");
                // Optionnel : return ici si tu veux arrêter le parcours après un return
                return;
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
            } else {
                write_asm_func(file,branch_func_name->word);
            }
            parcours_corps_func(corps_fonc,file,global_tab);
            // Autres fonctions à venir
            //parcours_corps_func(corps_fonc,file,global_tab);
        }
    } 
    parcours_arbre(root->firstChild,file,global_tab);
    parcours_arbre(root->nextSibling,file,global_tab);
}


