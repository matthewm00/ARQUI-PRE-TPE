GLOBAL cpuVendor
GLOBAL clock
GLOBAL readKeyboard
GLOBAL hasKeyboardKey

section .text

hasKeyboardKey:
    mov rax, 0
    in al, 64h //keyboard status
    and al, 0x01
    ret

readKeyboard:
	xor rax, rax
	in al, 60h //read the buffer
	ret

clock:
	push rbp
	mov rbp, rsp

	mov al, dil
	out 70h, al
	xor rax, rax
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
