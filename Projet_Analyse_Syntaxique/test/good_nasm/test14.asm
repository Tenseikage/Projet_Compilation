section .bss
  TAB_GLOBAL resb 16
  static_main_q resd 1
global _start
section .text
extern exit

; Affiche des caractères (affichage étrange)

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
babidi:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov rax, 0
  leave
  ret
dababy:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov rax, 2
  push rax
  mov al, 99 
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  mov byte [rbp-12], al
  mov rax, 1
  mov dword [rbp-8], eax
  mov al, byte [rbp-12]
  mov rdi, rax
  sub rsp, 8
  call putchar
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  leave
  ret
zbilzbil:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  sub rsp, 8
  call getint
  add rsp, 8
  mov dword [rbp-13], eax
  sub rsp, 8
  call getint
  add rsp, 8
  mov dword [rbp-17], eax
  mov rax, 128
  push rax
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  mov eax, dword [rbp-13]
  push rax 
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_0
  jmp .Lfalse_2
.Ltrue_0:
  mov rax, 1
  jmp .Lend_3
.Lfalse_2:
  mov rax, 0
.Lend_3:
  cmp rax, 0
  je .Lfalse_1
  mov eax, dword [rbp-13]
  push rax 
  mov rax, 128
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_1
  jmp .Lfalse_3
.Ltrue_1:
  mov rax, 1
  jmp .Lend_4
.Lfalse_3:
  mov rax, 0
.Lend_4:
  cmp rax, 0
  je .Lfalse_1
  mov rax, 1
  jmp .Lend_2
.Lfalse_1:
  mov rax, 0
.Lend_2:
  cmp rax, 0
  je .Lfalse_0
  mov rax, 128
  push rax
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  mov eax, dword [rbp-17]
  push rax 
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_2
  jmp .Lfalse_5
.Ltrue_2:
  mov rax, 1
  jmp .Lend_6
.Lfalse_5:
  mov rax, 0
.Lend_6:
  cmp rax, 0
  je .Lfalse_4
  mov eax, dword [rbp-17]
  push rax 
  mov rax, 128
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_3
  jmp .Lfalse_6
.Ltrue_3:
  mov rax, 1
  jmp .Lend_7
.Lfalse_6:
  mov rax, 0
.Lend_7:
  cmp rax, 0
  je .Lfalse_4
  mov rax, 1
  jmp .Lend_5
.Lfalse_4:
  mov rax, 0
.Lend_5:
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  jmp .Lend_1
.Lfalse_0:
  mov rax, 0
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov eax, dword [rbp-13]
  mov rdi, rax
  sub rsp, 8
  call putchar
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov eax, dword [rbp-17]
  mov rdi, rax
  sub rsp, 8
  call putchar
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  jmp .Lend_if_8

.Lelse_1:
  mov eax, dword [rbp-13]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov eax, dword [rbp-17]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  leave
  ret
.Lend_if_8:

  leave
  ret
tactical_doggo:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov rax, 97
  leave
  ret
main:
  push rbp
  mov rbp, rsp
  mov rax, 1
  mov [TAB_GLOBAL + 0], eax
  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  mov rax, 2
  push rax
  pop rcx
  pop rax
  imul rax, rcx
  mov [TAB_GLOBAL + 4], eax
  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  mov eax, dword [TAB_GLOBAL + 4]
  push rax 
  mov rax, 2
  push rax
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov [TAB_GLOBAL + 8], eax
  mov rax, 1
  mov dword [static_main_q], eax
  sub rsp, 8
  call zbilzbil
  add rsp, 8
  mov rax, 1
  mov rdi, rax
  mov rax, 2
  mov rsi, rax
  sub rsp, 8
  call tactical_doggo
  add rsp, 8
  mov rdi, rax
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
_start:
  sub rsp, 8
  call main
  add rsp, 8
  mov rdi, rax
  mov rax, 60
  syscall
