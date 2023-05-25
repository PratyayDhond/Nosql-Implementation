#include "nosql.h"
#include "Encryption/cipher.h"
#include <stdio.h>
#include<sys/ioctl.h> // for getting dimensions of the terminal window
#include <stdlib.h>
#include <string.h>   // for strcmp 
#include <ctype.h> // for toLower
#include <unistd.h> // for getPassword command

#define USER_ALREADY_EXISTS 0


typedef enum Commands{
    ls,
    ls_users,
    ls_documents,
    ls_collections,
    man,
    login,
    logout,
    create,
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

struct winsize sz;


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

void printHeading(char *str){
    // char * str = ; 
    int length = getLength(str);
    for(int i = 0; i < sz.ws_col/2-length/2;i++)
        printf(" ");
    printf("%s\n",str);
    for(int i = 0; i < sz.ws_col/2-length/2-2;i++)
        printf(" ");
    printDashes(length);
return;
}

void printDeclaration(){
    char * str = "This project is developed under the guidance of Prof. Ashwini Matange ma'am by the students Pratyay Dhond, Sarvesh Kulkarni and Sohel Bargir of Computer Engineering Div 2.\n";
    for(char *p = str; *p != '\0'; p++){
        printf("   ");
        for(int j = 2; j < sz.ws_col-3;j++){
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
    printHeading("Welcome to NoSQL implementation using C.");
    printDeclaration();
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

    printHeading("Manual Page for NoSQL Implementation");
    
    FILE *fptr = fopen(".manual","r");
    char * temp = calloc(200,sizeof(char));
    while(fgets(temp,200,fptr)){
        printf("%s",temp);
    }
    printf("\n");
    fclose(fptr);
    free(temp);

    char * str = "Press Any key to exit manual";

    printDashes(getLength(str));
    printf("%s\n: ",str);
   
    // This test case is explicitly for handling arrow presses, when a user presses an arrow 3 characters are put in the input stream '\033', '[' and either A,B,C,D
    if(getch() == '\033'){
        getch(); 
        getch();
    }
   
    system("clear");
}

char * getPassword(char * str){
    char * password = (char *) malloc(sizeof(char) * 32);
    int i = 0;
    int ch;

    printf("%s",str);
    while ((ch = getch()) != '\n') {
        if (ch == 127 || ch == 8) { // handle backspace
            if (i != 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    return password;
}

int checkIfUserExists(char * username){
    char command[100] = "ls -d .root/";
    strcat(command,username);
    int x = system(command);

    system("clear");
    printHeading("Create New User");
    printf("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) \n");
    printf("Enter your username: %s\n",username);

    if(x == 0)
        return USER_ALREADY_EXISTS;
    return create_user; 
}

void createUserDirectoryAndFiles(char * username,char * password){
    char command[100] = "mkdir '.root/";
    strcat(command,username);
    strcat(command,"'");
    system(command);

    strcpy(command,"touch .root/");
    strcat(command,username);
    strcat(command,"/.pass");
    system(command);

    char * encryptedPassword = Encrypt(password);

    // Writing Encrypted Password to file
    char passwordFile[100] = ".root/";
    strcat(passwordFile,username);
    strcat(passwordFile,"/.pass");
    FILE * fptr = fopen(passwordFile,"w+");
    fprintf(fptr,"%s",encryptedPassword);
    fclose(fptr);
    free(encryptedPassword);
    return;
    // system("clear");
}

void createUser(){
    system("clear");

    printHeading("Create New User");
    char * username = calloc(100,sizeof(char));
    char * password;
    char * confirmPassword;
    printf("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) \n");
    printf("Enter your username: ");
    scanf("%s",username);
    
    if(checkIfUserExists(username) ==  USER_ALREADY_EXISTS){
        printf("USER ALREADY EXISTS. Try picking a new username or logging in.\n");
    }else{
        reEnterPassword:
        password = getPassword("Enter Password  : ");
        confirmPassword = getPassword("Confirm Password: ");

        if(strcmp(password,confirmPassword) == 0){
            printf("Creating user...\n");
            createUserDirectoryAndFiles(username,password);
            printf("User has been created successfully.\n Do you want to display your password?\n : ");
        }
        // marked for probable depreciation
        else{
            printf("both Passwords must be the same.\n");
            goto reEnterPassword;
        }

    }
    
    printf("Press any key to continue.\n :");
    if(getch() == '\033'){
        getch(); 
        getch();
    }
    return;

    // printHeading()
}

int getInput(){
    char *input = (char *) calloc(100,sizeof(char)); // calloced to get an array initialised to 0
    int command = NOP;
    fflush(stdin);
    fgets(input,100,stdin);
    toLower(input);
    if(strcmp(input,"man") == 0)
        command = man;
    else if(strcmp(input,"ls") == 0)
        command = ls;    
    else if(strcmp(input,"ls users") == 0)
        command = ls_users;
    else if(strcmp(input,"ls docs") == 0 || strcmp(input,"ls documents") == 0)
        command = ls_documents;
    else if(strcmp(input,"ls collections") == 0 || strcmp(input,"ls cols") == 0)
        command = ls_collections;
    else if(strcmp(input,"login") == 0)
        command = login;
    else if(strcmp(input,"logout") == 0)
        command = logout;
    else if(strcmp(input,"create") == 0)
        command = create;    
    else if(strcmp(input,"create user") == 0)
        command = create_user;
    else if(strcmp(input,"create doc ") == 0 || strcmp(input,"create document") == 0)
        command = create_document;
    else if(strcmp(input,"create collection") == 0 || strcmp(input,"create col") == 0)
        command = create_collection;
// use document
// use collection
   free(input);
   return command; 
}

void noSQLMenu(){
    ioctl(0,TIOCGWINSZ,&sz);

    createUser();
    exit(0);

    printWelcomeMessage();
    int command;
    while(1){
        printf(">> ");
        command = getInput();
        if(command == man){
            displayMAN();
            fflush(stdout);
            fflush(stdin);
            printWelcomeMessage();
        }else if(command == ls){
            printf("use `ls` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `ls users`\n");
            printf("   2. <SYNTAX> => `ls docs`\n");
            printf("   3. <SYNTAX> => `ls cols`\n");
            printf("use command `man` for more details\n");
        }else if(command == create){
            printf("use `create` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `create user`\n");
            printf("   2. <SYNTAX> => `create document`\n");
            printf("   3. <SYNTAX> => `create collection`\n");
            printf("use command `man` for more details\n");

        }else if(command == create_user){
            createUser();
        }
    }
}

// Write a function to load all documents into AVL tree