section .bss
  TAB_GLOBAL resb 8
  static_add_q resd 1
  static_poppi_c resd 1
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
add:
  push rbp
  mov rbp, rsp
  sub rsp, 32
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov dword [rbp-12], edx
  mov dword [rbp-16], ecx
  mov dword [rbp-20], r8d
  mov byte [rbp-24], r9b
  mov al, 99 
  mov byte [rbp-25], al
  mov eax, dword [rbp-4]
  push rax 
  mov eax, dword [rbp-8]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov eax, dword [rbp-12]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov eax, dword [rbp-16]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov eax, dword [rbp-20]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov al, byte [rbp-24]
  push rax 
  pop rcx
  pop rax
  add rax, rcx
  mov dword [rbp-4], eax
  mov rax, 1
  mov dword [static_add_q], eax
  mov eax, dword [rbp-4]
  mov rdi, rax
  sub rsp, 8
  call putint
  add rsp, 8
  mov rax, 0
  leave
  ret
blab:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov byte [rbp-1], dil
  mov al, 97 
  mov byte [rbp-2], al
  mov al, byte [rbp-1]
  leave
  ret
poppi:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov dword [rbp-4], edi
  mov dword [rbp-8], esi
  mov rax, 1
  cmp rax, 0
  je  .Lelse_1

  mov rax, 2
  push rax
  mov rax, 3
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov dword [static_poppi_c], eax
  jmp .Lend_if_1

.Lelse_1:
  mov dil,113
  sub rsp, 8
  call putchar
  add rsp, 8
.Lend_if_1:

  mov rax, 0
  leave
  ret
main:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov rax, 1
  mov rdi, rax
  mov rax, 2
  mov rsi, rax
  mov rax, 3
  mov rdx, rax
  mov rax, 4
  mov rcx, rax
  mov rax, 5
  mov r8, rax
  mov rax, 6
  mov r9, rax
  sub rsp, 8
  call add
  add rsp, 8
  mov [TAB_GLOBAL + 0], eax
  mov rax, 1
  push rax
  mov rax, 2
  push rax
  mov rax, 3
  push rax
  pop rcx
  pop rax
  imul rax, rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov rax, 4
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov [TAB_GLOBAL + 4], eax
  mov dil,10
  sub rsp, 8
  call putchar
  add rsp, 8
  mov rax, 1
  mov rdi, rax
  mov rax, 2
  mov rsi, rax
  sub rsp, 8
  call poppi
  add rsp, 8
  mov al, 98 
  mov rdi, rax
  sub rsp, 8
  call blab
  add rsp, 8
  mov byte [rbp-12], al
  mov al, byte [rbp-12]
  mov rdi, rax
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
