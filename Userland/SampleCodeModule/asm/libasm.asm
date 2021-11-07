GLOBAL _syscall

GLOBAL _opcodeExp

section .text


_syscall:
    push rbp
    mov rbp, rsp
    
	int 80h

	mov rsp, rbp
    pop rbp

    ret

	;Generates an invalid opcode.
	;This instruction is provided for software testing to explicitly generate an invalid opcode. 
	;The opcode for this instruction is reserved for this purpose.
_opcodeExp:
	UD2 
	ret
