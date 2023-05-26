#include<stdio.h>
typedef struct node
{
    char *key, *value, *datatype;
    struct node* next;
} node;

typedef node* Pair;

typedef struct document
{
    char* key;
    Pair pairs;
} document;

typedef struct collectionNode
{
    document *document;
    struct collectionNode* next;
} collectionNode;

typedef collectionNode* Collection;

void initPair(Pair *pairs);
void appendToPair(Pair *pairs, char* key, char* value, char* datatype);
int createDocument(char* collection, document* doc);
int updateDocument(char* collection, document* doc);
int deleteDocument(char* collection, char* documentKey);
document* getDocument(char *collection ,char* documentkey);
Pair getAllPairsOfDocument(FILE *file);
Collection getAllDocumentFromCollection(char* collectionName);
void displayDocument(document doc);
void initCollection(Collection *collection);
void addDocumentToCollection(Collection *collection, document* doc);
void displayCollection(Collection collection);
document* initilizeAndCreateDocument(char* documentkey, Pair pairs);
void createPair(Pair *pairs,char* key, char* value, char* datatype);
int deleteFieldFromDocument(char* collection, char* documentKey, char *pairkey);
int deletePair(Pair *pairs, char *pairKey);
int freePairs(Pair* pairs);
int validateDataFormatProtocol(char* line);
