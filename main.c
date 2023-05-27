#include "Encryption/cipher.h"
#include "nosql.h"
#include<stdlib.h>
#include<stdio.h>
#include "globals/globals.h"

char * test(char * str){
    char * s = Encrypt(str);
    printf("Encrypted -> '%s'\n\n",s); 
    return(Decrypt(s));
}

int main(){
    // printf("%s",Decrypt("YfL"));
    // printf("Decrypted -> %s\n",test("{}~"));
    // noSQLMenu(); 
    char * encrypt = dataEncrypt("Hello Sohel");
    char * Decrypt = dataDecrypt(encrypt);
    printf("%s -> %s",encrypt,Decrypt);
return 0;
}
