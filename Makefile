run:
	gcc -g *.c
	./a.out
	
debug:
	gcc -g *.c
	gdb a.out
	
