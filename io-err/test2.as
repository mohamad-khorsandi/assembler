	slt	2,3,1	#twice define of a lable err
	add	7,16,3
	and	7,16,3
	nand	4,2,1
	slti	5,2,1
end	addi	2,6,4 	#first define
	sw	3,0,num
	lw 	1,6,16	
	beq	3,2,end	
	jlar	5,12
	j	end		
end	halt		#second define
num	.fill	123
