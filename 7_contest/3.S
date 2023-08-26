    .intel_syntax noprefix
    .global _start
    
_start:
  // устанавливаем конец сегмента данных в значение укаанное в аргументе end_data_segment
  //kogda это  значемие является приемлемым,система симулирует нехватку памяти.
    mov rax, 12
    syscall 
  // берем насколько это возможно больше памяти
    mov rbp, rax
    mov rsp, rbp
    mov rax, 12
    lea rdi, [rbp+60000000]
    syscall

    // add EOL symbol
    mov r8, 10
    mov [rbp], r8
    add rsp, 1

read:
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 4096
    syscall
    
    test rax, rax
    jl pass
    
    add rsp, rax
    test rax, rax
    jnz read

pass:
    sub rsp, 1
    cmp rsp, rbp
    jle end
    
    cmpb [rsp], 10
    jz pass
    cmpb [rsp], 32
    jz pass
    
    add rsp, 1
    mov r8, 10
    mov [rsp], r8
    mov rbx, rsp
    jmp string
    
write:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rbx + 1]
    mov rdx, rcx
    syscall

    mov rsp, rbx
    cmp rbx, rbp
    jle end

string:
    sub rbx, 1
    cmpb [rbx], 10
    jnz string

    mov rcx, rsp
    sub rcx, rbx
    jmp write
     
end:
    mov rax, 60
    syscall