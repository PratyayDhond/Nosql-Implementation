#include<stdio.h>
#include<stdlib.h>
#ifndef MAIN_H
#define MAIN_H
#include "HashMap.h"
#include<limits.h>
#include<string.h>
#endif

int getCount(HashMap tnode){
    if(!tnode)
    return 0;
    return 1 + getCount(tnode -> left) + getCount(tnode -> right);
}
int main(){
    HashMap t;
    initHashMap(&t);

    char data[1000][1000];
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
        insertIntoTree(&t,data[k]);
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
   
    //  preOrder(t );

    return 0;
}