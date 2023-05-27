run:
	clear
	gcc -g  main.c nosql.c Encryption/cipher.c DocumentHashmap/DocumentHashMap.c Backend/document.c globals/globals.c
	./a.out
	
debug:
	gcc -g  main.c nosql.c Encryption/cipher.c DocumentHashmap/DocumentHashMap.c Backend/document.c
	gdb a.out
	
