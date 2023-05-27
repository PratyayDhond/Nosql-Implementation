#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>
#include"document.h"
#include<limits.h>
#include "../globals/globals.h"
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
    if(strlen(key) == 0 || strlen(datatype) == 0 || strlen(value) == 0 ) return;

    node *nn = (node*) malloc(sizeof(node));
    nn->datatype = (char*) malloc(strlen(datatype)*sizeof(char));
    nn->key = (char*) malloc(strlen(key)*sizeof(char));
    nn->value = (char*) malloc(strlen(value)*sizeof(char));
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

// This is used to delete a single a pair from pairs linkedlist
int deletePair(Pair *pairs, char *pairKey)
{
    if(!(*pairs))
        return INT_MIN;

    if(strlen(pairKey)) return -1;
    node * temp;
    if (strcmp((*pairs)->key, pairKey) == 0) {

        temp = *pairs;
        *pairs = (*pairs)->next;
        free(temp);
        return 1;

    }else {
        node *current = *pairs;

        while (current->next) {
            if(strcmp(current->next->key, pairKey) == 0) {
                temp = current->next;
                current->next = current-> next->next;
                free(temp);
                return 1;
            }else
                current = current -> next;
    }
  }

  return 0;
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
    if(!collection || !doc) return;

    collectionNode *nn = (collectionNode*) malloc(sizeof(collectionNode));
    if(!nn)
        return;

    nn->document = doc;
    nn -> next = NULL;


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
        printf("%s\n", nn->document->documentId);
        nn = nn->next;
    }
}


// This function returns a single document as a document structure
document* getDocument(char *collection,char* documentId)
{
    FILE *file;

    if(strlen(collection) == 0 || strlen(documentId) == 0)
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
    while (documentId[i] != '\0') {
        if(documentId[i] == '\n') documentId[i] = '\0';
        // printf("%c ",key[i]);
        documentpath[j] = documentId[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    file = fopen(documentpath, "r");

    if(!file)
    {
        printf("document not found\n");
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
        free(pairs);
        printf("Cannot mallocate a document\n");
        return NULL;
    }

    doc->documentId = (char*) malloc(strlen(documentId)*sizeof(char));
    if(!doc->documentId) return NULL;
    strcpy(doc->documentId, documentId);
    doc->pairs = pairs;
    return doc;
    
}

void displayDocument(document doc)
{
    printf("Document Id: %s\n", doc.documentId);
    node* temp = doc.pairs;

    while(temp)
    {
        printf("(%s) %s: %s\n", temp->datatype, temp->key, temp->value);
        temp = temp -> next;
    }
}

int validateDataFormatProtocol(char* line)
{
    if(strlen(line) == 0) return 0;
     regex_t reegex;
 
    int value;

    value = regcomp(&reegex, "^\\(\\w+\\)\\s*\\w+:\\s*(.*)$",REG_EXTENDED|REG_NOSUB);
 
    value = regexec(&reegex, line,
                     0, NULL, 0);

    return value;
}

// return pairs linked list by fetching all key-value pairs from document 
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

        if(validateDataFormatProtocol(line) == REG_NOMATCH) 
        {
            printf("Error parsing the document\n");
            free(pairs);
            return NULL;
        }

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
            // if(line[lineTraverse] == '\0');

            key[counter++] = line[lineTraverse++];
        }
        lineTraverse++;

        key[counter] = '\0';

        counter = 0;
        while(line[lineTraverse] != '\0')
        {
            // if(value[counter] == '\n') value[counter] = '\0';
            value[counter++] = line[lineTraverse++];
        }
        value[counter] = '\0';
        appendToPair(&pairs, key, value, datatype);

        counter = 0, lineTraverse = 0;
    }

    fclose(file);

    return pairs;
}

// It returns all documents from collection as linkedlist named as Collection
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

// This function create key value pair mapping and attaches to a pairs linkedlist
void createPair(Pair *pairs,char* key, char* value, char* datatype)
{
    if(!pairs)
        return;

    appendToPair(pairs, key, value, datatype);
    return;
}

// This function accepts documentId and pairs as parameters and returns a document structure
document* initilizeAndCreateDocument(char* documentId, Pair pairs)
{
    document *doc = (document*) malloc(sizeof(document));
    
    if(!doc)
    {
        printf("Cannot mallocate a document\n");
        return NULL;
    }

    doc->documentId = (char*) malloc(sizeof(document));
    
    if(!doc->documentId) return NULL;
    
    strcpy(doc->documentId, documentId);
    doc->pairs = pairs;
    return doc;
}

// This function helps to create a single document
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
    while (doc->documentId[i] != '\0') {
        if(doc->documentId[i] == '\n') doc->documentId[i] = '\0';
        documentpath[j] = doc->documentId[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    // Checking whether the document is exists or not
    char command[200] = "test -f ./";

    strcat(command, collection);
    strcat(command, "/");
    strcat(command, doc->documentId);

    int status = system(command);

    if(!status) 
    {
        printf("Document already exists\n");
        return 0;
    }

    fp = fopen(documentpath, "w");

    if(!fp) return 0;

    node* temp = doc->pairs;


    while(temp)
    {
        fprintf(fp,"(%s) %s: %s\n", temp->datatype, temp->key, temp->value);
        temp = temp -> next;
    }

    printf("Document created successfully\n");
    fclose(fp);
    return 1;
}

// This function helps to update the document
int updateDocument(char* collection, document* doc)
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
    while (doc->documentId[i] != '\0') {
        if(doc->documentId[i] == '\n') doc->documentId[i] = '\0';
        documentpath[j] = doc->documentId[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    // Checking whether the document is exists or not
    char command[200] = "test -f ./";

    strcat(command, collection);
    strcat(command, "/");
    strcat(command, doc->documentId);

    int status = system(command);

    if(status) 
    {
        printf("Document does not exist\n");
        return 0;
    }

    fp = fopen(documentpath, "w");

    if(!fp) return 0;

    node* temp = doc->pairs;


    while(temp)
    {
        fprintf(fp,"(%s) %s: %s", temp->datatype, temp->key, temp->value);
        temp = temp -> next;
    }

    printf("Document updated successfully\n");
    fclose(fp);
    return 1;
}

// This function helps to delete a single document
int deleteDocument(char* collection, char* documentKey)
{
    if(strlen(documentKey) == 0) return 0;

    if(strlen(collection) == 0) return 0;

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
    while (documentKey[i] != '\0') {
        if(documentKey[i] == '\n') documentKey[i] = '\0';
        documentpath[j] = documentKey[i];
        i++;
        j++;
    }

    documentpath[j] = '\0';
    // Checking whether the document is exists or not
    char command[200] = "test -f ./";

    strcat(command, collection);
    strcat(command, "/");
    strcat(command, documentKey);

    int status = system(command);

    if(status) 
    {
        printf("Document does not exist\n");
        return 0;
    }

    char del[200] = "rm ";

    strcat(del, collection);
    strcat(del, "/");
    strcat(del, documentKey);

    if(system(del))
    {
        printf("Error deleting a document\n");
        return 0;
    }

    printf("Document deleted successfully\n");
    return 1;
}

// This function helps to delete single field from document
int deleteFieldFromDocument(char* collection, char* documentKey, char *pairkey)
{
    if(strlen(collection) == 0) return 0;
    if(strlen(documentKey) == 0) return 0;

    document *doc = getDocument(collection, documentKey);

    if(!doc) return 0;

    if(!(doc->pairs)) return 0;

    if(!deletePair(&(doc->pairs), pairkey))
    {
        printf("Associated value for given key not found\n");
        return 0;
    }else{
    }

    if(updateDocument(collection, doc))
    {
        printf("%s field is deleted successfully\n", pairkey);
        return 1;
    }

    return 0;

}

// freeing up memory of pairs in a document
int freePairs(Pair *pairs)
{
    if(!*pairs) return 0;

    while(*pairs)
    {
        node* temp = (*pairs);
        *pairs = (*pairs) -> next;
        free(temp);
    }

    return 1;
}

// freeing up memory of a single document
int freeDocument(document* document)
{
    if(!document) return 0;

    Pair pairs = document->pairs;
    freePairs(&pairs);
    free(document);
}

// freeing up memory of a single collection
int freeCollection(Collection *collection)
{
    if(!*collection) return 0;

    while(*collection)
    {
        collectionNode* temp = (*collection);
        *collection = (*collection) -> next;
        document* doc = temp->document;
        freeDocument(doc);
        free(temp);
    }

    return 1;
}

char* convertSingleDocumentIntoJSONString(document *doc)
{
    return NULL;
}

char* jsonify(Collection collection)
{
    if(!collection) return NULL;

    collectionNode* temp = collection;

    FILE *fileptr;

    char filename[MAX_LINE_LENGTH];
    strcat(filename, "users");
    strcat(filename, ".json");
    fileptr = fopen(filename, "w+");

    if(!fileptr) return NULL; 

    char collectionJSONString[MAX_LINE_LENGTH];
    strcat(collectionJSONString, "[\n");

    while(temp)
    {
        document* doc = temp->document;
        char* documentJSONString = convertSingleDocumentIntoJSONString(doc);
        strcat(collectionJSONString, documentJSONString);
        temp = temp -> next;
    }

    strcat(collectionJSONString, "]");

    // return collectionJSONString;
}