#include<stdio.h>
#include"document.h"

int main()
{
    document *d= getDocument("Posts","post2");

    // displayDocument(*d);

    Collection col = getAllDocumentFromCollection("Posts");

   displayCollection(col);

    return 0;
}