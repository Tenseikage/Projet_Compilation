section .bss
  TAB_GLOBAL resb 27
global _start
section .text
extern show_registers
extern exit



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
  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  push 14
  pop rcx
  pop rax
  add rax, rcx
  push rax

  pop rax
  mov [TAB_GLOBAL + 0], eax

  push 0
  pop rax
  ret
main:
  push 24

  pop rax
  mov [TAB_GLOBAL + 4], eax

  push 24
  push 12
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  push rax

  pop rax
  mov [TAB_GLOBAL + 8], eax

  mov al, 'c' 
  push rax 

  pop rax
  mov [TAB_GLOBAL + 20], eax

  mov al, '0' 
  push rax 

  pop rax
  mov [TAB_GLOBAL + 21], eax

  mov eax, dword [TAB_GLOBAL + 20]
  push rax 
  mov al, 'A' 
  push rax 
  mov al, 'a' 
  push rax 
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  push rax

  pop rax
  mov [TAB_GLOBAL + 23], eax

  mov eax, dword [TAB_GLOBAL + 4]
  push rax 
  push 24
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  push 1
  pop rcx
  pop rax
  add rax, rcx
  cmp rax, 0
  je .Ltrue_1
  mov rax, 0
  jmp .Lend_2
.Ltrue_1:
  mov rax, 1
.Lend_2:
  cmp rax, 0
  jne .Ltrue_0
  mov rax, 1
  cmp rax, 0
  je .Lfalse_0
  mov rax, 0
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  jmp .Lend_3
.Lfalse_0:
  mov rax, 0
.Lend_3:
  cmp rax, 0
  jne .Ltrue_0
  mov rax, 0
  jmp .Lend_1
.Ltrue_0:
  mov rax, 1
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov eax, dword [TAB_GLOBAL + 4]
  push rax 
  push 24
  pop rcx            ; rhs
  pop rax            ; lhs
  cmp rax, rcx       ; comparer lhs vs rhs
  je .Ltrue_4
  jmp .Lfalse_1
.Ltrue_4:
  mov rax, 1
  jmp .Lend_6
.Lfalse_1:
  mov rax, 0
  cmp rax, 0
  je  .Lelse_1

.Lend_6:
  cmp rax, 0
  jne .Ltrue_3
  mov eax, dword [TAB_GLOBAL + 12]
  push rax 
  push 58
  pop rcx            ; rhs
  pop rax            ; lhs
  cmp rax, rcx       ; comparer lhs vs rhs
  jg .Ltrue_5
  jmp .Lfalse_2
.Ltrue_5:
  mov rax, 1
  jmp .Lend_7
.Lfalse_2:
  mov rax, 0
  cmp rax, 0
  je  .Lelse_1

.Lend_7:
  cmp rax, 0
  jne .Ltrue_3
  mov rax, 0
  jmp .Lend_5
.Ltrue_3:
  mov rax, 1
.Lend_5:
  cmp rax, 0
  je .Ltrue_2
  mov rax, 0
  jmp .Lend_4
.Ltrue_2:
  mov rax, 1
.Lend_4:
  push rax

  pop rax
  mov [TAB_GLOBAL + 12], eax

  jmp .Lend_if_8

.Lelse_1:
  push 4

  pop rax
  mov [TAB_GLOBAL + 12], eax

.Lend_if_8:

  mov rdi, 10
  call putchar
  mov edi, [TAB_GLOBAL + 12]
  call putint
  mov rdi, 10
  call putchar
  push 0
  pop rax
  ret
_start:
  sub rsp, 8
  call main
  add rsp, 8
  mov rax, 60
  xor rdi, rdi
  syscall
