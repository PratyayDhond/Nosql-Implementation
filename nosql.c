#include "nosql.h"
#include "Encryption/cipher.h"
#include <stdio.h>
#include<sys/ioctl.h> // for getting dimensions of the terminal window
#include <stdlib.h>
#include <string.h>   // for strcmp 
#include <ctype.h> // for toLower
#include <unistd.h> // for getPassword command

#define USER_ALREADY_EXISTS 0
#define PASSWORDS_MATCH 1
#define PASSWORDS_DO_NOT_MATCH 2

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
    clear,
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

void printDeclaration(char * str){
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
        printf(" \n");

    // str = "Available commands are"
    // for()

return;
}

void getchSafe(){
    printf("Press any key to continue.\n :");
    if(getch() == '\033'){
        getch(); 
        getch();
    }
    return;
}

void clearInputBuffer(){
        char temp = getch();
        while(temp != '\n' ){
            if(temp == '\033'){
                getch(); getch();
                break;
            }
            temp = getch();
        }
        return;
}

void printAvailableCommands(){
    char * str = "Available commands are ls,man,login,create. Use command man for more details\n\n";
    printf("   %s",str);
return;
}

void printWelcomeMessage(){
    printHeading("Welcome to NoSQL implementation using C.");
    printDeclaration("This project is developed under the guidance of Prof. Ashwini Matange ma'am by the students Pratyay Dhond, Sarvesh Kulkarni and Sohel Bargir of Computer Engineering Div 2.");
    printAvailableCommands();
    return;
}

void toLower(char * input){
    int length = getLength(input);
    input[length - 2] = '\0';
    for(int i = 0; i < length-1; i++){
        input[i] = tolower(input[i]);
    }
    // printf("length -2 = '%d'",input[length-2]);
    for(int i = length -1; i >= 0; i--)
        if(input[i] == (char) 13){
            input[i] == '\0';
            break;
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


    printDashes(getLength("Press any key to continue.\n :"));
    getchSafe();
    // This test case is explicitly for handling arrow presses, when a user presses an arrow 3 characters are put in the input stream '\033', '[' and either A,B,C,D
    system("clear");
}

char * getPassword(char * str){
    char * password = (char *) malloc(sizeof(char) * 32);
    int i = 0;
    int ch;

    // prints the do you want to enter password wala statement, do not comment
    printf("%s",str);
    while ((ch = getch()) != '\n') {
        if(ch == '\033'){
            getch();    // this case deals with the input of arrow keys in pass word
            getch();
            continue;
        }
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

int checkPasswords(char *password, char * confirmPassword){

    if(strcmp(password,confirmPassword) == 0){
        free(confirmPassword);
        return PASSWORDS_MATCH;
    }
    free(password);
    free(confirmPassword);
    printf("ERROR! Both Passwords must be the same! Press any key to continue...\n");
    getchSafe();
    return PASSWORDS_DO_NOT_MATCH;
}

void createUser(){
    system("clear");

    printHeading("Create New User");
    char * username = calloc(100,sizeof(char));
    char input;

    printf("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) \n");
    printf("Enter your username: ");
    scanf("%s",username);
    if(checkIfUserExists(username) ==  USER_ALREADY_EXISTS){
        printf("USER ALREADY EXISTS. Try picking a new username or logging in.\n");
        getchSafe();
    }else{
            char * password;
            char * confirmPassword;

            // takes input till both passwords are the same
        do{
            system("clear");
            printHeading("Create New User");
            printf("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) \n");
            printf("Enter your username: %s\n",username); 
            password = getPassword("Enter Password  : ");
            confirmPassword = getPassword("Confirm Password: ");
        }while(checkPasswords(password,confirmPassword) == PASSWORDS_DO_NOT_MATCH);

        printf("Creating user...\n");
        createUserDirectoryAndFiles(username,password);
        printf("User has been created successfully.\n Do you want to display your password? [Y/N]\n : ");
        
        
        input = getch();
        if(input == '\033'){
            getch(); getch();
        }

        if(input == 'y' || input == 'Y'){
            printf("Password : %s\n",password);
            printf("Press return key to continue.\n :");
            scanf("%c",&input);
            clearInputBuffer();
        }
        free(password);
        free(username);
    }   
    return;

    // printHeading()
}

int getInput(){
    char *input = (char *) calloc(100,sizeof(char)); // calloced to get an array initialised to 0
    int command = NOP;
    fgets(input,100,stdin);
    toLower(input);
    // printf("input -> `%s`",input);
    if(strcmp(input,"man") == 0)
        command = man;
    else if(strcmp(input, "clear") == 0)
        command = clear;
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
    else if(strcmp(input,"remove user") == 0 || strcmp(input,"rm user") == 0)
        command = delete_user;
// use document
// use collection
   free(input);
   return command; 
}

void showUsers(){
    system(" ls .root/ >> users");
    FILE *fptr = fopen("users","r");
    if(!fptr)
        return;
    char temp[32] = "";
    printf("Users : \n");
    int j = 0;
    int code = 0;
    while(fscanf(fptr,"%s",temp)){
        if(feof(fptr))
            break;
        printf("  %s\n",temp);
    }
    printf("\n");
    fclose(fptr);
    system("rm users ");
}

int validateUser(char * username){
    int code;
    // printf("Enter password : ");
    char *password = (char*) malloc(sizeof(char) * 32);
    if(!password)
        return PASSWORDS_DO_NOT_MATCH;
    fgets(password,32,stdin);
    password = getPassword("Enter password : ");
    if(password[0] == '\n')
        password = getPassword("Enter password : ");
        // fgets(password,32,stdin);
    // password[getLength(password)-2] = '\0'; // replaces /n from the password

    strcpy(password,Encrypt(password));
    
    char *filename = (char*) calloc(100,sizeof(char));
    strcat(filename,".root/");
    strcat(filename,username);
    strcat(filename,"/.pass");


    FILE *fptr = fopen(filename,"r");
    if(!fptr){
        printf("password file read failed!");
        return PASSWORDS_DO_NOT_MATCH;
    }

    char * encryptedPass = (char*) malloc(sizeof(char) * 32);
    fgets(encryptedPass,32,fptr);
    if(encryptedPass[getLength(encryptedPass)-2] == '\n')
        encryptedPass[getLength(encryptedPass)-2] = '\0';

    if(strcmp(password,encryptedPass) == 0)
        code = PASSWORDS_MATCH;
    else 
        code = PASSWORDS_DO_NOT_MATCH;

    fclose(fptr);
    return code;
}

void removeUser(){
    system("clear");
    printHeading("Remove User");
    printDeclaration("User removal is a dangerous process! All the collections and the documents of the user would be deleted along with the user metadate. Please make sure that you are at the right place before proceeding.");
    printf("Enter username : ");
    char * username = (char *) calloc(100,sizeof(char));
    fscanf(stdin,"%s",username);
    char command[100] = "ls -d '.root/";
    strcat(command, username);
    strcat(command, "'");
    int code = system(command);
    
    if(code == 0){
        code = validateUser(username);
        if(code == PASSWORDS_MATCH){
            strcpy(command,"rm -r '.root/");
            strcat(command, username);
            strcat(command, "'");
            system(command);
            printf("User `%s` deleted successfully!\n",username);
        }else{
            printf("Incorrect Password! User cannot be deleted with incorrect credentials.");
        }
        getchSafe();
    }else{
        printf("User does not exist. Check username again or try `ls users` to get list of users\n");
        getchSafe();
    }
    free(username); 
    return;
}


void noSQLMenu(){
    ioctl(0,TIOCGWINSZ,&sz);
    printWelcomeMessage();
    int command;
    while(1){
        printf(">> ");
        command = getInput();
        if(command == man){
            displayMAN();
            system("clear");
            printWelcomeMessage();

        }else if(command == ls){
            printf("use `ls` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `ls users`\n");
            printf("   2. <SYNTAX> => `ls docs`\n");
            printf("   3. <SYNTAX> => `ls cols`\n");
            printf("use command `man` for more details\n");
        }else if(command == ls_users){
            showUsers();
        }else if(command == create){
            printf("use `create` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `create user`\n");
            printf("   2. <SYNTAX> => `create document`\n");
            printf("   3. <SYNTAX> => `create collection`\n");
            printf("use command `man` for more details\n");
        }else if(command == create_user){
            createUser();
            system("clear");
            printWelcomeMessage();
        }else if(command == delete_user){
            removeUser();
            system("clear");
            printWelcomeMessage();
        }else if(command == clear){
            system("clear");
            printWelcomeMessage();
        }else if(command == NOP){
            printf("\b \b");
            printf("\b \b");
            printf("\b \b");
        }

    }
}

// Write a function to load all documents into AVL tree