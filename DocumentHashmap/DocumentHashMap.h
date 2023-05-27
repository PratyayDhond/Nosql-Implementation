#include "../Backend/document.h"


typedef struct documentHashmap{
    int bf;
    char* key;
    char* value;
    char* datatype;
    struct documentHashmap* left;
    struct documentHashmap* right;          //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct documentHashmap* parent;         
}documentHashmap;

typedef documentHashmap* DocumentHashMap;

//Basic Tree functions
void initDocumentHashMap(DocumentHashMap* );
void destroyTree(DocumentHashMap* );
void removedocumentHashmap(DocumentHashMap*,char* );
Pair findAndFetchDocument(DocumentHashMap tdocumentHashmap,char* key);
void updateValue(DocumentHashMap*,char*,char*,char*);

//Traversals
void inOrder(DocumentHashMap );
void preOrder(DocumentHashMap );
