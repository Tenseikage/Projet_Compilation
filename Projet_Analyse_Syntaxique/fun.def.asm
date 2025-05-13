; default code;
; use make and edit fun.asm

section .text
global my_getchar
global my_putchar
global my_getint
global my_putint

extern exit

my_getchar:
    sub rsp, 8
    mov rax, 0          ; syscall read
    mov rdi, 0          ; stdin
    mov rsi, rsp        ; buffer pointe vers pile
    mov rdx, 1          ; lire 1 octet
    syscall
    movzx rax, byte [rsp]  ; lire le caractère (0-étendu à 64 bits)
    add rsp, 8
    ret
my_getint:
    xor rbx, rbx        ; accumule le nombre dans rbx
    mov r8, 1           ; signe = +1

    call my_getchar
    cmp rax, -1
    je .erreur

    cmp rax, '-'        ; si signe moins
    je .set_neg

    cmp rax, '0'        ; si chiffre entre 0 et 9
    jb .erreur
    cmp rax, '9'
    ja .erreur

    jmp .read_digits_first_char

.set_neg:
    mov r8, -1
    call my_getchar
    cmp rax, -1
    je .erreur
    cmp rax, '0'
    jb .erreur
    cmp rax, '9'
    ja .erreur

.read_digits_first_char:
    sub rax, '0'
    mov rbx, rax

.read_loop:
    call my_getchar
    cmp rax, -1
    je .done
    cmp rax, '0'
    jb .done
    cmp rax, '9'
    ja .done
    sub rax, '0'
    imul rbx, 10
    add rbx, rax
    jmp .read_loop

.done:
    imul rbx, r8
    mov rax, rbx
    ret

.erreur:
    mov rdi, 5          ; code erreur
    mov rax, 60         ; syscall exit
    syscall


my_putchar:
    sub rsp, 8
    mov [rsp], dil      ; écrire 1 octet
    mov rax, 1          ; syscall write
    mov rdi, 1          ; stdout
    mov rsi, rsp        ; adresse du caractère
    mov rdx, 1          ; taille (1 octet)
    syscall
    add rsp, 8
    ret
my_putint:
    push rbx
    push r12
    mov rax, rdi
    mov rcx, 10
    xor rbx, rbx        ; compteur de chiffres
    mov r12, rsp        ; sauvegarde pile
    cmp rax, 0
    jge .convert
    mov rdi, '-'
    call my_putchar
    neg rax
.convert:
.convert_loop:
    xor rdx, rdx
    div rcx             ; rax / 10, reste dans rdx
    add dl, '0'
    push rdx
    inc rbx
    test rax, rax
    jnz .convert_loop
.print_loop:
    pop rdi
    call my_putchar
    dec rbx
    jnz .print_loop
    pop r12
    pop rbx
    ret
