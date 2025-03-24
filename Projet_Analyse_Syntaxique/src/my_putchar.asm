section .data
section .text
global _start
extern show_registers

getchar:
    sub rsp, 8
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp 
    mov rdx, 1
    syscall
    pop rax    
    ret

putchar:
    push rbx
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall 
    pop rbx
    ret

_start :
    call getchar
    mov rbx, rax
    call putchar
    mov rbx, 10
    call putchar
    mov rax, 60
    mov rdi, 0
    syscall