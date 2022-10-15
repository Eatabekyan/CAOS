	.text
	.global	sum
sum:
	mov    x3, #0
	mov    x4, x1
Start:
	cmp    x3, x4     // сравниваем  
  bge    End    // переходим в конец цикла, если x0 >= x1
	ldr    w10, [x2]
	add    w0, w0, w10
	add    x2, x2, #4
  add    x3, x3, #1
	b      Start
End:
	ret