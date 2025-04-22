global _start
section .text
extern show_registers
_start:
  push 0
  push 97
  push 6
  pop rcx
  pop rax
  add rax, rcx
  push rax
  pop rcx
  pop rax
  sub rax, rcx
  push rax
  push 14
  push 15
  pop rcx
  pop rax
  add rax, rcx
  push rax
  push 16
  pop rcx
  pop rax
  add rax, rcx
  push rax
  mov rbx, rcx 
  mov r12, rax 
  call show_registers
  pop rdi
  mov rax, 60
  syscall
