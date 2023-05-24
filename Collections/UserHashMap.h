typedef struct userHashMapNode{
    int bf;
    char* data;
    struct userHashMapNode* left;
    struct userHashMapNode* right;     //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct userHashMapNode* parent;         
}userHashMapNode;

typedef userHashMapNode* UserHashMap;

//Basic Tree functions
void initCollections(UserHashMap* tree);
void setDocuments(UserHashMap *tnode,char* data);
void destroyTree(UserHashMap* tnode);
void removeNode(UserHashMap *tnode,char* data);
char* getDocument(UserHashMap tnode,char* data);

//Traversals
void inOrder(UserHashMap tnode);
void preOrder(UserHashMap tNode);
