GLOBAL cpuVendor
GLOBAL clock
GLOBAL kbFlag
GLOBAL readKeyboard

section .text


kbFlag:
        push rbp
        mov rbp, rsp
		
		mov rax,0
loop:
		in al,0x64       
    	mov cl,al
        and al,0x01       
    	cmp al,0
        je loop
    	in al,0x60
       
    mov rsp, rbp
    pop rbp
    ret

readKeyboard:
	xor rax, rax
	in al, 64h
	and al, 1 ;Me quedo con el ultimo bit
	test al, al
	jz readKeyboard
	in al, 60h
	.end:
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
