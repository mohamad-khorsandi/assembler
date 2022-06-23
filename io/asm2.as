	addi 	1,0,100
	sw	1,0,m1
	lw	2,0,m1
	beq	2,1,end
	addi	10,0,-1
end	halt
m1	.fill 	6
m2	.fill 	7 
