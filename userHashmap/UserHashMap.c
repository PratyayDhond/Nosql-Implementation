#include <stdio.h>
#include <stdlib.h>
#include "UserHashMap.h"
#include <string.h>
#include <limits.h>

int max(int a, int b)
{
   return a > b ? a : b;
}

int heightOfTree(UserHashMap tcollectionNode)
{
    if (!tcollectionNode)
        return -1;

    return 1 + max(heightOfTree(tcollectionNode->left), heightOfTree(tcollectionNode->right));
}

UserHashMap mallocateAcollectionNode(UserHashMap *tcollectionNode, char *data)
{
    userHashMapNode *newcollectionNode = (userHashMapNode*)malloc(sizeof(userHashMapNode)); // Mallocating a userHashMapNode and initializing the structure
    newcollectionNode->left = NULL;
    newcollectionNode->right = NULL;
    newcollectionNode->parent = NULL;
    newcollectionNode->data = data;
    newcollectionNode->bf = 0;
    return newcollectionNode;
}
void initCollections(UserHashMap *tcollectionNode)
{
    *tcollectionNode = NULL; // Initializing a structure
}

void reassignBalanceFactor(UserHashMap *tcollectionNode)
{
    userHashMapNode* temp = *tcollectionNode;
    while (temp)
    {
        temp->bf = heightOfTree(temp->left) - heightOfTree(temp->right); // Assigning balance factor to userHashMapNode as left height - right height
        temp = temp->parent;
    }
    return;
}

UserHashMap getimBalancedNode(UserHashMap tcollectionNode)
{
    if (!tcollectionNode)
        return NULL;
    userHashMapNode* temp = tcollectionNode; // Imbalanaced userHashMapNode is that userHashMapNode who has balance factor apart from 0,1,-1
    while (temp)
    {
        if (temp->bf >= 2 || temp->bf <= -2)
            return temp;  // Traversing whole the parent ancestor tree for finding imbalanced userHashMapNode
        temp = temp->parent;
    }
    return NULL;
}


void LLRotation(UserHashMap *tcollectionNode, UserHashMap *mainTcollectionNode)  //Rotate whole tree in right direction
{
    userHashMapNode* A = (*tcollectionNode);
    userHashMapNode* B = A->left;
    userHashMapNode* BR = B->right;
    userHashMapNode* AP = A->parent;
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

void RRRotation(UserHashMap *tcollectionNode, UserHashMap *mainTcollectionNode) //Rotate tree to left
{
    userHashMapNode* A = (*tcollectionNode);
    userHashMapNode* B = A->right;
    userHashMapNode* BR = B->left;
    userHashMapNode* AP = A->parent;
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
void LRRotation(UserHashMap *tcollectionNode, UserHashMap *mainTcollectionNode)
{
    RRRotation(&(*tcollectionNode)->left, mainTcollectionNode);     //Rotate left subtree and then rotate that updated tree to right
    LLRotation(tcollectionNode, mainTcollectionNode);
}

void RLRotation(UserHashMap *tcollectionNode, UserHashMap *mainTcollectionNode)
{
    LLRotation(&(*tcollectionNode)->right, mainTcollectionNode); //Rotate right subtree and then rotate that updated tree to left
    RRRotation((tcollectionNode), mainTcollectionNode);
}

void getBalancedTree(UserHashMap* tcollectionNode,userHashMapNode* nodeToCheck){
     userHashMapNode* imBalancedNode = getimBalancedNode(nodeToCheck);
  
    if (!imBalancedNode)
        return;
    // printf("\nImbalaned userHashMapNode : %s , bf : %d\n", imBalancedNode->data, imBalancedNode->bf);
    if (imBalancedNode->bf == -2)
    {
        if (imBalancedNode->right->bf == 0 || imBalancedNode->right->bf == -1) 
            RRRotation(&imBalancedNode, tcollectionNode);
        else
            RLRotation(&imBalancedNode, tcollectionNode);
    }
    else if (imBalancedNode->bf == 2)
    {
        if (imBalancedNode->left->bf == 0 ||imBalancedNode->left->bf == 1 )
            LLRotation(&imBalancedNode, tcollectionNode);
        else  
            LRRotation(&imBalancedNode, tcollectionNode);        
    }
    return ;
}

void setDocuments(UserHashMap *tcollectionNode, char *data)
{
    userHashMapNode* newcollectionNode = mallocateAcollectionNode(tcollectionNode, data);
    if (!*tcollectionNode)
    {
        *tcollectionNode = newcollectionNode;
        return;
    }
    userHashMapNode* p = *tcollectionNode;
    userHashMapNode* q = NULL;

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
   
    reassignBalanceFactor(&q);      //Reassinging balanace factor and  getting imbalanced userHashMapNode
    getBalancedTree(tcollectionNode,q);
}

void inOrder(UserHashMap tcollectionNode)
{
    if (!tcollectionNode)
        return;

    inOrder(tcollectionNode->left);
    printf("userHashMapNode: %s , Parent : %s ,BF : %d , Left : %s , Right : %s\n", tcollectionNode->data,
           tcollectionNode->parent ? tcollectionNode->parent->data : "", tcollectionNode->bf, tcollectionNode->left ? tcollectionNode->left->data : "", tcollectionNode->right ? tcollectionNode->right->data : "");
    inOrder(tcollectionNode->right);
}
void preOrder(UserHashMap tcollectionNode)
{

    if (!tcollectionNode)
        return;

    printf("N: %s  ,BF : %d , L : %s , R : %s , P : %s\n", tcollectionNode ? tcollectionNode->data : "",
           tcollectionNode->bf, tcollectionNode->left ? tcollectionNode->left->data : "", tcollectionNode->right ? tcollectionNode->right->data : "",tcollectionNode -> parent ? tcollectionNode -> parent -> data : "");

    preOrder(tcollectionNode->left);
    preOrder(tcollectionNode->right);
}

void removecollectionNodeHelper(UserHashMap* parent,UserHashMap* tcollectionNode)
{
    if(!(*parent))
        return;
    reassignBalanceFactor(parent);
    getBalancedTree(tcollectionNode,*parent);

    if((*tcollectionNode) && (*tcollectionNode) -> parent &&  (*tcollectionNode) -> parent == (*parent))
        *tcollectionNode = *parent;
}

void removecollectionNode(UserHashMap *tcollectionNode, char *data)
{
    userHashMapNode *p, *q;
    if (!*tcollectionNode)
        return;

    p = *tcollectionNode;
    while (p)
    {
        int result = strcmp(p->data, data);
        if (result == 0)
            break;
        q = p; // Search for presence of userHashMapNode and make pointer q following p
        if (result > 0)
            p = p->left;
        else
            p = p->right;
    }
    // if (p)
        // printf("%s Found\n", p->data);
    
    if (!p){
        // printf("\n %s Not Found\n", data);
        return; // userHashMapNode not present
    }
    // Now 4 cases
    
    // leaf userHashMapNode
    int flag = 0;
    if (!p->right && !p->left)
    {
        userHashMapNode *deletecollectionNode = p;
        userHashMapNode *temp = deletecollectionNode->parent;
        if (p == *tcollectionNode) // There is only 1 userHashMapNode (root userHashMapNode)
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
        userHashMapNode* deletecollectionNode = p;
        userHashMapNode* temp = deletecollectionNode->parent;
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
        userHashMapNode* deletecollectionNode = p;
        userHashMapNode* temp = deletecollectionNode->parent;
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
        userHashMapNode *temp, *preecedingPointer; // There is root with left and right child
        preecedingPointer = p->left;
        temp = preecedingPointer->right;
        userHashMapNode* parentOfTemp = NULL;
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

void destroyTree(UserHashMap *tcollectionNode)
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



// If multiple collections per user
// char* getDocuments(UserHashMap tcollectionNode,char* data){
    // userHashMapNode* p = tcollectionNode;
    // while(p){
        // int result = strcmp(data,tcollectionNode -> data);
        // if(result == 0){
            // return data; 
        // }
        // else if(result > 0)
            // p = p -> left;
        // else 
            // p = p -> right;
    // }
    // return NULL;
// }