#include "../Backend/document.h"


typedef struct documentHashmap{
    int bf;
    char* key;
    char* value;
    char* datatype;
    // document *data;
    struct documentHashmap* left;
    struct documentHashmap* right;          //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct documentHashmap* parent;         
}documentHashmap;

typedef documentHashmap* DocumentHashMap;

//Basic Tree functions
void initDocumentHashMap(DocumentHashMap* );
void insertIntoDocumentHashMap(DocumentHashMap*,char*,char*,char*);
void destroyTree(DocumentHashMap* );
void removedocumentHashmap(DocumentHashMap*,char* );
Pair findAndFetchDocument(DocumentHashMap tdocumentHashmap,char* key);

void updateValue(DocumentHashMap*,char*,char*,char*);
// void insertIntoDocument(char* key,char *value,char* datatype);

//Traversals
void inOrder(DocumentHashMap );
void preOrder(DocumentHashMap );
