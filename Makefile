run:
	gcc -g  main.c nosql.c Encryption/cipher.c DocumentHashmap/DocumentHashMap.c Backend/document.c globals/globals.c -o NoSQL
	./NoSQL
	
debug:
	gcc -g  main.c nosql.c Encryption/cipher.c DocumentHashmap/DocumentHashMap.c Backend/document.c globals/globals.c -o NoSQL
	gdb NoSQL
	
