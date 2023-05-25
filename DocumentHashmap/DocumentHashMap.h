
typedef struct value {
    char* key;
    char* value;
    char* datatype;
}value;
typedef value* Values;
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
void insertIntoDocumentHashMap(DocumentHashMap*,char*,char*,char* );
void destroyTree(DocumentHashMap* );
void removedocumentHashmap(DocumentHashMap*,char* );
Values findAndFetchDocument(DocumentHashMap ,char* );
void updateValue(DocumentHashMap*,char*,char*,char*);

//Traversals
void inOrder(DocumentHashMap );
void preOrder(DocumentHashMap );
