.text
.global machine_switch
.global start_thread
.global delete_start

machine_switch:

	push %rax
	push %rbx
	push %rcx
	push %rdx
	push %rbp
	push %rdi
	push %r8
	push %r9
	push %r10
	push %r11
	push %r12
	push %r13
	push %r14
	push %r15
	push %rsi

	mov %rsp, (%rsi)
	mov (%rdi), %rsp

	pop %rsi
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %r11
	pop %r10
	pop %r9
	pop %r8
	pop %rdi
	pop %rbp
	pop %rdx
	pop %rcx
	pop %rbx
	pop %rax

	ret 

#for stop main
start_thread:

	mov %rdi, %rsp
	
	ret


#for delete_start
delete_start:

	mov (%rdi), %rsp

	pop %rsi
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %r11
	pop %r10
	pop %r9
	pop %r8
	pop %rdi
	pop %rbp
	pop %rdx
	pop %rcx
	pop %rbx
	pop %rax

	ret
