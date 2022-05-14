	add	1,2,3	#all of machine instructions test
lbl1	sub	2,3,1
	slt	7,16,3
	or	7,16,3
	nand	4,2,1
lbl2	addi	3,1,12
	slti	5,2,1
	ori	2,6,4
lbl3	lui	5,2
	lw	3,0,six
	lw	4,1,20
	sw 	1,6,three	#foo
	beq	3,2,end
	beq	6,2,lbl1	
	jlar	5,6
	j	3
	j 	six
end	halt
six	.fill	6
three 	.fill 	3
