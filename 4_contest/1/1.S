.data 
Number1: 
    .word 0
Number2: 
    .word 0
scan_fmt: 
    .string "%d %d" 
print_fmt: 
    .string "%d\n" 

.text 
.global main 
main: 
  sub sp, sp, 16
  str x30, [sp]

  adr    x0, scan_fmt 
  adr    x1,  Number1
  adr    x2,  Number2
  bl scanf 

  adr    x1,  Number1
  ldr    x1, [x1] 
  adr    x2,  Number2 
  ldr    x2, [x2]

  add    x1, x1, x2

  adr    x0, print_fmt
  bl     printf
  
  ldr x30, [sp] 
  add sp, sp, 16
  
  ret
