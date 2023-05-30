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
int insertIntoDocumentHashmap(Pair*);
int updateDocumentHashMap(Pair );
int removeFieldFromDocument(char* ,char* ,char* );

void showFieldsDocuments();
void destroyHashMap();
int searchTheDocumentInFile(char*);
