#include "cipher.h"
#include<stdio.h>

char * test(char * str){
    char * s = Encrypt(str);
    printf("Encrypted -> '%s'\n\n",s); 
    return(Decrypt(s));
}

int main(){
    printf("%s",test("Test@#123"));
return 0;
}