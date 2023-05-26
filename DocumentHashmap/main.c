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
    document data;
    initPair(&data.pairs);
    appendToPair(&data.pairs,"Name", "Sarvesh", "string");
    appendToPair(&data.pairs,"Address", "COEP", "string");

    document data1;
    data1.key = "raul";

    initPair(&data1.pairs);
    appendToPair(&data1.pairs,"Name", "Raul", "string");
    appendToPair(&data1.pairs,"Address", "Laturrr", "string");

    data.key = "sar";
    // displayDocument(data);
    insertIntoDocumentHashMap(&t,data);
    insertIntoDocumentHashMap(&t,data1);

    // document get = findAndFetchDocument(t,"sar");

    // displayDocument(data);
    // displayDocument(data1);


     preOrder(t);

    return 0;
}
/*
void testingFile()
{
    FILE* fp;
    char ch;
    int k = 0; 
    fp = fopen("data1.txt", "r");
     if (NULL == fp) {
        return 0;
    }
  char str[1000];
      int i = 0;

    while (fscanf(fp, "%s", data[k]) != EOF) {
        insertIntoHashMap(&t,data[k]);
        k++;
        i++;
    }
    k = 0 , i = 0 ;
    fclose(fp);
    int count = 0 ;
      while(t){
            removeNode(&t,t-> data);
     printf("\nTnode Count :  %d",getCount(t));
            count++;
            // printf("\n%d",count);
        }
}
*/