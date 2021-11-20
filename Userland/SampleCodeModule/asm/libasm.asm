GLOBAL _syscall

GLOBAL _opcodeExp
GLOBAL _divZeroExp

GLOBAL _setStack

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

_divZeroExp:
	mov rdx, 5
	mov al,1
	mov bl,0
	div bl
	ret


; Usamos esta funcion para que el valor de RSP sea el mismo durante el inicio del programa
; y cuando se produce alguna excepcion donde reseteamos el stack y volvemos a correr el codigo del modulo Userland.
; La diferencia se debe a que el kernel luego de llamar a getStackBase llama otras funciones que consumen stack
; mientras que luego de la excepción vamos directo a 0x400000 (sampleCodeModuleAddress)
_setStack:

	mov rbx, [rsp]
	mov rsp, 0x10CFD0 ; direccion de inicio del stack (valor que retorna la funcion getStackBase)
	push rbx
	ret
