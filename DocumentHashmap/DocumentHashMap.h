#include "../Backend/document.h"
// #include ""
typedef struct documentHashmap{
    int bf;
    char* key;
    char* value;
    char* datatype;
    struct documentHashmap* left;
    struct documentHashmap* right;      //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct documentHashmap* parent;         
}documentHashmap;

typedef documentHashmap* DocumentHashMap;

//Basic Tree functions
void initDocumentHashMap(DocumentHashMap* );
// void helpInsertingIntoDocumentFile(Pair*,DocumentHashMap* ,char*,char*);
void destroyTree(DocumentHashMap* );
int removedocumentHashmap(DocumentHashMap*,char* );
Pair findAndFetchDocument(DocumentHashMap ,char* );
void updateValue(DocumentHashMap*,char*,char*,char*);

//Traversals
void preOrder(DocumentHashMap);
