.text
.global main
main:
  sub sp, sp, 16 
  str x30, [sp, 8] 
  mov	x0, 0
	mov	x1, 51
	bl	realloc	
	mov	x3, 2
	mov	x5, x0
	mov	x6, 0
	mov	x4, 51
read:
  bl getchar_unlocked

	cmp	x0, -1
	beq	reve

	str	x0, [x5, x6]
	add	x6, x6, 1	

	cmp	x6, x4		// r6 <= 51
	blo	read

	mov	x0, x5		// r0 = r5
	mul	x1, x4, x3	// r1 = r4 * 2
	mov	x4, x1		// r4 *= 2
	bl	realloc		// r0 = realloc(r5, 2 * r4)
	mov	x5, x0		// r5 = r0
	b	read
reve:
  cmp x6, 0
  beq fin
  sub x6, x6, 1
  ldr x0, [x5,x6]
  bl putchar_unlocked
  b reve
fin:
  mov x0, x5
  bl free
  ldr x30, [sp, 8] 
  add sp, sp, 16 
  ret
