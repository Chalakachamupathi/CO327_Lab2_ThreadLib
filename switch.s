.text
.global machine_switch
.global start_thread

machine_switch:
	# address of the new sp is arg1
	# address of the current tcb is arg2
	# need to store all required registered for old tcb
	# restore all required registred from the new tcb
	# then when you return, you should get to the new thread 

	

	push %rax
	push %rbx
	push %rcx
	push %rdx
	push %rbp
	push %rsi
	push %rdi
	push %r8
	push %r9
	push %r10
	push %r11
	push %r12
	push %r13
	push %r14
	push %r15

	mov %rsp, (%rsi)

	mov (%rdi), %rsp

	pop %rax
	pop %rbx
	pop %rcx
	pop %rdx
	pop %rbp
	pop %rsi
	pop %rdi
	pop %r8
	pop %r9
	pop %r10
	pop %r11
	pop %r12
	pop %r13
	pop %r14
	pop %r15 

	ret 

#for stop main
start_thread:

	mov %rdi, %rsp

	ret