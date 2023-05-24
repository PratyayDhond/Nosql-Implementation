#include "nosql.h"
#include <stdio.h>
#include<sys/ioctl.h>
// Welcome
// Login
// 

void println(){
    printf("===================================================================================================================");
return;
}

void printHeading(int windowCol){
    for(int i = 0; i < windowCol/2-19;i++)
    printf(" ");
    printf("Welcome to NoSQL implementation using C.\n");

    for(int i = 0; i < windowCol/2-20;i++)
        printf(" ");
    printf("------------------------------------------\n\n");
return;
}

void printDeclaration(int windowCol){
    char * str = "This project is developed under the guidance of Prof. Ashwini Matange ma'am by the students Pratyay Dhond, Sarvesh Kulkarni and Sohel Bargir of Computer Engineering Div 2.\n";
    
    for(char *p = str; *p != '\0'; p++){
        printf("   ");
        for(int j = 2; j < windowCol-3;j++){
            if(*p == '\0') break;
            printf("%c",*p);
            p++;
        }
        if(*p == '\0')
            break;
        printf(" \n");
    }
    // str = "Available commands are"
    // for()

return;
}

void printWelcomeMessage(){
    struct winsize sz;
    ioctl(0,TIOCGWINSZ,&sz);

    printHeading(sz.ws_col);
    printDeclaration(sz.ws_col);
    return;
}

void noSQLMenu(){
    printWelcomeMessage();
    while(1){
        
    }
}