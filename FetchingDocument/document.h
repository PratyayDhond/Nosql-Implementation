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

void initPair(Pair *l);
void appendToPair(Pair *l, char* key, char* value, char* datatype);
document* getDocument(char *collection ,char* key);
Pair getAllPairsOfDocument(FILE *file);
void displayDocument(document doc);