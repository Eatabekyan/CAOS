.global _start
.intel_syntax noprefix

_start:
  push    rbp
  mov     rbp, rsp
  sub     rsp, 16
Read:
  // 0	Read	sys_Read
  mov rax, 0
  mov rdi, 0
  mov rsi, rsp
  mov rdx, 1
  syscall
  
  cmp rax, 0
  jne     Write
  
  // 60	exit	sys_exit
  mov rax, 60
  syscall

  
  
Write:
  // 1	Write	sys_Write
  mov rax, 1
  mov rdi, 1
  mov rsi, rsp
  mov rdx, 1
  syscall
  jmp     Read
    
