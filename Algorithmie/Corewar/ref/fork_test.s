.name "fork test"
.comment "just a basic living prog"

	fork %:zjmp
	
live:
#	st r1, 42
	and r1, %0, r1
	st r1, r24
zjmp:	
	zjmp %:live					
#	st r2, 10
#	st r0, -4
#	st r1, 4096
