typedef struct node
{
    char *key, *value;
    char *datatype;
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

void initPair(Pair *l);
void appendToPair(Pair *l, char* key, char* value, char* datatype);
int createDocument(char* collection, document* doc);
int updateDocument(char* collection, document* doc);
int deleteDocument(char* collection, document* doc);
document* getDocument(char *collection ,char* key);
Pair getAllPairsOfDocument(FILE *file);
Collection getAllDocumentFromCollection(char* collectionName);
void displayDocument(document doc);
void initCollection(Collection *c);
void addDocumentToCollection(Collection *collection, document* doc);
void displayCollection(Collection collection);


