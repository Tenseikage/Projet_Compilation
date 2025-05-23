section .bss
  TAB_GLOBAL resb 4
global _start
section .text
extern exit

; Comparaison presque equivalente

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
  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  mov rax, 1
  push rax
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov rax, 2
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  jle .Ltrue_0
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
  mov rax, 1
  leave
  ret
.Lend_if_2:

  mov rax, 0
  leave
  ret
  mov rax, 1
  leave
  ret
_start:
  sub rsp, 8
  call main
  add rsp, 8
  mov rdi, rax
  mov rax, 60
  syscall
