  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global hexasc 
.global time2string 
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
 hexasc:
	
	sltiu	$v0,$a0,10
	
	beq 	$v0,$0,letters	# till letters om input är större än 9
	nop
	
	addi	$v0,$a0,48	# + 48 för att v0 = 1, 48 för att omvandla till ASCII
	
	andi	$v0,$v0,0x07f	# bara 7 (lsb) return
	
	jr	$ra	# hoppa tillbaka till efter jal 
	nop
	
letters:
	addi	$v0,$a0,55
	
	andi	$v0,$v0,0x07f	# bara 7 (lsb) return
	jr	$ra
	nop
	
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
 	
 time2string:
 	PUSH 	$s0
 	PUSH 	$ra
 	PUSH 	$s1
 	
 	add	$s0,$0,$a0	#address sparas till s0
 	add	$s1,$0,$a1	#tiden sparas på 16 lsb i a1, kopiera till s1
 	
 	andi	$t0,$a1,0xf000	# minut 5
 	srl	$a0,$t0,12	# shift to (lsb)
 	jal	hexasc		# kalla hexasc
 	nop
 
 	sb	$v0,0($s0)	# store byte
 	
 	andi	$t2,$a1,0xf00	# minut 9
 	srl	$a0,$t2,8
 	jal	hexasc
 	nop
 
 	sb	$v0,1($s0)
 	
 	li	$t6, 0x3A	# : tecknet
 	sb	$t6, 2($s0)
 	
 	andi	$t4,$a1,0xf0	# sekund 5
 	srl	$a0,$t4,4
 	jal	hexasc
 	nop
 	
 	sb	$v0,3($s0)
 	
 	andi	$a0,$a1,0xf	# sekund 7
 	jal	hexasc
 	nop
 	sb	$v0,4($s0)	# shift to next register

  sb  $0,5($s0)
 	
 	POP $s0
 	POP $ra
 	POP $s1
 	
 	jr	$ra
 	nop

