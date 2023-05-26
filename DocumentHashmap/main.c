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
    insertIntoDocumentHashMap(&t,"Name","Sarvesh","string");
    insertIntoDocumentHashMap(&t,"address","COEP","string");
    removedocumentHashmap(&t,"Name");
    updateValue(&t,"Name","Raul","string");


     preOrder(t);

    return 0;
}
