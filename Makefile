run:
	gcc -g  main.c nosql.c Encryption/cipher.c FetchingDocument/document.c
	./a.out
	
debug:
	gcc -g  main.c nosql.c Encryption/cipher.c FetchingDocument/document.c
	gdb a.out
	
