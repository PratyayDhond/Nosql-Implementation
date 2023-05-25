#include<stdio.h>
#include<stdlib.h>
#include "UserHashMap.h"
#include<limits.h>
#include<string.h>

int getCount(UserHashMap tnode){
    if(!tnode)
    return 0;
    return 1 + getCount(tnode -> left) + getCount(tnode -> right);
}
void initDocumentsIntoCollections(UserHashMap* t){
    FILE* fp;
    char ch;
    char data[1000][1000];
    int k = 0; 
    fp = fopen("names", "r");
     if (NULL == fp) {
        return ;
    }
  char str[1000];
      int i = 0;

    while (fscanf(fp, "%s", data[k]) != EOF) {
        setDocuments(t,data[k]);
        k++;
        i++;
    }
    k = 0 , i = 0 ;
    fclose(fp);
}
int main(){
    UserHashMap t;
    initCollections(&t);
    initDocumentsIntoCollections(&t);

    // setDocuments(&t,"sar");
    // setDocuments(&t,"sar");
    // printf("%s",getDocument(t,"sar"));
    // insertIntoHashMap(&t,"kul");

    // char data[1000][1000];
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
     preOrder(t );

    return 0;
}