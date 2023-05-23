#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"
#include <string.h>
#include <limits.h>

HashMap mallocateANode(HashMap *tnode, char *data)
{
    Node *newnode = (Node*)malloc(sizeof(Node)); // Mallocating a node and initializing the structure
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->data = data;
    newnode->bf = 0;
    return newnode;
}
void initHashMap(HashMap *tnode)
{
    *tnode = NULL; // Initializing a structure
}

void reassignBalanceFactor(HashMap *tnode)
{
    Node* temp = *tnode;
    while (temp)
    {
        temp->bf = heightOfTree(temp->left) - heightOfTree(temp->right); // Assigning balance factor to node as left height - right height
        temp = temp->parent;
    }
    return;
}

HashMap getImBalancedNode(HashMap tnode)
{
    if (!tnode)
        return NULL;
    Node* temp = tnode; // Imbalanaced node is that node who has balance factor apart from 0,1,-1
    while (temp)
    {
        if (temp->bf >= 2 || temp->bf <= -2)
            return temp;  // Traversing whole the parent ancestor tree for finding imbalanced node
        temp = temp->parent;
    }
    return NULL;
}


void LLRotation(HashMap *tnode, HashMap *mainTNode)  //Rotate whole tree in right direction
{
    Node* A = (*tnode);
    Node* B = A->left;
    Node* BR = B->right;
    Node* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTNode = B;
    else
    {
        if (AP->right == A)
            AP->right = B;
        else
            AP->left = B;
    }
    A->parent = B;
    B->right = A;
    A->left = BR;
    if (BR)
        BR->parent = A;
    A->bf = 0;
    B->bf = 0;

    reassignBalanceFactor(&A);          //We have rotated the tree using pointers , now reassingning its bf

    return;
}

void RRRotation(HashMap *tnode, HashMap *mainTNode) //Rotate tree to left
{
    Node* A = (*tnode);
    Node* B = A->right;
    Node* BR = B->left;
    Node* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTNode = B;
    else
    {
        if (AP->right == A)
            AP->right = B;
        else
            AP->left = B;
    }
    A->parent = B;
    B->left = A;
    A->right = BR;
    if (BR)
        BR->parent = A;
    A->bf = 0;
    B->bf = 0;
    reassignBalanceFactor(&A);  //We have rotated the tree using pointers , now reassingning its bf
}
void LRRotation(HashMap *tnode, HashMap *mainTNode)
{
    RRRotation(&(*tnode)->left, mainTNode);     //Rotate left subtree and then rotate that updated tree to right
    LLRotation(tnode, mainTNode);
}

void RLRotation(HashMap *tnode, HashMap *mainTNode)
{
    LLRotation(&(*tnode)->right, mainTNode); //Rotate right subtree and then rotate that updated tree to left
    RRRotation((tnode), mainTNode);
}

void getBalancedTree(HashMap* tnode,Node* ImbalancedNode){
     Node* imBalancedNode = getImBalancedNode(ImbalancedNode);
  
    if (!imBalancedNode)
        return;
    
    // printf("\nImbalaned Node : %s , bf : %d\n", imBalancedNode->data, imBalancedNode->bf);
    if (imBalancedNode->bf == -2)
    {
        if (imBalancedNode->right->bf == 0 || imBalancedNode->right->bf == -1) 
            RRRotation(&imBalancedNode, tnode);
        else
            RLRotation(&imBalancedNode, tnode);
    }
    else if (imBalancedNode->bf == 2)
    {
        if (imBalancedNode->left->bf == 0 ||imBalancedNode->left->bf == 1 )
            LLRotation(&imBalancedNode, tnode);
        else  
            LRRotation(&imBalancedNode, tnode);        
    }
    return ;
}

void insertIntoTree(HashMap *tnode, char *data)
{
    Node* newnode = mallocateANode(tnode, data);
    if (!*tnode)
    {
        *tnode = newnode;
        return;
    }
    Node* p = *tnode;
    Node* q = NULL;

    while (p)
    {
        q = p;
        int result = strcmp(p->data, data);     //Return 0 -> strings are equal , 1 -> First string is greater, 2 -> second string is greater
        if (result == 0)
        {
            free(newnode);
            return;
        }
        else if (result > 0)        //If string 1 is greater , go left
            p = p->left;
        else
            p = p->right;
    }
    int res = strcmp(q->data, data);
    if (res > 0)
        q->left = newnode;

    else
        q->right = newnode;

    newnode->parent = q;
   
    reassignBalanceFactor(&q);      //Reassinging balanace factor and  getting imbalanced node
    getBalancedTree(tnode,q);
}

void inOrder(HashMap tnode)
{
    if (!tnode)
        return;

    inOrder(tnode->left);
    printf("Node: %s , Parent : %s ,BF : %d , Left : %s , Right : %s\n", tnode->data,
           tnode->parent ? tnode->parent->data : "", tnode->bf, tnode->left ? tnode->left->data : "", tnode->right ? tnode->right->data : "");
    inOrder(tnode->right);
}
void preOrder(HashMap tnode)
{

    if (!tnode)
        return;

    printf("N: %s  ,BF : %d , L : %s , R : %s , P : %s\n", tnode ? tnode->data : "",
           tnode->bf, tnode->left ? tnode->left->data : "", tnode->right ? tnode->right->data : "",tnode -> parent ? tnode -> parent -> data : "");

    preOrder(tnode->left);
    preOrder(tnode->right);
}

int max(int a, int b)
{
   return a > b ? a : b;
}
int heightOfTree(HashMap tNode)
{
    if (!tNode)
        return -1;

    return 1 + max(heightOfTree(tNode->left), heightOfTree(tNode->right));
}

void removeNodeHelper(HashMap* parent,HashMap* tnode)
{
    if(!(*parent))
        return;
    reassignBalanceFactor(parent);
    getBalancedTree(tnode,*parent);

    if((*tnode) && (*tnode) -> parent &&  (*tnode) -> parent == (*parent))
        *tnode = *parent;
}

void removeNode(HashMap *tnode, char *data)
{
    Node *p, *q;
    if (!*tnode)
        return;

    p = *tnode;
    while (p)
    {
        int result = strcmp(p->data, data);
        if (result == 0)
            break;
        q = p; // Search for presence of node and make pointer q following p
        if (result > 0)
            p = p->left;
        else
            p = p->right;
    }
    // if (p)
        // printf("%s Found\n", p->data);
    
    if (!p){
        // printf("\n %s Not Found\n", data);
        return; // Node not present
    }
    // Now 4 cases
    
    // leaf node
    int flag = 0;
    if (!p->right && !p->left)
    {
        Node *deleteNode = p;
        Node *temp = deleteNode->parent;
        if (p == *tnode) // There is only 1 node (root node)
                *tnode = NULL;
        else
        {
            if (q->left == p)
                q->left = NULL;
            else
                q->right = NULL;
            
            p -> parent = NULL;
        }
        free(deleteNode);
        removeNodeHelper(&temp,tnode);

        return;
    }
        //1 child -> Only left child exists
    if (!p->right && p->left)
    {
        Node* deleteNode = p;
        Node* temp = deleteNode->parent;
        if (p == *tnode) // There is root with only left child
        {
            p -> left -> parent = (*tnode) -> parent;
            *tnode = p->left;
        }
        else
        {
            if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
            p -> left -> parent = q;
        }

        free(deleteNode);
        removeNodeHelper(&temp,tnode);

        return;
    }
    //1 Child , Only right child exists
    else if (p->right && !p->left)
    {
        Node* deleteNode = p;
        Node* temp = deleteNode->parent;
        if (p == *tnode)
        {
            p -> right -> parent = (*tnode) -> parent;
            *tnode = (deleteNode->right);
        }
        else
        {
            if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
            
            p -> right -> parent = q;
        }
        free(deleteNode);
        removeNodeHelper(&temp,tnode);

        return;
    }
    //2 Childs i.e there exits both left and right
    else if (p->right && p->left)
    {
        Node *temp, *preecedingPointer; // There is root with left and right child
        preecedingPointer = p->left;
        temp = preecedingPointer->right;
        Node* parentOfTemp = NULL;
        if (!temp)
        {
            p->data = (char *)malloc(sizeof(preecedingPointer->data));
            strcpy(p->data, preecedingPointer->data);
            p->left = preecedingPointer->left;
            if(preecedingPointer -> left)
            preecedingPointer -> left -> parent = p;
            parentOfTemp = preecedingPointer->parent;
            free(preecedingPointer);
        }
        else
        {
            while (temp->right)
            {
                preecedingPointer = temp;
                temp = temp->right;
            }
            char *tempo = temp->data;
            (p)->data = (char *)malloc(sizeof(p->data));
            strcpy(p->data, temp->data);

            parentOfTemp = preecedingPointer;
            if(temp -> left){
                preecedingPointer -> right = temp -> left;
                temp -> left -> parent = preecedingPointer; //EDGE CASE , MISSING CASE
            }
            else
            preecedingPointer->right = NULL;
            free(temp);
        }
        removeNodeHelper(&parentOfTemp,tnode);
    }
}

void destroyTree(HashMap *tnode)
{
    if (!(*tnode))
        return;
    destroyTree(&(*tnode)->left);
    destroyTree(&(*tnode)->right);
    printf("\n%s Deleted\n", (*tnode)->data);
    free(*tnode);
    *tnode = NULL;
    return;
}