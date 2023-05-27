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
void disp(Pair docs){
    node* p = docs;
    while(p){
        printf("%s %s %s \n",p -> key , p -> value , p -> datatype);
        p = p -> next;
    }
    return;
}
int main(){
    // Pair new;
    // initPair(&new);
    // appendToPair(&new,"sarvesh","Sarvesh","string");
    // appendToPair(&new,"pratyay","COEP","string");
    // appendToPair(&new,"sohel","COEP","string");
    // appendToPair(&new,"aditya","COEP","string");
    // appendToPair(&new,"raul","COEP","string");

    // helpInsertingIntoDocumentFile(&new);

    return 0;
}
