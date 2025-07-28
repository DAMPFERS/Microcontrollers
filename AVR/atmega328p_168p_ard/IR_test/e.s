	.file	"e.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "%d\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	64(%rsp), %rbp
	.seh_setframe	%rbp, 64
	.seh_endprologue
	call	__main
	movabsq	$8453855113460344136, %rax
	movq	%rax, -21(%rbp)
	movabsq	$27419017320157728, %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L5:
	movl	$0, -8(%rbp)
	jmp	.L3
.L4:
	movl	-4(%rbp), %eax
	cltq
	movzbl	-21(%rbp,%rax), %eax
	movsbl	%al, %edx
	movl	$7, %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	sarl	%cl, %edx
	movl	%edx, %eax
	andl	$1, %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addl	$1, -8(%rbp)
.L3:
	cmpl	$7, -8(%rbp)
	jle	.L4
	movl	$32, %ecx
	call	putchar
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	movslq	%eax, %rbx
	leaq	-21(%rbp), %rax
	movq	%rax, %rcx
	call	strlen
	cmpq	%rax, %rbx
	jb	.L5
	movl	$0, %eax
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
	.def	strlen;	.scl	2;	.type	32;	.endef
