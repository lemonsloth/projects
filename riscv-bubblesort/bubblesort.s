addi s0, zero, 0x400   	 #generate constant 0x400 to store base address of array

#GENERATE 15 VALUES
addi t1, zero, -15
sw t1, 0(s0)

addi t1, zero, 42
sw t1, 4(s0)

addi t1, zero, 73
sw t1, 8(s0)

addi t1, zero, 19
sw t1, 12(s0)

addi t1, zero, -8
sw t1, 16(s0)

addi t1, zero, 24
sw t1, 20(s0)

addi t1, zero, 16
sw t1, 24(s0)

addi t1, zero, -2
sw t1, 28(s0)

addi t1, zero, 99
sw t1, 32(s0)

addi t1, zero, -78
sw t1, 36(s0)

addi t1, zero, -21
sw t1, 40(s0)

addi t1, zero, 23
sw t1, 44(s0)

addi t1, zero, -88
sw t1, 48(s0)

addi t1, zero, 49
sw t1, 52(s0)

addi t1, zero, -101
sw t1, 54(s0)

add a0, zero, s0   	 	#put base address of array into argument 0
addi a1, zero, 14   		#generate constant 14 to store the [size of the array - 1]

jal bubblesort			#a function call to bubblesort
j end				#jumps to end of program


bubblesort:
addi sp, sp, -4			#allocate stack frame for 1 word
sw s0, 0(sp)			#preserve s0


addi s0, zero, 0   		#generate a constant (0) for counter i (will count up to 14)
addi s1, zero, 0   		#generate a constant (0) for counter j (counts up to 14-i)
add s2, zero,  a0   		#holds the value of the base address and traverses through array 
				#(it will increment by 4)

addi t0, zero, 0   		#generate constant 0 to hold j condition logic (14-i)


#START OF LOGIC
forloopi:   			#start loop
  bge s0, a1, done   		#i < 9
  add s2, zero, a0   		#reset traverser to beginning of array
 
  #START FOR forloopj
  forloopj:
	sub t0, a1, s0   		 #s5 is condition (14 (final index) - i counter)
     	bge s1,t0, forloopjdone    	 #j < (14  - i)
    
  	lw t1, 0(s2)   			 #load sortarray[j] into temp t1 register using traverser
	lw t2, 4(s2)   			 #load sortarray[j+1] into temp t2 register using traverser
 	 
  	ble t1, t2, next   		 #if(sortarray[j] > sortarray[j+1])
   	 
    	#only executes if t1 > t2
    	add t3, zero, t1   	 	#tempVal = sortarray[j];
   	 
    	add t1, zero, t2   	 	#add zero + sortarray[j+1] and put in t1 register
    	sw t1, 0(s2)   		 	#sortarray[j] = sortarray[j+1];
   	 
    	add t2, zero, t3   	 	#add zero and t3 and store in t2 register
    	sw t2, 4(s2)   		 	#sortarray[j+1] = tempVal;
 	 
  	#always executes
  	next:   					 
  	addi s2, s2, 4   	 	#increment traverser by 4 to skip to next word
  	addi s1, s1, 1   	 	#increment j counter by 1 for condition checking
    j forloopj   		 #restart j loop
      
  #EXECUTES ONCE J LOOP CONDITION IS MET
  forloopjdone:
  addi s1, zero, 0   		 #reset j counter
  addi s0, s0, 1   		 #increment i

  #REPEAT I LOOP
  j forloopi   				 
 
#EXECUTES ONCE I LOOP CONDITION IS MET

done:

addi sp, sp, -4			#deallocate stack frame for 1 word
lw s0, 0(sp)			#restore s0
jr ra				#returns to caller


end:				#exits
