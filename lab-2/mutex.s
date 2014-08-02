	.syntax unified
	.arch armv7-a
	.text

	.equ locked, 1
	.equ unlocked, 0

@ void lock_mutex(void *mutex)
	.global lock_mutex
	.type lock_mutex, function
lock_mutex:
        @ INSERT CODE BELOW
.L1:
	ldr r1, =locked
	ldrex r2, [r0]
	cmp r2, r1
	beq .L1
	strexne r2, r1, [r0]
	cmpne r2, #1
	beq .L1
	dmb
        @ END CODE INSERT
	bx lr

	.size lock_mutex, .-lock_mutex

@ void unlock_mutex(void *mutex)
	.global unlock_mutex
	.type unlock_mutex, function
unlock_mutex:
	@ INSERT CODE BELOW
	ldr r1, =unlocked
	dmb
	str r1, [r0]
	dsb
	sev
        @ END CODE INSERT
	bx lr
	.size unlock_mutex, .-unlock_mutex

	.end
