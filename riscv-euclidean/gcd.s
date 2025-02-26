#MAIN
main:

addi s0, zero, 25	#unsigned int a = 25
addi s1, zero, 15	#unsigned int b = 15
	
add a0, zero, s0	#put a in argument 1
add a1, zero, s1	#put b in argument 2

jal gcd			#call gcd
			#a0 is already in the correct register

#next function call

addi s0, zero, 64	#unsigned int a = 64
addi s1, zero, 96	#unsigned int b = 96
	
add a0, zero, s0	#put a in argument 1
add a1, zero, s1	#put b in argument 2

jal gcd			#call gcd
			#a0 is already in the correct register

j end			#jump to end

#GCD FUNCTION
gcd:

addi sp, sp, -4		#allocate stack frame by one word
sw s0, 0(sp)		#save s0 on stack

addi s0, zero, 0	#set s0 to 0 (for swapping)

while:
ble a0, zero, skip	#checks if a <= 0, goes to skip if condition met
			#otherwise,
add s0, a0, zero	#set s0 to a0 		[temp = a]
remu a0, a1, a0		#set a0 to a1 mod a0 	[a = b % a]
add a1, s0, zero	#set a1 to s0		[b = temp]

j while			#jump to top of loop

skip:			#once condition met,

lw s0, 0(sp)		#restore s0
addi sp, sp, 4		#deallocate stack frame


add a0, zero, a1	#put b in return argument
jr ra			#return to caller




end:			#end of program