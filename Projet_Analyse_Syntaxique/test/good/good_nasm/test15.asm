section .bss
  TAB_GLOBAL resb 9
  static_main_d resd 1
  static_main_c resb 1
  static_main_n resb 1
global _start
section .text
extern exit

; Mauvaise gestion des entiers signés (unsigned int ?)

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
add:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-8]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  leave
  ret
sub:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-8]
  push rax 
  pop rcx
  pop rax
  sub rax, rcx
  leave
  ret
main:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov rax, 258
  mov dword [rbp-12], eax
  mov rax, 23
  mov dword [rbp-16], eax
  mov eax, dword [rbp-12]
  mov rdi, rax
  mov eax, dword [rbp-16]
  mov rsi, rax
  sub rsp, 8
  call add
  add rsp, 8
  mov dword [static_main_d], eax
  mov al, 100 
  mov byte [static_main_c], al
  mov al, 100 
  mov byte [static_main_n], al
  mov al, byte [static_main_c]
  push rax 
  mov al, byte [static_main_n]
  push rax 
  pop rcx
  pop rax
  cmp rax, rcx
  jne .Ltrue_1
  jmp .Lfalse_0
.Ltrue_1:
  mov rax, 1
  jmp .Lend_2
.Lfalse_0:
  mov rax, 0
.Lend_2:
  cmp rax, 0
  je .Ltrue_0
  mov rax, 0
  jmp .Lend_1
.Ltrue_0:
  mov rax, 1
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov eax, dword [static_main_d]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov rax, 1
  leave
  ret
  jmp .Lend_if_3

.Lelse_1:
.Lend_if_3:

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
