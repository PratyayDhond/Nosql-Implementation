#include <stdio.h>
#include <stdlib.h>
#include "Collections.h"
#include <string.h>
#include <limits.h>

int max(int a, int b)
{
   return a > b ? a : b;
}

int heightOfTree(Collections tcollectionNode)
{
    if (!tcollectionNode)
        return -1;

    return 1 + max(heightOfTree(tcollectionNode->left), heightOfTree(tcollectionNode->right));
}

Collections mallocateAcollectionNode(Collections *tcollectionNode, char *data)
{
    collectionNode *newcollectionNode = (collectionNode*)malloc(sizeof(collectionNode)); // Mallocating a collectionNode and initializing the structure
    newcollectionNode->left = NULL;
    newcollectionNode->right = NULL;
    newcollectionNode->parent = NULL;
    newcollectionNode->data = data;
    newcollectionNode->bf = 0;
    return newcollectionNode;
}
void initCollections(Collections *tcollectionNode)
{
    *tcollectionNode = NULL; // Initializing a structure
}

void reassignBalanceFactor(Collections *tcollectionNode)
{
    collectionNode* temp = *tcollectionNode;
    while (temp)
    {
        temp->bf = heightOfTree(temp->left) - heightOfTree(temp->right); // Assigning balance factor to collectionNode as left height - right height
        temp = temp->parent;
    }
    return;
}

Collections getImBalancedcollectionNode(Collections tcollectionNode)
{
    if (!tcollectionNode)
        return NULL;
    collectionNode* temp = tcollectionNode; // Imbalanaced collectionNode is that collectionNode who has balance factor apart from 0,1,-1
    while (temp)
    {
        if (temp->bf >= 2 || temp->bf <= -2)
            return temp;  // Traversing whole the parent ancestor tree for finding imbalanced collectionNode
        temp = temp->parent;
    }
    return NULL;
}


void LLRotation(Collections *tcollectionNode, Collections *mainTcollectionNode)  //Rotate whole tree in right direction
{
    collectionNode* A = (*tcollectionNode);
    collectionNode* B = A->left;
    collectionNode* BR = B->right;
    collectionNode* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTcollectionNode = B;
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

void RRRotation(Collections *tcollectionNode, Collections *mainTcollectionNode) //Rotate tree to left
{
    collectionNode* A = (*tcollectionNode);
    collectionNode* B = A->right;
    collectionNode* BR = B->left;
    collectionNode* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTcollectionNode = B;
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
void LRRotation(Collections *tcollectionNode, Collections *mainTcollectionNode)
{
    RRRotation(&(*tcollectionNode)->left, mainTcollectionNode);     //Rotate left subtree and then rotate that updated tree to right
    LLRotation(tcollectionNode, mainTcollectionNode);
}

void RLRotation(Collections *tcollectionNode, Collections *mainTcollectionNode)
{
    LLRotation(&(*tcollectionNode)->right, mainTcollectionNode); //Rotate right subtree and then rotate that updated tree to left
    RRRotation((tcollectionNode), mainTcollectionNode);
}

void getBalancedTree(Collections* tcollectionNode,collectionNode* ImbalancedcollectionNode){
     collectionNode* imBalancedcollectionNode = getImBalancedcollectionNode(ImbalancedcollectionNode);
  
    if (!imBalancedcollectionNode)
        return;
    // printf("\nImbalaned collectionNode : %s , bf : %d\n", imBalancedcollectionNode->data, imBalancedcollectionNode->bf);
    if (imBalancedcollectionNode->bf == -2)
    {
        if (imBalancedcollectionNode->right->bf == 0 || imBalancedcollectionNode->right->bf == -1) 
            RRRotation(&imBalancedcollectionNode, tcollectionNode);
        else
            RLRotation(&imBalancedcollectionNode, tcollectionNode);
    }
    else if (imBalancedcollectionNode->bf == 2)
    {
        if (imBalancedcollectionNode->left->bf == 0 ||imBalancedcollectionNode->left->bf == 1 )
            LLRotation(&imBalancedcollectionNode, tcollectionNode);
        else  
            LRRotation(&imBalancedcollectionNode, tcollectionNode);        
    }
    return ;
}

void setDocuments(Collections *tcollectionNode, char *data)
{
    collectionNode* newcollectionNode = mallocateAcollectionNode(tcollectionNode, data);
    if (!*tcollectionNode)
    {
        *tcollectionNode = newcollectionNode;
        return;
    }
    collectionNode* p = *tcollectionNode;
    collectionNode* q = NULL;

    while (p)
    {
        q = p;
        int result = strcmp(p->data, data);     //Return 0 -> strings are equal , 1 -> First string is greater, 2 -> second string is greater
        if (result == 0)
        {
            p -> data = (char*)malloc(sizeof(data));
            strcpy(p -> data,data);
            free(newcollectionNode);
            return;
        }
        else if (result > 0)        //If string 1 is greater , go left
            p = p->left;
        else
            p = p->right;
    }
    int res = strcmp(q->data, data);
    if (res > 0)
        q->left = newcollectionNode;
    else
        q->right = newcollectionNode;

    newcollectionNode->parent = q;
   
    reassignBalanceFactor(&q);      //Reassinging balanace factor and  getting imbalanced collectionNode
    getBalancedTree(tcollectionNode,q);
}

void inOrder(Collections tcollectionNode)
{
    if (!tcollectionNode)
        return;

    inOrder(tcollectionNode->left);
    printf("collectionNode: %s , Parent : %s ,BF : %d , Left : %s , Right : %s\n", tcollectionNode->data,
           tcollectionNode->parent ? tcollectionNode->parent->data : "", tcollectionNode->bf, tcollectionNode->left ? tcollectionNode->left->data : "", tcollectionNode->right ? tcollectionNode->right->data : "");
    inOrder(tcollectionNode->right);
}
void preOrder(Collections tcollectionNode)
{

    if (!tcollectionNode)
        return;

    printf("N: %s  ,BF : %d , L : %s , R : %s , P : %s\n", tcollectionNode ? tcollectionNode->data : "",
           tcollectionNode->bf, tcollectionNode->left ? tcollectionNode->left->data : "", tcollectionNode->right ? tcollectionNode->right->data : "",tcollectionNode -> parent ? tcollectionNode -> parent -> data : "");

    preOrder(tcollectionNode->left);
    preOrder(tcollectionNode->right);
}

void removecollectionNodeHelper(Collections* parent,Collections* tcollectionNode)
{
    if(!(*parent))
        return;
    reassignBalanceFactor(parent);
    getBalancedTree(tcollectionNode,*parent);

    if((*tcollectionNode) && (*tcollectionNode) -> parent &&  (*tcollectionNode) -> parent == (*parent))
        *tcollectionNode = *parent;
}

void removecollectionNode(Collections *tcollectionNode, char *data)
{
    collectionNode *p, *q;
    if (!*tcollectionNode)
        return;

    p = *tcollectionNode;
    while (p)
    {
        int result = strcmp(p->data, data);
        if (result == 0)
            break;
        q = p; // Search for presence of collectionNode and make pointer q following p
        if (result > 0)
            p = p->left;
        else
            p = p->right;
    }
    // if (p)
        // printf("%s Found\n", p->data);
    
    if (!p){
        // printf("\n %s Not Found\n", data);
        return; // collectionNode not present
    }
    // Now 4 cases
    
    // leaf collectionNode
    int flag = 0;
    if (!p->right && !p->left)
    {
        collectionNode *deletecollectionNode = p;
        collectionNode *temp = deletecollectionNode->parent;
        if (p == *tcollectionNode) // There is only 1 collectionNode (root collectionNode)
                *tcollectionNode = NULL;
        else
        {
            if (q->left == p)
                q->left = NULL;
            else
                q->right = NULL;
            
            p -> parent = NULL;
        }
        free(deletecollectionNode);
        removecollectionNodeHelper(&temp,tcollectionNode);

        return;
    }
        //1 child -> Only left child exists
    if (!p->right && p->left)
    {
        collectionNode* deletecollectionNode = p;
        collectionNode* temp = deletecollectionNode->parent;
        if (p == *tcollectionNode) // There is root with only left child
        {
            p -> left -> parent = (*tcollectionNode) -> parent;
            *tcollectionNode = p->left;
        }
        else
        {
            if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
            p -> left -> parent = q;
        }

        free(deletecollectionNode);
        removecollectionNodeHelper(&temp,tcollectionNode);

        return;
    }
    //1 Child , Only right child exists
    else if (p->right && !p->left)
    {
        collectionNode* deletecollectionNode = p;
        collectionNode* temp = deletecollectionNode->parent;
        if (p == *tcollectionNode)
        {
            p -> right -> parent = (*tcollectionNode) -> parent;
            *tcollectionNode = (deletecollectionNode->right);
        }
        else
        {
            if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
            
            p -> right -> parent = q;
        }
        free(deletecollectionNode);
        removecollectionNodeHelper(&temp,tcollectionNode);

        return;
    }
    //2 Childs i.e there exits both left and right
    else if (p->right && p->left)
    {
        collectionNode *temp, *preecedingPointer; // There is root with left and right child
        preecedingPointer = p->left;
        temp = preecedingPointer->right;
        collectionNode* parentOfTemp = NULL;
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
        removecollectionNodeHelper(&parentOfTemp,tcollectionNode);
    }
}

void destroyTree(Collections *tcollectionNode)
{
    if (!(*tcollectionNode))
        return;
    destroyTree(&(*tcollectionNode)->left);
    destroyTree(&(*tcollectionNode)->right);
    printf("\n%s Deleted\n", (*tcollectionNode)->data);
    free(*tcollectionNode);
    *tcollectionNode = NULL;
    return;
}

char* getDocument(Collections tcollectionNode,char* data){
    collectionNode* p = tcollectionNode;
    while(p){
        int result = strcmp(data,tcollectionNode -> data);
        if(result == 0){
            return data; 
        }
        else if(result > 0)
            p = p -> left;
        else 
            p = p -> right;
    }
    return NULL;
}