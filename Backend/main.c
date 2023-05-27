#include<stdio.h>
#include<string.h>
#include"document.h"

int main()
{
    // Code for getting a single document
    // document *d= getDocument("Posts","post1");
    // if(d) displayDocument(*d);

    // Code for freeing the pairs
    // freePairs(&(d->pairs));
    // if(!d->pairs) printf("deleted");
  
    // Code for creating and initlizing the doucment
    // Pair pairs;
    // initPair(&pairs);
    // createPair(&pairs, "name", "Sohel Bargir","string");
    // createPair(&pairs, "subject", "DSA","string");
    // createPair(&pairs, "College", "COEP","string");

    // document* doc = initilizeAndCreateDocument("documentpath", pairs);
    // int result = createDocument("Posts", doc);


    // Code for getting all documents from collection
    // Collection col = getAllDocumentFromCollection("Posts");
    // displayCollection(col);

    // Code for updating a single document
    // Pair pairs;
    // initPair(&pairs);
    // createPair(&pairs, "name", "Aditya Raul","string");
    // createPair(&pairs, "subject", "DSA","string");
    // createPair(&pairs, "College", "COEP","string");

    // document* doc = initilizeAndCreateDocument("documentpath", pairs);
    // int status = updateDocument("Posts", doc);

    // Code for deleting a single document
    // int status = deleteDocument("Posts", "newpost");

    // Code for deleting a single field from a document
    int status = deleteFieldFromDocument("Posts", "post1", "name");
    // if(status) printf("document field deleted\n");


    // Code for converting document structure into json object string
    // document *d= getDocument("Posts","post1");
    // if(d) displayDocument(*d);

    // document *d1= getDocument("Posts","post2");
    // if(d1) displayDocument(*d1);

    // document *d2= getDocument("Posts","documentpath");
    // if(d2) displayDocument(*d2);
    // printf("%s\n", convertSinglePairIntoJSONString(d->pairs->next));
    // printf("%s\n", convertSingleDocumentIntoJSONString(d));
    // printf("%s\n", convertSingleDocumentIntoJSONString(d1));
    // printf("%s\n", convertSingleDocumentIntoJSONString(d2));

    // printf("%s\n", jsonfiyCollection("Posts"));

    // exportCollection("Posts");
    // exportUser("sohel");

    return 0;
}