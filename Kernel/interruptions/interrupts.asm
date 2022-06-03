GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _xchg

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL _syscallHandler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallSelector
EXTERN getStackBase
EXTERN processManager

SECTION .text

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

%macro popState 0
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

%macro pushStateExtra 0
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
	push fs
    push gs
%endmacro

%macro popStateExtra 0
	pop gs
	pop fs
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


%macro irqHandlerMaster 1
	pushState

	mov rdi, %1
	mov rsi, rsp
	call irqDispatcher

	sendEndOfInterrupt

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1
	mov rsi, rsp
	call exceptionDispatcher
%endmacro

%macro sendEndOfInterrupt 0
	mov al, 20h
	out 20h, al
%endmacro

_hlt:
	sti
	hlt
	cli
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

_xchg:
	mov rax, rsi
	xchg [rdi], eax		; put eax in [rdi] and [rdi] in eax
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	pushStateExtra

	mov rdi, 0
	mov rsi, rsp
	call irqDispatcher

	mov rdi,rsp
	call processManager
	mov rsp, rax

	sendEndOfInterrupt

	popStateExtra
	iretq

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid OpCode Exception
_exception6Handler:
	exceptionHandler 6
haltcpu:
	cli
	hlt
	ret

_syscallHandler:

	call syscallSelector
	
	iretq

SECTION .bss
	aux resq 1