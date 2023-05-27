#include "../Backend/document.h"
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

// Basic Tree functions
void initDocumentHashMap();
int helpInsertingIntoDocumentFile(Pair*);
int helpRemoveFieldFromDocument(char* collectionName,char* documentName,char* key);
void destroyTree();
void showFieldsDocuments();
int removedocumentHashmap(char* );
Pair findAndFetchDocument(char* );
void updateValue(char*,char*,char*);
void destroyTree();

//Traversals
void preOrder();
