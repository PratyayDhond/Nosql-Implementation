typedef struct collectionNode{
    int bf;
    char* data;
    struct collectionNode* left;
    struct collectionNode* right;     //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct collectionNode* parent;         
}collectionNode;

typedef collectionNode* Collections;

//Basic Tree functions
void initCollections(Collections* tree);
void setDocuments(Collections *tnode,char* data);
void destroyTree(Collections* tnode);
void removeNode(Collections *tnode,char* data);
char* getDocument(Collections tnode,char* data);

//Traversals
void inOrder(Collections tnode);
void preOrder(Collections tNode);
