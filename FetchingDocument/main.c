#include<stdio.h>
#include<string.h>
#include"document.h"

int main()
{
    document *d= getDocument("Posts","post3");

    if(d) displayDocument(*d);

    strcpy(d->key,"sohel");


    int result = createDocument("Posts", d);

    // Collection col = getAllDocumentFromCollection("Posts");

    // displayCollection(col);

    return 0;
}