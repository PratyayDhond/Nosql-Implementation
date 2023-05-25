#include<stdio.h>
#include<stdlib.h>
#include "DocumentHashMap.h"
#include<limits.h>
#include<string.h>

int getCount(DocumentHashMap tnode){
    if(!tnode)
    return 0;
    return 1 + getCount(tnode -> left) + getCount(tnode -> right);
}
int main(){
    DocumentHashMap t;
    initDocumentHashMap(&t);

    insertIntoDocumentHashMap(&t,"Sarvesh","Kulkarni","string");
    insertIntoDocumentHashMap(&t,"Sarvesh","sarvesh","string");

    insertIntoDocumentHashMap(&t,"Pratyay","Dhond","string");
    insertIntoDocumentHashMap(&t,"Sohel","Bargir","string");
    insertIntoDocumentHashMap(&t,"Aditya","Raul","string");
    insertIntoDocumentHashMap(&t,"Mahind","Salwe","string");
    updateValue(&t,"Sarvesh","1","int");
    // Values temp = findAndFetchDocument(t,"");
    // if(temp){
    // printf("\n Key : %s , ",temp -> key);
    // printf("Value : %s , ",temp -> value);
    // printf("Datatype : %s\n",temp -> datatype);
    // }
    // else{
    //     printf("No output\n");
    // }
    // ######TESTED CODE - ALL WORKS FINE 
     
    // removedocumentHashmap(&t,"Sarvesh");
    // removedocumentHashmap(&t,"Pratyay");
    // removedocumentHashmap(&t,"Mahind");
    // removedocumentHashmap(&t,"Aditya");
    // removedocumentHashmap(&t,"Sohel");
//     FILE* fp;
//     char ch;
//     int k = 0; 
//     fp = fopen("data1.txt", "r");
//      if (NULL == fp) {
//         return 0;
//     }
//   char str[1000];
//       int i = 0;

//     while (fscanf(fp, "%s", data[k]) != EOF) {
//         insertIntoHashMap(&t,data[k]);
//         k++;
//         i++;
//     }
//     k = 0 , i = 0 ;
//     fclose(fp);
    // int count = 0 ;
    //   while(t){
    //         removeNode(&t,t-> data);
    //  printf("\nTnode Count :  %d",getCount(t));
    //         count++;
    //         // printf("\n%d",count);
    //     }
     preOrder(t);

    return 0;
}
