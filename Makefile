run:
	gcc -g -W main.c nosql.c Encryption/cipher.c
	./a.out
	
debug:
	gcc -g main.c nosql.c Encryption/cipher.c
	gdb a.out
	
