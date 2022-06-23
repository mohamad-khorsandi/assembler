	beq	1,2,end	#undefined lable err
	add	2,3,1
	slt	7,16,3
	or	7,16,3
	nand	4,2,1
	slti	5,2,1
	ori	2,6,4
	lw	3,0,ten
	sw 	1,6,three	#here is usage undefined lable
	beq	3,2,end	
	jlar	5,6
	j	foo		
end	halt			#here is usage undefined lable
ten	.fill	10
