section .bss
  TAB_GLOBAL resb 12
global _start
section .text
extern show_registers
_start:
  push 235
  pop rax
  mov dword [TAB_GLOBAL + 0], eax
  push 53
  pop rax
  mov dword [TAB_GLOBAL + 4], eax
  mov rbx, qword [TAB_GLOBAL]
  mov r12, qword [TAB_GLOBAL + 4]
  sub rsp,8
  call show_registers
  add rsp,8
  ;sub rsp, 8
  mov rax, 60
  xor rdi, rdi
  syscall
  ;add rsp, 8
