global _start
section .text
extern show_registers
_start:
  push 25
  push 32
  pop rcx
  pop rax
  add rax, rcx
  push rax
  push 10
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  mov rbx, rcx 
  mov r12, rax 
  call show_registers
  pop rdi
  mov rax, 60
  syscall
