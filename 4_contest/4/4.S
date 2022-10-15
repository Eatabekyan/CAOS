.text
.global main
main:
  mov x0, 0
  mov x1, 1
  bl realloc

  mov x5, x0
  mov x6, 0

  sub sp, sp, 16 
  str x30, [sp, 8] 
read:
  bl getchar_unlocked
  cmp x0, 0
  blt rev
  str x0, [x5, x6]
  add x6, x6, 1
  mov x0, x5
  mov x1, x6
  bl realloc
  mov x5, x0
  b read
rev:
  sub x6, x6, 1
  cmp x6, 0
  blt fin
  ldr x0, [x5,x6]
  bl putchar_unlocked
  b rev
fin:
  bl free
  ldr x30, [sp, 8] 
  add sp, sp, 16 
  ret


