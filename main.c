#include "Encryption/cipher.h"
#include "nosql.h"
#include<stdio.h>

char * test(char * str){
    char * s = Encrypt(str);
    printf("Encrypted -> '%s'\n\n",s); 
    return(Decrypt(s));
}

int main(){
    // printf("Decrypted -> %s\n",test("{}~"));
    noSQLMenu(); 
return 0;
}
