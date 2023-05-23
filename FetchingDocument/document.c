#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"document.h"

#define MAX_LINE_LENGTH 1000000

// Initilizing the pairs linkedlist
void initPair(Pair *pairs)
{
    *pairs = NULL;
    return;
}

// For appending pair into pairs linkedlist
void appendToPair(Pair *pair, char* key, char* value, char* datatype)
{
    node *nn = (node*) malloc(sizeof(node));
    nn->datatype = (char*) malloc(sizeof(datatype));
    nn->key = (char*) malloc(sizeof(key));
    nn->value = (char*) malloc(sizeof(value));
    strcpy(nn->datatype, datatype);
    strcpy(nn->key, key);
    strcpy(nn->value, value);
    nn -> next = NULL;

    if(!nn)
        return;

    if(!(*pair))
    {
        *pair = nn;
        return;
    }

    node *temp = *pair;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp -> next = nn;
    return;
}

// this function returns a single document as a document structure
document* getDocument(char *collection,char* key)
{
    FILE *file; 

    // concatinating collection name and document key
    char documentpath[100];
    
    int i=0, j=0;

    while (collection[i] != '\0') {
        documentpath[j] = collection[i];
        i++;
        j++;
    }
    documentpath[j++] = '/';
   
    i = 0;
    while (key[i] != '\0') {
        documentpath[j] = key[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';

    file = fopen(documentpath, "r");

    if(!file)
        return NULL;

    Pair pairs = getAllPairsOfDocument(file);

    if(!pairs)
        return NULL;

    document *doc = (document*) malloc(sizeof(document));
    doc->key = (char*) malloc(sizeof(key));
    strcpy(doc->key, key);
    doc->pairs = pairs;

    return doc;
    
}

void displayDocument(document doc)
{
    printf("Document Id: %s\n", doc.key);
    node* temp = doc.pairs;

    while(temp)
    {
        printf("(%s) %s: %s\n", temp->datatype, temp->key, temp->value);
        temp = temp -> next;
    }
}

Pair getAllPairsOfDocument(FILE *file)
{
    // Initilizing pairs linked list
    Pair pairs; 
    initPair(&pairs);

    int lineTraverse = 0;
    int counter = 0;

    // To fetch data from file line by line 
    char line[MAX_LINE_LENGTH]; 

    // For extracting key, values and datatype fields from line
    char key[MAX_LINE_LENGTH], value[MAX_LINE_LENGTH], datatype[20];

    while(fgets(line, MAX_LINE_LENGTH, file)){
        if(line[lineTraverse++] == '(')
        {
            while(line[lineTraverse] != ')')
            {
                datatype[counter++] = line[lineTraverse++];
            }
            datatype[counter] = '\0';
        }
        lineTraverse++;
        counter = 0;

        while(line[lineTraverse] == ' ')
            lineTraverse++;
        
        while(line[lineTraverse] != ':')
        {
            key[counter++] = line[lineTraverse++];
        }
        lineTraverse++;

        key[counter] = '\0';

        counter = 0;
        while(line[lineTraverse] != '\0')
        {
            value[counter++] = line[lineTraverse++];
        }
        value[counter] = '\0';
        appendToPair(&pairs, key, value, datatype);

        counter = 0, lineTraverse = 0;
    }

    fclose(file);

    return pairs;
}

