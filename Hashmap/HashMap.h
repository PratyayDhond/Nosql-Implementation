
typedef struct Document {
    char* key;
    char* value;
    int type ;
}Doc;

typedef struct Node{
    int bf;
    char* data;
    struct Node* left;
    struct Node* right;          //Maintaining data , balanace factor , left ,right and parent pointer for each node
    struct Node* parent;         
}Node;

typedef Node* HashMap;

//Basic Tree functions
void initHashMap(HashMap* tree);
void insertIntoHashMap(HashMap *tnode,char* data);
void destroyTree(HashMap* tnode);
void removeNode(HashMap *tnode,char* data);
char* getDocument(HashMap tnode,char* data);

//Traversals
void inOrder(HashMap tnode);
void preOrder(HashMap tNode);
