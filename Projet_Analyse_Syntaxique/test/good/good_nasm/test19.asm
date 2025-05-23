section .bss
  TAB_GLOBAL resb 22
global _start
section .text
extern exit

; test 21 good

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
magma:
  push rbp
  mov rbp, rsp
  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  mov rax, 14
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov [TAB_GLOBAL + 0], eax
  mov eax, dword [TAB_GLOBAL + 0]
  cmp rax, 0
  je  .Lelse_1

  mov rax, 15
  mov [TAB_GLOBAL + 0], eax
  mov eax, dword [TAB_GLOBAL + 0]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  jmp .Lend_if_1

.Lelse_1:
.Lend_if_1:

  mov rax, 0
  leave
  ret
baba:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov rax, 0
  mov dword [rbp-8], eax
  mov eax, dword [rbp-4]
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  jmp .Lend_2
.Lfalse_0:
  mov rax, 0
.Lend_2:
  cmp rax, 0
  je  .Lelse_2

  mov eax, dword [rbp-4]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  jmp .Lend_if_3

.Lelse_2:
.Lend_if_3:

.Lwhile_start_0:
  mov eax, dword [rbp-8]
  push rax 
  mov rax, 5
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_0
  jmp .Lfalse_1
.Ltrue_0:
  mov rax, 1
  jmp .Lend_3
.Lfalse_1:
  mov rax, 0
.Lend_3:
  cmp rax, 0
  je .Lwhile_end_0
  mov rax, 5
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov eax, dword [rbp-8]
  push rax 
  mov rax, 1
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov dword [rbp-8], eax
  jmp .Lwhile_start_0
.Lwhile_end_0:
  mov rax, 0
  leave
  ret
main:
  push rbp
  mov rbp, rsp
  mov rax, 24
  mov [TAB_GLOBAL + 4], eax
  mov rax, 24
  push rax
  mov rax, 12
  push rax
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  mov [TAB_GLOBAL + 8], eax
  mov al, 99 
  mov byte [TAB_GLOBAL + 16], al
  mov al, 48 
  mov byte [TAB_GLOBAL + 17], al
  mov al, byte [TAB_GLOBAL + 16]
  push rax 
  mov al, 65 
  push rax 
  mov al, 97 
  push rax 
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov [TAB_GLOBAL + 18], eax
  mov rax, 1
  cmp rax, 0
  je  .Lelse_3

  mov dil,99
  sub rsp, 8
  call putchar
  add rsp, 8
  jmp .Lend_if_5

.Lelse_3:
.Lend_if_5:

  sub rsp, 8
  call getint
  add rsp, 8
  mov [TAB_GLOBAL + 12], eax
  sub rsp, 8
  call magma
  add rsp, 8
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov eax, dword [TAB_GLOBAL + 12]
  mov rdi, rax
  sub rsp, 8
  call putint
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
