section .text
bits 64
default rel

global daxpy_asm
;daxpy_asm(int n, double A, double* X, double* Y, double* Z)
;			rcx,	xmm1,	r8,			r9,			?
daxpy_asm:
	push rbp 
	mov rbp, rsp
	add rbp, 16
	mov r10, [rbp+32] ;get 5th parameter

	sub rcx, 0x1 ;dec n

	L1:
		cmp rcx, 0x0
		jl Tapos

		movsd xmm2, [r8 + rcx*8]
		movsd xmm3, [r9 + rcx*8]

		mulsd xmm2, xmm1
		addsd xmm2, xmm3

		movsd [r10 + rcx*8], xmm2

		dec rcx

		jmp L1

Tapos:
	pop rbp
	ret