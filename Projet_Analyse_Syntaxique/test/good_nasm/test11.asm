section .bss
  TAB_GLOBAL resb 0
  static_main_a resd 1
  static_main_c resb 1
global _start
section .text
extern exit

; Écrit sur la sortie standard en minuscules

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
to_lower:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov byte [rbp-1], dil
  mov al, byte [rbp-1]
  push rax 
  mov al, 65 
  push rax 
  pop rcx
  pop rax
  cmp rax, rcx
  jge .Ltrue_0
  jmp .Lfalse_1
.Ltrue_0:
  mov rax, 1
  jmp .Lend_2
.Lfalse_1:
  mov rax, 0
.Lend_2:
  cmp rax, 0
  je .Lfalse_0
  mov al, byte [rbp-1]
  push rax 
  mov al, 90 
  push rax 
  pop rcx
  pop rax
  cmp rax, rcx
  jle .Ltrue_1
  jmp .Lfalse_2
.Ltrue_1:
  mov rax, 1
  jmp .Lend_3
.Lfalse_2:
  mov rax, 0
.Lend_3:
  cmp rax, 0
  je .Lfalse_0
  mov rax, 1
  jmp .Lend_1
.Lfalse_0:
  mov rax, 0
.Lend_1:
  cmp rax, 0
  je  .Lelse_1

  mov al, byte [rbp-1]
  push rax 
  mov al, 97 
  push rax 
  mov al, 65 
  push rax 
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  leave
  ret
  jmp .Lend_if_4

.Lelse_1:
  mov al, byte [rbp-1]
  leave
  ret
.Lend_if_4:

main:
  push rbp
  mov rbp, rsp
  mov rax, 0
  mov dword [static_main_a], eax
.Lwhile_start_0:
  mov eax, dword [static_main_a]
  push rax 
  mov rax, 64
  push rax
  pop rcx
  pop rax
  cmp rax, rcx
  jl .Ltrue_2
  jmp .Lfalse_3
.Ltrue_2:
  mov rax, 1
  jmp .Lend_4
.Lfalse_3:
  mov rax, 0
.Lend_4:
  cmp rax, 0
  je .Lwhile_end_0
  sub rsp, 8
  call getchar
  add rsp, 8
  mov byte [static_main_c], al
  mov al, byte [static_main_c]
  mov rdi, rax
  sub rsp, 8
  call to_lower
  add rsp, 8
  mov byte [static_main_c], al
  mov al, byte [static_main_c]
  mov rdi, rax
  sub rsp, 8
  call putchar
  add rsp, 8
  mov eax, dword [static_main_a]
  push rax 
  mov rax, 1
  push rax
  pop rcx
  pop rax
  add rax, rcx
  mov dword [static_main_a], eax
  jmp .Lwhile_start_0
.Lwhile_end_0:
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
