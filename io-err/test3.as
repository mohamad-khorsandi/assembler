	slt	2,3,1	#out of bound offset err
	add	7,16,3
	or	7,16,3
lbl	nand	4,2,1
	slti	5,2,1
	addi	2,6,4 	
	sw	3,0,num1
	lw 	1,6,16	
	beq	3,2,lbl	
	jlar	5,12
	j	32768	#this number doesnt fit	
	halt		
num1	.fill	1
num2	.fill	3
