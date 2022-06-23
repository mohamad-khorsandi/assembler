start	slt	2,3,1	#usage of undefiend opcode err
	nand	7,16,3
	or	7,16,3
	mov	4,2,1 	#this instruction is illegal
	addi	5,2,1
	ori	2,6,4 	
	sw	3,0,mem
	lw 	1,6,mem	
	j	start	
	halt
mem	.fill	34
