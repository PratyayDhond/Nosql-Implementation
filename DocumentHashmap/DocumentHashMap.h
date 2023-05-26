#include "../FetchingDocument/document.h"


typedef struct documentHashmap{
    int bf;
    document *data;
    struct documentHashmap* left;
    struct documentHashmap* right;          //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct documentHashmap* parent;         
}documentHashmap;

typedef documentHashmap* DocumentHashMap;

//Basic Tree functions
void initDocumentHashMap(DocumentHashMap* );
void insertIntoDocumentHashMap(DocumentHashMap*,document);
void destroyTree(DocumentHashMap* );
void removedocumentHashmap(DocumentHashMap*,char* );
document findAndFetchDocument(DocumentHashMap ,char* );
void updateValue(DocumentHashMap*,char*,char*,char*);
// void insertIntoDocument(char* key,char *value,char* datatype);

//Traversals
void inOrder(DocumentHashMap );
void preOrder(DocumentHashMap );
