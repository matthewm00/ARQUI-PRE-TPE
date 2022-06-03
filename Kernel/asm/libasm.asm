
GLOBAL _getRTCInfo

GLOBAL _getKey
GLOBAL _hasKey
GLOBAL _getMem
GLOBAL _exit
GLOBAL _callTimerTick
section .text
	

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

_callTimerTick:
    int 20h
    ret

_exit:
    jmp $
