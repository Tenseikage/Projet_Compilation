section .text
global getint
;extern show_registers

extern getchar

extern exit

fin:
    imul rbx, r8
    mov rax, rbx
    ret

erreur:
   mov rdi, 5
   call exit

negatif:
    mov r8, -1
    jmp boucle

boucle:
    call getchar
    mov rcx, rax
    cmp rcx, '-'
    je negatif
    cmp rcx, '0'
    jl erreur
    cmp rcx, '9'
    jg erreur
    sub rcx, 48
    imul rbx, 10
    add rbx, rcx
    jmp boucle

getint:
    mov rbx, 0
    mov r8, 1
    jmp boucle


;_start:
    ;call getint
    ;mov rdi, rax
    ;call show_registers
    ;mov rdi, 0
    ;call exit