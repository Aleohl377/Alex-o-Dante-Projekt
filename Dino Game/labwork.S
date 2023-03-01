  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global delay

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  #
  # Please add your own code below this line
  #
delay:
 	addi	$t2,$0,0	# i=0
 	addi	$t1,$0,4711	# t1 = 4711
 whileloop:
 	ble	$a0,$0,end
 	nop			# fortsätt bara om argument är större än 0
 	addi	$a0,$a0,-1	# ms - 1
 	andi $t2, $t2, 0x0
 forloop:
 	beq	$t2,$t1,whileloop
 	nop			# tillbaka till while lopp
 	addi	$t2,$t2,1	# increment med 1
 	j	forloop
 	nop		

 end:
 	jr	$ra
 	nop