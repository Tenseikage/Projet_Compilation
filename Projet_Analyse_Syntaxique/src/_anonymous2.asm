section .bss
  TAB_GLOBAL resb 12
global _start
section .text
extern show_registers
_start:
  push 1

  pop rax
  mov [TAB_GLOBAL + 0], rax

  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  push 2
  pop rcx
  pop rax
  imul rax, rcx
  push rax

  pop rax
  mov [TAB_GLOBAL + 4], rax

  mov eax, dword [TAB_GLOBAL + 0]
  push rax 
  mov eax, dword [TAB_GLOBAL + 4]
  push rax 
  push 2
  pop rcx
  pop rax
  xor rdx, rdx
  div rcx
  push rax
  pop rcx
  pop rax
  add rax, rcx
  push rax

  pop rax
  mov [TAB_GLOBAL + 8], rax
  mov ebx, dword [TAB_GLOBAL]
  mov r12d, dword [TAB_GLOBAL + 4]
  mov r13d, dword [TAB_GLOBAL + 8]
  sub rsp,8
  call show_registers
  add rsp,8
  mov rax, 60
  xor rdi, rdi
  syscall
