section .bss
  TAB_GLOBAL resb 8
  static_main_m resd 1
  static_main_c resd 1
global _start
section .text
extern exit

; Multiple expressions booléennes

getchar:
    sub rsp, 8
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 1
    syscall
    movzx rax, byte [rsp]
    add rsp, 8
    ret
getint:
    xor rbx, rbx
    mov r8, 1
    call getchar
    cmp rax, -1
    je .erreur_getint
    cmp rax, '-'
    je .set_neg
    cmp rax, '0'
    jb .erreur_getint
    cmp rax, '9'
    ja .erreur_getint
    jmp .read_digits_first_char
.set_neg:
    mov r8, -1
    call getchar
    cmp rax, -1
    je .erreur_getint
    cmp rax, '0'
    jb .erreur_getint
    cmp rax, '9'
    ja .erreur_getint
.read_digits_first_char:
    sub rax, '0'
    mov rbx, rax
.read_digits_loop:
    call getchar
    cmp rax, '0'
    jb .end_read_digits
    cmp rax, '9'
    ja .end_read_digits
    sub rax, '0'
    imul rbx, 10
    add rbx, rax
    jmp .read_digits_loop
.end_read_digits:
    imul rbx, r8
    mov rax, rbx
    ret
.erreur_getint:
    mov rdi, 5
    call exit
putchar:
    sub rsp, 8
    mov [rsp], dil
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    add rsp, 8
    ret
putint:
    push rbx
    push r12
    mov rax, rdi
    mov rcx, 10
    xor rbx, rbx
    mov r12, rsp
    cmp rax, 0
    jge .convert
    mov rdi, '-'
    call putchar
    neg rax
.convert:
.convert_loop:
    xor rdx, rdx
    div rcx
    add dl, '0'
    push rdx
    inc rbx
    test rax, rax
    jnz .convert_loop
.print_loop:
    pop rdi
    call putchar
    dec rbx
    jnz .print_loop
    pop r12
    pop rbx
    ret
main:
  push rbp
  mov rbp, rsp
  mov rax, 1
  mov [TAB_GLOBAL + 0], eax
  mov rax, 52
  mov [TAB_GLOBAL + 4], eax
  mov rax, 954
  mov dword [static_main_c], eax
  mov rax, 0
  mov dword [static_main_m], eax
  mov eax, dword [static_main_m]
  cmp rax, 0
  jne .Ltrue_1
  mov eax, dword [TAB_GLOBAL + 0]
  cmp rax, 0
  jne .Ltrue_1
  mov rax, 0
  jmp .Lend_3
.Ltrue_1:
  mov rax, 1
.Lend_3:
  cmp rax, 0
  je .Ltrue_0
  mov rax, 0
  jmp .Lend_2
.Ltrue_0:
  mov rax, 1
.Lend_2:
  cmp rax, 0
  je .Lfalse_0
  mov eax, dword [static_main_c]
  cmp rax, 0
  je .Ltrue_3
  mov rax, 0
  jmp .Lend_5
.Ltrue_3:
  mov rax, 1
.Lend_5:
  cmp rax, 0
  jne .Ltrue_2
  mov eax, dword [TAB_GLOBAL + 4]
  cmp rax, 0
  jne .Ltrue_2
  mov rax, 0
  jmp .Lend_4
.Ltrue_2:
  mov rax, 1
.Lend_4:
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  jmp .Lend_1
.Lfalse_0:
  mov rax, 0
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov dil,112
  sub rsp, 8
  call putchar
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  jmp .Lend_if_6

.Lelse_1:
  mov dil,115
  sub rsp, 8
  call putchar
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov rax, 0
  leave
  ret
.Lend_if_6:

  mov rax, 0
  leave
  ret
_start:
  sub rsp, 8
  call main
  add rsp, 8
  mov rdi, rax
  mov rax, 60
  syscall
