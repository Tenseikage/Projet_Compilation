#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"
#include "write_asmfile.h"
#include "symb_tab.h"
#include "semantics.h"


static int _if_label = 0;
static int _else_label = 0;
static int _false_label = 0;
static int _true_label = 0;
static int cond_elem_count = 0;
static int while_label = 0;
//Fonctions s'appelant mutuellement
static void write_asm_condexp(Node* root, FILE* file, Symbol_table_global* global_tab,Symbol_table_functions* tab_funks,char* funcname);
static void write_asm_while(Node* root, FILE* file, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname);

static void write_asm_getchar(FILE* file) {
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

static void write_asm_putchar(FILE* file) {
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

static void write_asm_getint(FILE *file) {
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






static int get_total_global_size(Symbol_table_global* global_tab){
    int total_global_size = 0;
    for (int i = 0; i < global_tab->index_tab; i++) {
        total_global_size += global_tab->vars[i].size;  
    }
    return total_global_size;
}




static int get_var_global_offset(const char* str_ident, Symbol_table_global* global_tab) {
    for (int i = 0; i < global_tab->index_tab; i++) {
        if (!strcmp(global_tab->vars[i].name, str_ident)) {
            return global_tab->vars[i].offset;
        }
    } 
    return -1;
   
}

static int get_var_local_offset_by_func(Symbol_table_functions* tab, const char* funcname, const char* varname) {
    if (!tab || !funcname || !varname) return -1;
    for (int i = 0; i < tab->index_tab; i++) {
        if (!strcmp(tab->tab_funcs[i].name, funcname)) {
            Symbol_table_locale* local_tab = tab->tab_funcs[i].local_tab;
            for (int j = 0; j < local_tab->index_tab; j++) {
                if (strcmp(local_tab->vars[j].name, varname) == 0) {
                    return local_tab->vars[j].offset;
                }
            }
        }
    }
    return -1; 
}

static int get_total_local_and_param_offset(Symbol_table_functions* tab, const char* funcname) {
    if (!tab || !funcname) return 0;
    int total = 0;
    for (int i = 0; i < tab->index_tab; i++) {
        if (!strcmp(tab->tab_funcs[i].name, funcname)) {
            for (int j = 0; j < tab->tab_funcs[i].index_tabv; j++) {
                total += tab->tab_funcs[i].vars[j].size;
            }
            Symbol_table_locale* local_tab = tab->tab_funcs[i].local_tab;
            for (int k = 0; k < local_tab->index_tab; k++) {
                if (!local_tab->vars[k].isStatic) {
                    total += local_tab->vars[k].size;
                }
            }
            break;
        }
    }
    return total;
}

static Symbol_table_locale* get_local_tab_by_func(Symbol_table_functions* tab, const char* funcname) {
    if (!tab || !funcname) return NULL;
    for (int i = 0; i < tab->index_tab; i++) {
        if (strcmp(tab->tab_funcs[i].name, funcname) == 0) {
            return tab->tab_funcs[i].local_tab;
        }
    }
    return NULL;
}


static void gen_mov_var(FILE* file, const char* varname, const char* funcname, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, int mode) {
    for (int i = 0; i < tab_funks->index_tab; i++) {
        if (!strcmp(tab_funks->tab_funcs[i].name, funcname)) {
            Symbol_table_function* func = &tab_funks->tab_funcs[i];
            for (int j = 0; j < func->index_tabv; j++) {
                if (!strcmp(func->vars[j].name, varname)) {
                    int offset = func->vars[j].offset;
                    const char* var_type = func->vars[j].type;
                    if (!strcmp(var_type, "int")) {
                        if (mode == 0)
                            fprintf(file, "  mov eax, dword [rbp-%d]\n", offset);
                        else
                            fprintf(file, "  mov dword [rbp-%d], eax\n", offset);
                    } else if (!strcmp(var_type, "char")) {
                        if (mode == 0)
                            fprintf(file, "  mov al, byte [rbp-%d]\n", offset);
                        else
                            fprintf(file, "  mov byte [rbp-%d], al\n", offset);
                    }
                    return;
                }
            }
            break;
        }
    }

    int offset = get_var_local_offset_by_func(tab_funks, funcname, varname);
    if (offset >= 0) {
        Symbol_table_locale* local_tab = get_local_tab_by_func(tab_funks, funcname);
        const char* var_type = get_var_type(local_tab, LOCAL, varname);
        int is_static = 0;
        for (int i = 0; i < local_tab->index_tab; i++) {
            if (!strcmp(local_tab->vars[i].name, varname)) {
                is_static = local_tab->vars[i].isStatic;
                break;
            }
        }
        if (is_static) {
            if (!strcmp(var_type, "int")) {
                if (mode == 0)
                    fprintf(file, "  mov eax, dword [static_%s_%s]\n", funcname, varname);
                else
                    fprintf(file, "  mov dword [static_%s_%s], eax\n", funcname, varname);
            } else if (!strcmp(var_type, "char")) {
                if (mode == 0)
                    fprintf(file, "  mov al, byte [static_%s_%s]\n", funcname, varname);
                else
                    fprintf(file, "  mov byte [static_%s_%s], al\n", funcname, varname);
            }
            return;
        } else {
            if (!strcmp(var_type, "int")) {
                if (mode == 0)
                    fprintf(file, "  mov eax, dword [rbp-%d]\n", offset);
                else
                    fprintf(file, "  mov dword [rbp-%d], eax\n", offset);
            } else if (!strcmp(var_type, "char")) {
                if (mode == 0)
                    fprintf(file, "  mov al, byte [rbp-%d]\n", offset);
                else
                    fprintf(file, "  mov byte [rbp-%d], al\n", offset);
            }
            return;
        }
    }
    offset = get_var_global_offset(varname, global_tab);
    if (offset >= 0) {
        const char* var_type = get_var_type(global_tab, GLOBAL, varname);
        if (!strcmp(var_type, "int")) {
            if (mode == 0)
                fprintf(file, "  mov eax, dword [TAB_GLOBAL + %d]\n", offset);
            else
                fprintf(file, "  mov [TAB_GLOBAL + %d], eax\n", offset);
        } else if (!strcmp(var_type, "char")) {
            if (mode == 0)
                fprintf(file, "  mov al, byte [TAB_GLOBAL + %d]\n", offset);
            else
                fprintf(file, "  mov byte [TAB_GLOBAL + %d], al\n", offset);
        }
        return;
    }
    fprintf(stderr, "Erreur : variable '%s' non trouvée\n", varname);
}
static char decode_escape_sequence(const char* s) {
    if (s[1] == '\\') {
        switch (s[2]) {
            case 'n': return '\n';
            case 't': return '\t';
            case 'r': return '\r';
            case '\\': return '\\';
            case '\'': return '\'';
            case '\"': return '\"';
            default: return '?'; 
        }
    } else {
        return s[1];
    }
}


static void parcours_expr_droite(Node* root, FILE* file, Symbol_table_global* global_tab,Symbol_table_functions* tab_funks,char* funcname, int push_result) {
    if (!root) {
        return;

    }
    if (root->label == Num) {
        fprintf(file, "  mov rax, %d\n", root->value);
        if (push_result)
            fprintf(file, "  push rax\n");
        return;
    }

    if(root->label == Character){
        fprintf(file, "  mov al, %d \n", decode_escape_sequence(root->word));
        if(push_result){
            fprintf(file, "  push rax \n");
        }
        return;
    }

    if (root->label == ident) {
        Node* branch = root->firstChild;
        if(!branch){
            gen_mov_var(file,root->word,funcname,global_tab,tab_funks,0);
            if(push_result){
                fprintf(file, "  push rax \n");
            }
            return;
        } else if(branch->label == Void){
            fprintf(file, "  sub rsp, 8\n");
            fprintf(file, "  call %s\n", root->word);
            fprintf(file, "  add rsp, 8\n");
            if(push_result){
              fprintf(file, "  push rax\n"); 
            }
            return;
        }
        
    }

    if (root->label == divstar) {
        parcours_expr_droite(root->firstChild, file, global_tab,tab_funks,funcname,1);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,tab_funks,funcname,1);
        fprintf(file, "  pop rcx\n"); 
        fprintf(file, "  pop rax\n");

        if (strcmp(root->word, "*") == 0) {
            fprintf(file, "  imul rax, rcx\n");
        } else if (strcmp(root->word, "/") == 0) {
            fprintf(file, "  xor rdx, rdx\n"); 
            fprintf(file, "  div rcx\n");      
        } else if (strcmp(root->word, "%") == 0) {
            fprintf(file, "  xor rdx, rdx\n"); 
            fprintf(file, "  div rcx\n");
            fprintf(file, "  mov rax, rdx\n");
        } 

        if(push_result){
           fprintf(file, "  push rax\n");
        }
        return;
    }

    if (root->label == Addsub) {
        // Cette partie assembleur ne gère pas les nombre négatifs
        /*if(root->firstChild && !root->firstChild->nextSibling){
            printf("Negation detected: %s\n", root->word);
            parcours_expr_droite(root->firstChild, file, global_tab,tab_funks,funcname,push_result);
            fprintf(file, "  neg rax\n");
            if(push_result){
                fprintf(file, "  push rax\n");
            }
            return;
        }*/
        parcours_expr_droite(root->firstChild, file, global_tab,tab_funks,funcname,1);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,tab_funks,funcname,1);
        fprintf(file, "  pop rcx\n"); 
        fprintf(file, "  pop rax\n");

        if (strcmp(root->word, "+") == 0) {
            fprintf(file, "  add rax, rcx\n");
        } else if (strcmp(root->word, "-") == 0) {
            fprintf(file, "  sub rax, rcx\n"); 
        }

        if(push_result){
            fprintf(file, "  push rax\n");
        }
        return;
    } else if (root->label == And || root->label == Or || root->label == Not ||
        root->label == Eq || root->label == Order) {
        write_asm_condexp(root, file, global_tab,tab_funks,funcname);
        fprintf(file, "  push rax\n");
        return;
    }else if (root->label == ident && root->firstChild && root->firstChild->label == Arguments) {
        Node* arg = root->firstChild->firstChild;
        int arg_count = 0;
        while (arg && arg_count < 6) {
            if (strcmp(root->word, "putchar") == 0 && arg_count == 0 && arg->label== Character) {
                fprintf(file, "  mov dil,%d\n", decode_escape_sequence(arg->word));
                fprintf(file, "  sub rsp, 8\n");
                fprintf(file, "  call putchar\n");
                fprintf(file, "  add rsp, 8\n");
                return;
            } else {
                parcours_expr_droite(arg, file, global_tab,tab_funks,funcname,0); 
                switch(arg_count) {
                    case 0: fprintf(file, "  mov rdi, rax\n"); break;
                    case 1: fprintf(file, "  mov rsi, rax\n"); break;
                    case 2: fprintf(file, "  mov rdx, rax\n"); break;
                    case 3: fprintf(file, "  mov rcx, rax\n"); break;
                    case 4: fprintf(file, "  mov r8, rax\n"); break;
                    case 5: fprintf(file, "  mov r9, rax\n"); break;
                }
            }
            arg_count++;
            arg = arg->nextSibling;
            
        }
        fprintf(file, "  sub rsp, 8\n");
        fprintf(file, "  call %s\n", root->word);
        fprintf(file, "  add rsp, 8\n");
        if(push_result){
            fprintf(file, "  push rax\n");
        }
        return;
           
    }
    
        
        
    
       
}


static void write_asm_cmp_expr(Node* root, FILE* file, Symbol_table_global* global_tab,Symbol_table_functions* tab_funks,char *funcname) {
    int lbl_true  = _true_label++;
    int lbl_false = _false_label++;
    int lbl_end   = _if_label++;


    parcours_expr_droite(root->firstChild, file, global_tab,tab_funks,funcname,1);
    parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,tab_funks,funcname,1);
    fprintf(file,
        "  pop rcx\n"
        "  pop rax\n"
        "  cmp rax, rcx\n"
    );
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
    fprintf(file, "  jmp .Lfalse_%d\n", lbl_false);
    fprintf(file, ".Ltrue_%d:\n", lbl_true);
    fprintf(file, "  mov rax, 1\n");
    fprintf(file, "  jmp .Lend_%d\n", lbl_end);
    fprintf(file, ".Lfalse_%d:\n", lbl_false);
    fprintf(file, "  mov rax, 0\n");
    fprintf(file, ".Lend_%d:\n", lbl_end);
}


static void write_asm_condexp(Node* root, FILE* file, Symbol_table_global* global_tab,Symbol_table_functions* tab_funks,char* funcname) {
    if (!root) return;
    if (root->label == And) {
        int lbl_false = _false_label++;
        int lbl_end = _if_label++;
        if(root->firstChild){
            write_asm_condexp(root->firstChild, file, global_tab,tab_funks,funcname);
            fprintf(file,
                "  cmp rax, 0\n"
                "  je .Lfalse_%d\n", lbl_false);
        }
        if(root->firstChild->nextSibling){
            write_asm_condexp(root->firstChild->nextSibling,file,global_tab,tab_funks,funcname);
            fprintf(file,
                "  cmp rax, 0\n"
                "  je .Lfalse_%d\n", lbl_false);
        }
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);
        fprintf(file, ".Lfalse_%d:\n", lbl_false);
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }
    if (root->label == Or) {
        int lbl_true = _true_label++;
        int lbl_end = _if_label++;
        write_asm_condexp(root->firstChild, file, global_tab,tab_funks,funcname);
        fprintf(file,
            "  cmp rax, 0\n"
            "  jne .Ltrue_%d\n", lbl_true);
        write_asm_condexp(root->firstChild->nextSibling, file, global_tab,tab_funks,funcname);
        fprintf(file,
            "  cmp rax, 0\n"
            "  jne .Ltrue_%d\n", lbl_true);
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);
        fprintf(file, ".Ltrue_%d:\n", lbl_true);
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }
    if (root->label == Not) {
        int lbl_true = _true_label++;
        int lbl_end = _if_label++;

        write_asm_condexp(root->firstChild, file, global_tab,tab_funks,funcname);
        fprintf(file,
            "  cmp rax, 0\n"
            "  je .Ltrue_%d\n", lbl_true);
        fprintf(file, "  mov rax, 0\n");
        fprintf(file, "  jmp .Lend_%d\n", lbl_end);
        fprintf(file, ".Ltrue_%d:\n", lbl_true);
        fprintf(file, "  mov rax, 1\n");
        fprintf(file, ".Lend_%d:\n", lbl_end);
        return;
    }
    if (root->label == Eq || root->label == Order) {
        write_asm_cmp_expr(root, file, global_tab,tab_funks,funcname);
        return;
    }
    if (root->label == Addsub || root->label == divstar) {
        parcours_expr_droite(root->firstChild, file, global_tab,tab_funks,funcname,1);
        parcours_expr_droite(root->firstChild->nextSibling, file, global_tab,tab_funks,funcname,1);
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
        } else if (strcmp(root->word, "%") == 0) {
            fprintf(file, "  xor rdx, rdx\n");
            fprintf(file, "  div rcx\n");
            fprintf(file, "  mov rax, rdx\n");
        }
        return;
    }
    if (root->label == ident) {
        gen_mov_var(file,root->word,funcname,global_tab,tab_funks,0);
        return;
    }
    if (root->label == Num) {
        fprintf(file, "  mov rax, %d\n", root->value);
        return;
    }
}


static void write_asm_if_test(Node* root, FILE* file, Symbol_table_global* global_tab,Symbol_table_functions* tab_funks, char* funcname) {
    cond_elem_count = 0;
    int else_label = _else_label;
    write_asm_condexp(root, file, global_tab,tab_funks,funcname);
    fprintf(file,
        "  cmp rax, 0\n"
        "  je  .Lelse_%d\n\n",  else_label);
}

static void write_static_labels(FILE* file, Symbol_table_functions* tab_funks) {
    if (!file || !tab_funks) return;
    for (int i = 0; i < tab_funks->index_tab; i++) {
        const char* funcname = tab_funks->tab_funcs[i].name;
        Symbol_table_locale* local_tab = tab_funks->tab_funcs[i].local_tab;
        for (int j = 0; j < local_tab->index_tab; j++) {
            if (local_tab->vars[j].isStatic) {
                const char* varname = local_tab->vars[j].name;
                const char* vartype = local_tab->vars[j].type;
                if (!strcmp(vartype, "int")) {
                    fprintf(file, "  static_%s_%s resd 1\n", funcname, varname);
                } else if (!strcmp(vartype, "char")) {
                    fprintf(file, "  static_%s_%s resb 1\n", funcname, varname);
                }
            }
        }
    }
}


void write_asm_tab_global_static(FILE* file,Symbol_table_global* global_tab,Symbol_table_functions* tab_funks){
    if (!file) {
        fprintf(stderr, "Erreur : fichier non existant\n");
        exit(EXIT_FAILURE);
    }
    int byte_global = get_total_global_size(global_tab);
    fprintf(file,"section .bss\n");
    fprintf(file, "  TAB_GLOBAL resb %d\n",byte_global);
    write_static_labels(file,tab_funks);

}
void write_asm_file_and_built_funcs(FILE *file) {
    if (!file) {
        fprintf(stderr, "Erreur : fichier non existant\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "global _start\n");
    fprintf(file, "section .text\n");
    fprintf(file,  "extern exit\n");
    fprintf(file,"\n");
    fprintf(file,"\n");
    fprintf(file,"\n");
    write_asm_getchar(file);
    write_asm_getint(file);
    write_asm_putchar(file);
    write_asm_putint(file);
    
    
}

static Data* get_func_params(Symbol_table_functions* tab, const char* funcname, int* nb_params) {
    if (!tab || !funcname) {
        if (nb_params) *nb_params = 0;
        return NULL;
    }
    for (int i = 0; i < tab->index_tab; i++) {
        if (strcmp(tab->tab_funcs[i].name, funcname) == 0) {
            if (nb_params) *nb_params = tab->tab_funcs[i].index_tabv;
            return tab->tab_funcs[i].vars;
        }
    }
    if (nb_params) *nb_params = 0;
    return NULL;
}



static void write_asm_func(FILE* file, const char* funcname, Symbol_table_functions* tab_funks) {
    if(funcname){
        fprintf(file, "%s:\n", funcname);
        fprintf(file, "  push rbp\n");
        fprintf(file, "  mov rbp, rsp\n");
        int total_local_offset = get_total_local_and_param_offset(tab_funks,funcname);
        if (total_local_offset > 0) {
            fprintf(file, "  sub rsp, %d\n", ((total_local_offset + 15) /16)* 16);
        }
        int nb_params = 0;
        Data* vars_params = get_func_params(tab_funks, funcname, &nb_params);
        int param_count = 0;
        while (vars_params && param_count < nb_params && param_count < 6){
            int offset = vars_params[param_count].offset;
            if (!strcmp(vars_params[param_count].type, "int")) {
                switch(param_count) {
                    case 0: fprintf(file, "  mov dword [rbp-%d], edi\n", offset); break;
                    case 1: fprintf(file, "  mov dword [rbp-%d], esi\n", offset); break;
                    case 2: fprintf(file, "  mov dword [rbp-%d], edx\n", offset); break;
                    case 3: fprintf(file, "  mov dword [rbp-%d], ecx\n", offset); break;
                    case 4: fprintf(file, "  mov dword [rbp-%d], r8d\n", offset); break;
                    case 5: fprintf(file, "  mov dword [rbp-%d], r9d\n", offset); break;
                }
            } else if (!strcmp(vars_params[param_count].type, "char")) {
                switch(param_count) {
                    case 0: fprintf(file, "  mov byte [rbp-%d], dil\n", offset); break;
                    case 1: fprintf(file, "  mov byte [rbp-%d], sil\n", offset); break;
                    case 2: fprintf(file, "  mov byte [rbp-%d], dl\n", offset); break;
                    case 3: fprintf(file, "  mov byte [rbp-%d], cl\n", offset); break;
                    case 4: fprintf(file, "  mov byte [rbp-%d], r8b\n", offset); break;
                    case 5: fprintf(file, "  mov byte [rbp-%d], r9b\n", offset); break;
                }
            }
            param_count++;
        }
        

        
    }
}



void write_end_asm_file(FILE *file) {
    fprintf(file, "_start:\n");
    fprintf(file, "  sub rsp, 8\n");
    fprintf(file, "  call main\n");
    fprintf(file, "  add rsp, 8\n");
    fprintf(file, "  mov rdi, rax\n");
    fprintf(file, "  mov rax, 60\n");   
    fprintf(file, "  syscall\n");       
}




static void parcours_instr_cond(Node* root, FILE* file,Symbol_table_global* global_tab,Symbol_table_functions* tab_funks, char* funcname){
    if(!root) return;
    if(root->label == SuiteInstr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                Node* ident_branch = branch_instr->firstChild;
                if(ident_branch->label == Arguments || ident_branch->label == Void){
                    parcours_expr_droite(branch_instr, file, global_tab,tab_funks,funcname, 0);
                    
                    
                } else {
                    char* str_ident = branch_instr->word;
                    Node* right_expr = branch_instr->firstChild;
                    if(right_expr){
                        parcours_expr_droite(right_expr,file,global_tab,tab_funks,funcname,0);
                        gen_mov_var(file,str_ident,funcname,global_tab,tab_funks,1);
                    }
                }
                
            } else if (branch_instr->label == If) {
                _else_label++;
                _if_label++;
                Node* cond = branch_instr->firstChild;
                Node* then_block  = branch_instr->firstChild->nextSibling;
                Node* else_block = branch_instr->nextSibling;
                if(cond->label == Exp){
                    write_asm_if_test(cond->firstChild, file, global_tab,tab_funks,funcname);
                }
                if(then_block->label == SuiteInstr){
                    parcours_instr_cond(then_block, file, global_tab,tab_funks,funcname);
                
                } 
                if(then_block->label == Return){
                    Node* expr = then_block->firstChild;
                    if (expr) {
                        parcours_expr_droite(expr, file, global_tab,tab_funks,funcname,0);
                    }
                    fprintf(file, "  leave\n"); 
                    fprintf(file, "  ret\n");
                }
                fprintf(file, "  jmp .Lend_if_%d\n\n", _if_label);
                fprintf(file, ".Lelse_%d:\n", _else_label);
                if (else_block->label == Else && else_block) {
                    parcours_instr_cond(else_block, file, global_tab,tab_funks,funcname);
                }
                fprintf(file, ".Lend_if_%d:\n\n", _if_label);
            } else if (branch_instr->label == Return) {
                Node* expr = branch_instr->firstChild;
                if (expr) {
                    parcours_expr_droite(expr, file, global_tab,tab_funks,funcname,0);
                 
                }
                fprintf(file, "  leave\n");
                fprintf(file, "  ret\n");
                return;
            } else if (branch_instr->label == While) {
                write_asm_while(branch_instr, file, global_tab, tab_funks, funcname);
            }
            branch_instr = branch_instr->nextSibling;

        } 
    } else if(root->label == Return){
            Node* expr = root->firstChild;
            if (expr) {
                parcours_expr_droite(expr, file, global_tab,tab_funks,funcname,0);
            }
            fprintf(file, "  leave\n");
            fprintf(file, "  ret\n");

    }
    parcours_instr_cond(root->firstChild,file,global_tab,tab_funks,funcname);
    parcours_instr_cond(root->nextSibling,file,global_tab,tab_funks,funcname);
}


static void write_asm_while(Node* root, FILE* file, Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname) {
    int lbl = while_label++;
    fprintf(file, ".Lwhile_start_%d:\n", lbl);
    Node* cond = root->firstChild;
    write_asm_condexp(cond->firstChild, file, global_tab, tab_funks, funcname);
    fprintf(file, "  cmp rax, 0\n");
    fprintf(file, "  je .Lwhile_end_%d\n", lbl);
    Node* body = cond->nextSibling;
    if (body && body->label == SuiteInstr) {
        parcours_instr_cond(body, file, global_tab, tab_funks, funcname);
    }
    fprintf(file, "  jmp .Lwhile_start_%d\n", lbl);
    fprintf(file, ".Lwhile_end_%d:\n", lbl);
}



static void parcours_corps_func(Node* root, FILE* file,Symbol_table_global* global_tab, Symbol_table_functions* tab_funks, char* funcname){
    if(!root) return;
    if(root->label == SuiteInstr){
        Node * branch_instr = root->firstChild;
        while(branch_instr){
            if(branch_instr->label == ident){
                Node* ident_branch = branch_instr->firstChild;
                if(ident_branch->label == Arguments || ident_branch->label == Void){
                    parcours_expr_droite(branch_instr, file, global_tab,tab_funks,funcname, 0);
                    
                    
                } else {
                    char* str_ident = branch_instr->word;
                    Node* right_expr = branch_instr->firstChild;
                    if(right_expr){
                        parcours_expr_droite(right_expr,file,global_tab,tab_funks,funcname,0);
                        gen_mov_var(file,str_ident,funcname,global_tab,tab_funks,1);

                    }

                   
                }
                
            } else if (branch_instr->label == If) {
                _else_label++;
                _if_label++;
                Node* cond = branch_instr->firstChild;
                Node* then_block  = branch_instr->firstChild->nextSibling;
                Node* else_block = branch_instr->nextSibling;
                if(cond->label == Exp){
                    write_asm_if_test(cond->firstChild, file, global_tab,tab_funks,funcname);
                }
                if(then_block->label == SuiteInstr){
                    parcours_instr_cond(then_block, file, global_tab,tab_funks,funcname);   
                }
                if (then_block->label == Return) {
    
                    Node* expr = then_block->firstChild;
                    if (expr) {
                        parcours_expr_droite(expr, file, global_tab,tab_funks,funcname,0);
                    }
                    fprintf(file, "  leave\n");
                    fprintf(file, "  ret\n");
                }
                fprintf(file, "  jmp .Lend_if_%d\n\n", _if_label);
                fprintf(file, ".Lelse_%d:\n", _else_label);
                if (else_block->label == Else && else_block) {
                    parcours_instr_cond(else_block, file, global_tab,tab_funks,funcname);
                }
                fprintf(file, ".Lend_if_%d:\n\n", _if_label);
            } else if (branch_instr->label == Return) {
                Node* expr = branch_instr->firstChild;
                if (expr) {
                    parcours_expr_droite(expr, file, global_tab,tab_funks,funcname,0);
                }
                fprintf(file, "  leave\n");
                fprintf(file, "  ret\n");
                return;
            } else if (branch_instr->label == While) {
                write_asm_while(branch_instr, file, global_tab, tab_funks, funcname);
            }
            branch_instr = branch_instr->nextSibling;

        }
        
    }
    parcours_corps_func(root->firstChild,file,global_tab,tab_funks,funcname);
    parcours_corps_func(root->nextSibling,file,global_tab,tab_funks,funcname);
}



void parcours_arbre(Node* root,FILE* file,Symbol_table_global* global_tab,Symbol_table_functions* tab_funks) {
    if (!root) return;
    if(root->label == DeclFonct){
        Node* branch_func_name;
        Node* corps_fonc;
        Node* isVoid = root->firstChild;
        if(isVoid->label == Void){
            Node* branch_func_name = isVoid->firstChild;
            Node* corps_fonc = root->firstChild->nextSibling->nextSibling;
            if(corps_fonc){
                write_asm_func(file,branch_func_name->word,tab_funks);
                parcours_corps_func(corps_fonc,file,global_tab,tab_funks,branch_func_name->word);
            }
        } else {
            branch_func_name = root->firstChild->firstChild->nextSibling;
            corps_fonc = root->firstChild->nextSibling->nextSibling;
            if(branch_func_name){
                write_asm_func(file,branch_func_name->word,tab_funks);
                parcours_corps_func(corps_fonc,file,global_tab,tab_funks,branch_func_name->word);
            }
        }
        
    } 
    parcours_arbre(root->firstChild,file,global_tab,tab_funks);
    parcours_arbre(root->nextSibling,file,global_tab,tab_funks);
}


