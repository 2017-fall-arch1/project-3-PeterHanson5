	.file "assembly.s"

	.text
	.balign 2
	.global countTrack
	.global scoreTrack

	.text
countTrack:
	add #1, 0(r12)
	pop r0

countScore:
	push r6
	push r7
	mov r13, r7
	mov r12, r6
	mov #48, 0(r6)
	mov r13, r12
	mov #10, r13
	call #first
	add r12, 0(r6)
	mov #48, 1(r6)
	mov r13, r12
	mov #10, r13
	call #second
	add r12, 1(r6)
	pop r7
	pop r6
	pop r0

first:
	push #0
	push #0
	push r13
	push #0
	cmp r4, r4
	rrc 2(r1)
	rrc 0(r1)
	push #8000

firstWhile:
	cmp #0, 0(r1)
	jz firstDone
	mov #0, r5
	mov 4(r1), r6
	cmp 2(r1), r12
	subc r6, r5
	jc firstIf
	sub 2(r1), r12
	bis 0(r1), 6(r1)

firstIf:
	cmp r4, r4
	rrc 4(r1)
	rrc 2(r1)
	rrc 0(r1)
	jmp firstWhile

firstDone:
	mov 6(r1), r12
	add #10, r1
	pop r0

second:
	push #0
	push #0
	push r13
	push #0
	cmp r4, r4
	rrc 2(r1)
	rrc 0(r1)
	push #8000

secondWhile:
	cmp #0, 0(r1)
	jz secondDone
	mov #0, r5
	mov 4(r1), r6
	cmp 2(r1), r12
	subc r6, r5
	jc secondIf
	sub 2(r1), r12
	bis 0(r1), 6(r1)

secondIf:
	cmp r4, r4
	rrc 4(r1)
	rrc 2(r1)
	rrc 0(r1)
	jmp secondWhile

secondDone:
	mov 6(r1), r12
	add #10, r1
	pop r0

.ident "GCC: (GNU) 4.9.1 20140707 (prerelease (msp430-14r1-364)) (GNUPro 14r1) (Based on: GCC 4.8 GDB 7.7 Binutils 2.24 Newlib 2.1)"
	
	
