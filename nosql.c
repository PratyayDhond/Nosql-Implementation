#include "nosql.h"
#include "Encryption/cipher.h"
#include <stdio.h>
#include<sys/ioctl.h> // for getting dimensions of the terminal window
#include <stdlib.h>
#include <string.h>   // for strcmp 
#include <ctype.h> // for toLower

typedef enum Commands{
    ls_users,
    ls_documents,
    ls_collections,
    man,
    login,
    logout,
    create_user,
    create_collection,
    create_document,
    delete_user,
    delete_collection,
    delete_document,
    show_users,
    show_documents,
    show_collections,
    use_document,
    use_collection,
    NOP // Command used to indicate that the command inputted by the user is Not a Proper command
} commands;


void println(){
    printf("===================================================================================================================");
return;
}

void printDashes(int length){
    for(int i = 0; i <= length +1; i++){
        printf("-");
    }
    printf("\n\n");
}

void printHeading(int windowCol, char *str){
    // char * str = ; 
    int length = getLength(str);
    for(int i = 0; i < windowCol/2-length/2;i++)
        printf(" ");
    printf("%s\n",str);
    for(int i = 0; i < windowCol/2-length/2-2;i++)
        printf(" ");
    printDashes(length);
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

void printAvailableCommands(){
    char * str = "Available commands are ls,man,login,create. Use command man for more details\n";
    printf("   %s",str);
return;
}

void printWelcomeMessage(){
    struct winsize sz;
    ioctl(0,TIOCGWINSZ,&sz);

    printHeading(sz.ws_col,"Welcome to NoSQL implementation using C.");
    printDeclaration(sz.ws_col);
    printAvailableCommands();
    return;
}

void toLower(char * input){
    int length = getLength(input);
    input[length - 2] = '\0';
    for(int i = 0; i < length-1; i++){
        input[i] = tolower(input[i]);
    }
    return;
}

void displayMAN(){
    system("clear");

    struct winsize sz;
    ioctl(0,TIOCGWINSZ,&sz);
    printHeading(sz.ws_col,"Manual Page for NoSQL Implementation");
    
    FILE *fptr = fopen(".manual","r");
    char * temp = calloc(200,sizeof(char));
    while(fgets(temp,200,fptr)){
        printf("%s",temp);
    }
    printf("\n");
    fclose(fptr);
    free(temp);
}

int getInput(){
    char *input = (char *) calloc(100,sizeof(char)); // calloced to get an array initialised to 0
    int command = NOP;
    fgets(input,100,stdin);
    toLower(input);
    if(strcmp(input,"man") == 0)
        command = man;
    if(strcmp(input,"ls users") == 0)
        command = ls_users;
    if(strcmp(input,"ls docs") == 0 || strcmp(input,"ls documents") == 0)
        command = ls_documents;
    if(strcmp(input,"ls collections") == 0 || strcmp(input,"ls cols") == 0)
        command = ls_collections;
    if(strcmp(input,"login") == 0)
        command = login;
    if(strcmp(input,"logout") == 0)
        command = logout;
// use document
// use collection
   free(input);
   return command; 
}

void noSQLMenu(){
    displayMAN();
    exit(0);
    printWelcomeMessage();
    int command;
    while(1){
        printf(">> ");
        command = getInput();
        if(command == man){
            
        }
    }
}

// Write a function to load all documents into AVL tree