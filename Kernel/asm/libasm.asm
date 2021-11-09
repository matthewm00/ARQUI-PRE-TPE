GLOBAL _getRTCInfo
GLOBAL _getKey
GLOBAL _hasKey
GLOBAL _getMem
GLOBAL _exit
GLOBAL _saveRegisters
GLOBAL getHour
GLOBAL getMins
GLOBAL getSeconds
GLOBAL _getStackPointer

EXTERN saveRegisters

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro	popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

_getRTCInfo:
    push rbp
    mov rbp,rsp

    mov rax, rdi
    out 70h, al
    mov rax,0
    in al, 71h

    leave
    ret

_getKey:
    push rbp
    mov rbp,rsp
    
    xor rax, rax
    in al,60h

    mov rsp, rbp
	pop rbp
    ret

_hasKey:
    push rbp
    mov rbp,rsp

    xor rax, rax
    in al,64h
    and al,0x01

    mov rsp, rbp
	pop rbp
    ret

_getMem:
    push rbp
	mov rbp,rsp

	mov al, byte[rdi]

	leave
	ret

_exit:
    jmp $

_saveRegisters:
	push rbp
	mov rbp, rsp

	push rdi
	mov rdi,rsp
	call saveRegisters
	pop rdi
	
	mov rsp, rbp
	pop rbp
	ret

_getStackPointer:

	mov rax, rsp
	ret


;; http://helppc.netcore2k.net/hardware/cmos-clock

getHour: ; recordar que clock devuelve la hora en formato BCD de 8 bits
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,4
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getMins:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,2
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getSeconds:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,0
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret