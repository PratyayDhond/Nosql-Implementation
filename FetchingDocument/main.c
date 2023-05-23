#include<stdio.h>
#include"document.h"

int main()
{
    document *d= getDocument("Posts","post2");

    displayDocument(*d);

    return 0;
}