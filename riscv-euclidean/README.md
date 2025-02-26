# RISC-V Euclidean Alg
This is my implementation of a Euclidiean Greatest Common Divisor algorithm using RISC-V assembly! This code includes two examples of the calculation for the GCD using different pairs of integers.

Check out my [RISC-V Bubble Sort Algorithm!](https://github.com/8bitFrog/RISC-V-Bubble-Sort)

## What I Learned
This was one of my first programs that I created in RISC-V assembly. I learned how to work with function calls, arithmetic, and stack management!

## Setup
### First GCD Function Call
The code begins by generating a pair of unsigned integers (25 and 15) and placing them into registers 's0' and 's1'. 

```
main:

addi s0, zero, 25	#unsigned int a = 25
addi s1, zero, 15	#unsigned int b = 15
```
Then these values are placed into argument registers 'a0' and 'a1', 

```
add a0, zero, s0	#put a in argument 1
add a1, zero, s1	#put b in argument 2
```

for the following function call: `jal gcd			#call gcd`

### Second GCD Function Call
The second function call is setup in a similar way, but the unsigned integers are 64 and 96.

```
#next function call

addi s0, zero, 64	#unsigned int a = 64
addi s1, zero, 96	#unsigned int b = 96
	
add a0, zero, s0	#put a in argument 1
add a1, zero, s1	#put b in argument 2

jal gcd			#call gcd
			#a0 is already in the correct register
```

### End of Program (but not yet)
Once the function call is performed, the program with jump to the end label.
```
j end                   # jump to end
```

## GCD Function
### Once in the GCD Function, Allocate Space on the Stack to Preserve 's0'

```
gcd:

addi sp, sp, -4		#allocate stack frame by one word
sw s0, 0(sp)		#save s0 on stack
```
### Then Perform the GCD Algoritm Until Loop Condition Met

```
while:
ble a0, zero, skip	#checks if a <= 0, goes to skip if condition met
			#otherwise,
add s0, a0, zero	#set s0 to a0 		[temp = a]
remu a0, a1, a0		#set a0 to a1 mod a0 	[a = b % a]
add a1, s0, zero	#set a1 to s0		[b = temp]

j while			#jump to top of loop

```
### Once Loop Condition is Met
The function restores the 's0' register from the stack and then deallocates the stack frame. The value inside 'a1' will be assigned to the return value 'a0' and then return to the caller.

```
skip:
lw s0, 0(sp)            # restore s0
addi sp, sp, 4          # deallocate stack frame

add a0, zero, a1        # put b in return argument
jr ra                   # return to caller
```

## Check The 'a0' Register
The value inside will be the GCD!
