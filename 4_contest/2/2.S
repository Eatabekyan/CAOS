  .data
  value:
    .word 0
  .text 
  .global main 

main: 
  sub sp, sp, 16 
  str x30, [sp, 8] 

read: 
  bl getchar_unlocked 
  cmp x0, value
  blt end

find:
  cmp x0, 57 
  bgt read 
  cmp x0, 48 
  blt read 

  bl putchar_unlocked 
  b read 
end: 
  ldr x30, [sp, 8] 
  add sp, sp, 16 
  ret
