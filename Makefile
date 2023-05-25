run:
	gcc -g main.c nosql.c Encryption/cipher.c
	./a.out
	
debug:
	gcc -g *.c
	gdb a.out
	
