# RISC-V Bubble Sort
This is my implementation of the Bubble Sort algorithm using the RISC-V assembly language! 
The code initializes an array of 15 integers and then proceeds to sort the array in ascending order.

## What I Learned
Completing this project help me solidify my understanding of the fundamentals of RISC-V assembly such as:

- Stack operations
- Loop implementations
- Function calls
- Register management

Even though this code is based off of a simple sorting algorithm, it helped me understand the intricacies of low-level vs high-level coding and how things are broken up into instructions.

## Setup
First I generate the base address of the array and then store it in register 's0'. I then proceed to initialize the array with the values -15, 42, 73, 19, -8, 24, 16, -2, 99, -78, -21, 23, -88, 49, and -101 at an offset of 4 from the base address that I stored in register's0'.

Example of the first two values being generated:
```
#GENERATE 15 VALUES
addi t1, zero, -15
sw t1, 0(s0)

addi t1, zero, 42
sw t1, 4(s0)
```

## Function Call Arguments
After initializing the array, I set up a function call to the bubblesort algorithm, as well as a jump to the end label once the algorithm sorts the array.

```
add a0, zero, s0   	 	#put base address of array into argument 0
addi a1, zero, 14   		#generate constant 14 to store the [size of the array - 1]

jal bubblesort			#a function call to bubblesort
j end				#jumps to end of program

```

## Bubble Sort Function
### Once in the Bubblesort Function, Allocate Space on the Stack to Preserve 's0': 
```
bubblesort:
addi sp, sp, -4			#allocate stack frame for 1 word
sw s0, 0(sp)			#preserve s0
```

### Then, Initialize the Loop Counters:
```
addi s0, zero, 0   		#generate a constant (0) for counter i (will count up to 14)
addi s1, zero, 0   		#generate a constant (0) for counter j (counts up to 14-i)
add s2, zero,  a0   		#holds the value of the base address and traverses through array 
				#(it will increment by 4)

addi t0, zero, 0   		#generate constant 0 to hold j condition logic (14-i)
```

### Create the Outer and Inner Loop Logic:
```
forloopi:   			#start loop
  bge s0, a1, done   		#i < 9
  add s2, zero, a0   		#reset traverser to beginning of array
```
Inner Loop
```
 forloopj:
	sub t0, a1, s0   		 #s5 is condition (14 (final index) - i counter)
     	bge s1,t0, forloopjdone    	 #j < (14  - i)
```
Outer Loop

### Then the program performs the comparisons and swaps.

### When the Bubble Sort Algorithm is Finished:
The program deallocates the stack, restores s0, and returns to the instruction that called the algorithm.
```
done:

addi sp, sp, -4			#deallocate stack frame for 1 word
lw s0, 0(sp)			#restore s0
jr ra				#returns to caller
```

## End of Program
Once the program returns to the intruction that called the algorithm, it jumps to the end label.

```
end:                  # Exits
```

Which ends the program.
