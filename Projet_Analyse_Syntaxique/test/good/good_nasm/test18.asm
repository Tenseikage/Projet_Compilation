section .bss
  TAB_GLOBAL resb 9
  static_main_d resd 1
  static_main_c resb 1
  static_main_n resb 1
global _start
section .text
extern exit

; modulo spécial

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
mod:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov eax, dword [rbp-8]
  push rax 
  mov rax, 0
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  je .Ltrue_0
  jmp .Lfalse_0
.Ltrue_0:
  mov rax, 1
  jmp .Lend_1
.Lfalse_0:
  mov rax, 0
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov rax, 0
  leave
  ret
  jmp .Lend_if_2

.Lelse_1:
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-8]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  mov rax, rdx
  leave
  ret
.Lend_if_2:

  mov rax, 0
  leave
  ret
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-8]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  mov rax, rdx
  leave
  ret
main:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov eax, dword [static_main_d]
  push rax 
  mov rax, 5
  mov rdi, rax
  mov rax, 4
  mov rsi, rax
  sub rsp, 8
  call mod
  add rsp, 8
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov dword [static_main_d], eax
  mov eax, dword [static_main_d]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
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
