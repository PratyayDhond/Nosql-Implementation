#ifndef STACK_H
#define STACK_H

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
void insertIntoTree(HashMap *tnode,char* data);
void insertRecursivelyIntoTree(HashMap* tnode,int data);
HashMap removeNodeRecursive(HashMap *root , char* data);
void removeNodeHelper(HashMap* parent,HashMap*);
void destroyTree(HashMap* tnode);

int heightOfTree(HashMap tNode);
void removeNode(HashMap *tnode,char* data);

//Traversals
void inOrder(HashMap tnode);
void preOrder(HashMap tNode);
#endif
