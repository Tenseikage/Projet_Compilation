section .bss
  TAB_GLOBAL resb 27
global _start
section .text
extern show_registers
extern exit



getchar:
    sub rsp, 8
    mov rax, 0          ; syscall read
    mov rdi, 0          ; stdin
    mov rsi, rsp        ; buffer
    mov rdx, 1
    syscall
    pop rax             ; récupérer caractère
    ret
getint:
    mov rbx, 0          ; accumulateur
    mov r8, 1           ; signe positif par défaut
.boucle_getint:
    call getchar
    mov rcx, rax
    cmp rcx, 10         ; saut de ligne ?
    je .fin_getint
    cmp rcx, '-'
    je .negatif_getint
    cmp rcx, '0'
    jl .erreur_getint
    cmp rcx, '9'
    jg .erreur_getint
    sub rcx, '0'
    imul rbx, 10
    add rbx, rcx
    jmp .boucle_getint
.negatif_getint:
    mov r8, -1
    jmp .boucle_getint
.fin_getint:
    imul rbx, r8
    mov rax, rbx
    ret
.erreur_getint:
    mov rdi, 5
    call exit
putchar:
    sub rsp, 8
    mov [rsp], dil      ; écrire 1 octet
    mov rax, 1          ; syscall write
    mov rdi, 1          ; stdout
    mov rsi, rsp        ; adresse du caractère
    mov rdx, 1          ; taille (1 octet)
    syscall
    add rsp, 8
    ret
putint:
    push rbx
    push r12
    mov rax, rdi
    mov rcx, 10
    xor rbx, rbx        ; compteur de chiffres
    mov r12, rsp        ; sauvegarde pile
    cmp rax, 0
    jge .convert
    mov rdi, '-'
    call putchar
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
    call putchar
    dec rbx
    jnz .print_loop
    pop r12
    pop rbx
    ret
_start:
  push 12

  pop rax
  mov [TAB_GLOBAL + 0], eax

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

  sub rsp, 8
  call getint
  add rsp, 8
  push rax

  pop rax
  mov [TAB_GLOBAL + 12], eax

  mov rdi, 10
  call putchar
  mov rax, 60
  xor rdi, rdi
  syscall
