	.file	"c_prog_clean.c"
	.intel_syntax noprefix
	.text
	.globl	tol
	.section .rdata,"dr"
	.align 8
tol:
	.long	-1598689907
	.long	1051772663
	.globl	sum
	.bss
	.align 8
sum:
	.space 8
	.globl	upper
	.align 8
upper:
	.space 8
	.globl	lower
	.align 8
lower:
	.space 8
	.text
	.globl	fx
	.def	fx;	.scl	2;	.type	32;	.endef
fx:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	movsd	QWORD PTR 16[rbp], xmm0
	movsd	xmm0, QWORD PTR 16[rbp]
	call	sqrt
	movsd	xmm1, QWORD PTR .LC0[rip]
	divsd	xmm1, xmm0
	movq	rax, xmm1
	movq	xmm0, rax
	leave
	ret
	.globl	trapez
	.def	trapez;	.scl	2;	.type	32;	.endef
trapez:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	and	rsp, -16
	sub	rsp, 80
	movups	XMMWORD PTR 80[rsp], xmm6
	movsd	QWORD PTR 16[rbp], xmm0
	movsd	QWORD PTR 24[rbp], xmm1
	movsd	QWORD PTR 32[rbp], xmm2
	mov	QWORD PTR 40[rbp], r9
	mov	DWORD PTR 76[rsp], 1
	movsd	xmm0, QWORD PTR 24[rbp]
	subsd	xmm0, QWORD PTR 16[rbp]
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, DWORD PTR 76[rsp]
	divsd	xmm0, xmm1
	movsd	QWORD PTR 56[rsp], xmm0
	movsd	xmm0, QWORD PTR 16[rbp]
	call	fx
	movapd	xmm6, xmm0
	mov	rax, QWORD PTR 24[rbp]
	movq	xmm0, rax
	call	fx
	addsd	xmm0, xmm6
	movsd	QWORD PTR 48[rsp], xmm0
	movsd	xmm0, QWORD PTR 48[rsp]
	mulsd	xmm0, QWORD PTR 56[rsp]
	movsd	xmm1, QWORD PTR .LC1[rip]
	divsd	xmm0, xmm1
	mov	rax, QWORD PTR 40[rbp]
	movsd	QWORD PTR [rax], xmm0
	pxor	xmm0, xmm0
	movsd	QWORD PTR 64[rsp], xmm0
.L6:
	sal	DWORD PTR 76[rsp]
	mov	rax, QWORD PTR 40[rbp]
	movsd	xmm0, QWORD PTR [rax]
	movsd	QWORD PTR 40[rsp], xmm0
	movsd	xmm0, QWORD PTR 24[rbp]
	subsd	xmm0, QWORD PTR 16[rbp]
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, DWORD PTR 76[rsp]
	divsd	xmm0, xmm1
	movsd	QWORD PTR 56[rsp], xmm0
	mov	DWORD PTR 72[rsp], 1
	jmp	.L4
.L5:
	pxor	xmm0, xmm0
	cvtsi2sd	xmm0, DWORD PTR 72[rsp]
	addsd	xmm0, xmm0
	movsd	xmm1, QWORD PTR .LC0[rip]
	subsd	xmm0, xmm1
	mulsd	xmm0, QWORD PTR 56[rsp]
	movsd	xmm1, QWORD PTR 16[rbp]
	addsd	xmm0, xmm1
	movsd	QWORD PTR 32[rsp], xmm0
	mov	rax, QWORD PTR 32[rsp]
	movq	xmm0, rax
	call	fx
	movsd	xmm1, QWORD PTR 64[rsp]
	addsd	xmm0, xmm1
	movsd	QWORD PTR 64[rsp], xmm0
	add	DWORD PTR 72[rsp], 1
.L4:
	mov	eax, DWORD PTR 76[rsp]
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	cmp	DWORD PTR 72[rsp], eax
	jle	.L5
	movsd	xmm0, QWORD PTR 64[rsp]
	addsd	xmm0, xmm0
	addsd	xmm0, QWORD PTR 48[rsp]
	movapd	xmm1, xmm0
	mulsd	xmm1, QWORD PTR 56[rsp]
	movsd	xmm0, QWORD PTR .LC3[rip]
	mulsd	xmm0, xmm1
	mov	rax, QWORD PTR 40[rbp]
	movsd	QWORD PTR [rax], xmm0
	mov	rax, QWORD PTR 40[rbp]
	movsd	xmm0, QWORD PTR [rax]
	subsd	xmm0, QWORD PTR 40[rsp]
	movq	xmm1, QWORD PTR .LC4[rip]
	andpd	xmm0, xmm1
	mov	rax, QWORD PTR 40[rbp]
	movsd	xmm1, QWORD PTR [rax]
	mulsd	xmm1, QWORD PTR 32[rbp]
	movq	xmm2, QWORD PTR .LC4[rip]
	andpd	xmm1, xmm2
	comisd	xmm0, xmm1
	ja	.L6
	nop
	nop
	movups	xmm6, XMMWORD PTR 80[rsp]
	leave
	ret
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	__main
	movsd	xmm0, QWORD PTR .LC0[rip]
	movsd	QWORD PTR lower[rip], xmm0
	movsd	xmm0, QWORD PTR .LC5[rip]
	movsd	QWORD PTR upper[rip], xmm0
	movsd	xmm1, QWORD PTR .LC6[rip]
	movsd	xmm0, QWORD PTR upper[rip]
	mov	rax, QWORD PTR lower[rip]
	lea	r9, sum[rip]
	movapd	xmm2, xmm1
	movapd	xmm1, xmm0
	movq	xmm0, rax
	call	trapez
	mov	eax, 0
	leave
	ret
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC1:
	.long	0
	.long	1073741824
	.align 8
.LC3:
	.long	0
	.long	1071644672
	.align 16
.LC4:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.align 8
.LC5:
	.long	0
	.long	1075970048
	.align 8
.LC6:
	.long	-1598689907
	.long	1051772663
	.ident	"GCC: (Rev9, Built by MSYS2 project) 11.2.0"
	.def	sqrt;	.scl	2;	.type	32;	.endef
