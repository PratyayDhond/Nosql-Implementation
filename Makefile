run:
	gcc -g  main.c nosql.c Encryption/cipher.c Backend/document.c
	./a.out
	
debug:
	gcc -g  main.c nosql.c Encryption/cipher.c Backend/document.c
	gdb a.out
	
