global _start
section .text
extern show_registers
_start:
  push 25
  push 32
  pop r12
  pop rbx
  add rbx, r12
  push rbx
  push 10
  pop r12
  pop rbx
  sub rbx, r12
  push rbx
  call show_registers
  pop rdi
  mov rax, 60
  syscall
