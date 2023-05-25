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

// For initilizing the collection linkedlist
void initCollection(Collection *c)
{
    *c = NULL;
    return;
}

// For appending document to collection linkedlist
void addDocumentToCollection(Collection *collection, document* doc)
{
    collectionNode *nn = (collectionNode*) malloc(sizeof(collectionNode));
    nn->document = doc;
    nn -> next = NULL;

    if(!nn)
        return;

    if(!(*collection))
    {
        *collection = nn;
        return;
    }

    collectionNode *temp = *collection;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp -> next = nn;
    return;
}

void displayCollection(Collection collection)
{
    if(!collection) return;

    collectionNode* nn = collection;

    while(nn)
    {
        printf("%s\n", nn->document->key);
        nn = nn->next;
    }
}


// this function returns a single document as a document structure
document* getDocument(char *collection,char* key)
{
    FILE *file;

    if(strlen(collection) == 0 || strlen(key) == 0)
        return NULL;

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
        if(key[i] == '\n') key[i] = '\0';
        // printf("%c ",key[i]);
        documentpath[j] = key[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    file = fopen(documentpath, "r");

    if(!file)
    {
        printf("file not found\n");
        return NULL;
    }
   
    Pair pairs = getAllPairsOfDocument(file);

    if(!pairs)
    {
        printf("Pairs not found\n");
        return NULL;
    }

    document *doc = (document*) malloc(sizeof(document));
    
    if(!doc)
    {
        printf("Cannot mallocate a document\n");
        return NULL;
    }

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

Collection getAllDocumentFromCollection(char* collectionName)
{
    Collection collection;
    initCollection(&collection);

    if(!collectionName)
        return 0;

    FILE *fp;
    char command[200] = "test -d ";

    strcat(command, collectionName);
    int status = system(command);
    
    // if collection directory not exists then simply return
    if(status)
        return 0;

    char listCommand[200] = "ls ./";
    strcat(listCommand, collectionName);
    fp = popen(listCommand, "r");

    if(!fp) return 0;

    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, fp)){
    
        document *doc = getDocument(collectionName, line);
        if(!doc)
        {
            free(collection);
            return 0;
        }
        addDocumentToCollection(&collection, doc);
    }

    fclose(fp);

    return collection;

}


document* initilizeAndCreateDocument(char* key, Pair pairs)
{
    document *doc = (document*) malloc(sizeof(document));
    
    if(!doc)
    {
        printf("Cannot mallocate a document\n");
        return NULL;
    }

    doc->key = (char*) malloc(sizeof(key));
    strcpy(doc->key, key);
    doc->pairs = pairs;
    return doc;
}

int createDocument(char* collection, document* doc)
{
    if(!doc) return 0;

    if(strlen(collection) == 0) return 0;

    FILE *fp;
    
    // concatinating collection name and document key
    char documentpath[MAX_LINE_LENGTH];
    
    int i=0, j=0;

    while (collection[i] != '\0') {
        documentpath[j] = collection[i];
        i++;
        j++;
    }
    documentpath[j++] = '/';
   
    i = 0;
    while (doc->key[i] != '\0') {
        if(doc->key[i] == '\n') doc->key[i] = '\0';
        // printf("%c ",key[i]);
        documentpath[j] = doc->key[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    printf("%s\n", documentpath);

    fp = fopen(documentpath, "w");

    if(!fp) return 0;

    node* temp = doc->pairs;

    // displayDocument(*doc);

    // while(temp)
    // {
        // strcat(temp->datatype, temp->key);
        // strcat(temp->datatype, temp->value);
        size_t stringLength = strlen(temp->value);

        size_t elementsWritten = fwrite(temp->value, sizeof(char), stringLength, fp);
        if (elementsWritten != stringLength) {
            printf("Error writing data to the file.\n");
            fclose(fp);
            return 1;
        }
    //     temp = temp -> next;
    // }
    // printf("\n");
    // fclose(fp);
    // return 1;
}