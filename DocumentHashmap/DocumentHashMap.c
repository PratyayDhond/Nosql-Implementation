#include <stdio.h>
#include <stdlib.h>
#include "DocumentHashMap.h"
#include <string.h>
#include <limits.h>

int max(int a, int b)
{
   return a > b ? a : b;
}

int heightOfTree(DocumentHashMap tdocumentHashmap)
{
    if (!tdocumentHashmap)
        return -1;

    return 1 + max(heightOfTree(tdocumentHashmap->left), heightOfTree(tdocumentHashmap->right));
}

void initDocumentHashMap(DocumentHashMap *tdocumentHashmap)
{
    *tdocumentHashmap = NULL; // Initializing a structure
}

void reassignBalanceFactor(DocumentHashMap *tdocumentHashmap)
{
    documentHashmap* temp = *tdocumentHashmap;
    while (temp)
    {
        temp->bf = heightOfTree(temp->left) - heightOfTree(temp->right); // Assigning balance factor to documentHashmap as left height - right height
        temp = temp->parent;
    }
    return;
}

DocumentHashMap getimBalancedNode(DocumentHashMap tdocumentHashmap)
{
    if (!tdocumentHashmap)
        return NULL;
    documentHashmap* temp = tdocumentHashmap; // Imbalanaced documentHashmap is that documentHashmap who has balance factor apart from 0,1,-1
    while (temp)
    {
        if (temp->bf >= 2 || temp->bf <= -2)
            return temp;  // Traversing whole the parent ancestor tree for finding imbalanced documentHashmap
        temp = temp->parent;
    }
    return NULL;
}


void LLRotation(DocumentHashMap *tdocumentHashmap, DocumentHashMap *mainTdocumentHashmap)  //Rotate whole tree in right direction
{
    documentHashmap* A = (*tdocumentHashmap);
    documentHashmap* B = A->left;
    documentHashmap* BR = B->right;
    documentHashmap* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTdocumentHashmap = B;
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
    A->bf = B->bf = 0;

    reassignBalanceFactor(&A);          //We have rotated the tree using pointers , now reassingning its bf
    return;
}

void RRRotation(DocumentHashMap *tdocumentHashmap, DocumentHashMap *mainTdocumentHashmap) //Rotate tree to left
{
    documentHashmap* A = (*tdocumentHashmap);
    documentHashmap* B = A->right;
    documentHashmap* BR = B->left;
    documentHashmap* AP = A->parent;
    B->parent = AP;
    if (!AP)
        *mainTdocumentHashmap = B;
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
    A->bf = B->bf = 0;
    reassignBalanceFactor(&A);  //We have rotated the tree using pointers , now reassingning its bf
}
void LRRotation(DocumentHashMap *tdocumentHashmap, DocumentHashMap *mainTdocumentHashmap)
{
    RRRotation(&(*tdocumentHashmap)->left, mainTdocumentHashmap);     //Rotate left subtree and then rotate that updated tree to right
    LLRotation(tdocumentHashmap, mainTdocumentHashmap);
}

void RLRotation(DocumentHashMap *tdocumentHashmap, DocumentHashMap *mainTdocumentHashmap)
{
    LLRotation(&(*tdocumentHashmap)->right, mainTdocumentHashmap); //Rotate right subtree and then rotate that updated tree to left
    RRRotation((tdocumentHashmap), mainTdocumentHashmap);
}

void getBalancedTree(DocumentHashMap* tdocumentHashmap,documentHashmap* nodeImbalance){
     documentHashmap* imBalancedNode = getimBalancedNode(nodeImbalance);
  
    if (!imBalancedNode)
        return;
    // printf("\nImbalaned documentHashmap : %s , bf : %d\n", imBalancedNode->data, imBalancedNode->bf);
    if (imBalancedNode->bf == -2)
    {
        if (imBalancedNode->right->bf == 0 || imBalancedNode->right->bf == -1) 
            RRRotation(&imBalancedNode, tdocumentHashmap);
        else
            RLRotation(&imBalancedNode, tdocumentHashmap);
    }
    else if (imBalancedNode->bf == 2)
    {
        if (imBalancedNode->left->bf == 0 ||imBalancedNode->left->bf == 1 )
            LLRotation(&imBalancedNode, tdocumentHashmap);
        else  
            LRRotation(&imBalancedNode, tdocumentHashmap);        
    }
    return ;
}

DocumentHashMap mallocateAdocumentHashmap(DocumentHashMap *tdocumentHashmap,
char* key,char* value,char* datatype)
{
    documentHashmap *newdocumentHashmap = (documentHashmap*)malloc(sizeof(documentHashmap)); // Mallocating a documentHashmap and initializing the structure
    newdocumentHashmap -> key = (char*) malloc(sizeof(char) * strlen(key));
    newdocumentHashmap -> value = (char*) malloc(sizeof(char) * strlen(value));
    newdocumentHashmap -> datatype = (char*) malloc(sizeof(char) * strlen(datatype));

    strcpy(newdocumentHashmap -> key ,key);
    strcpy(newdocumentHashmap -> value ,value);
    strcpy(newdocumentHashmap -> datatype ,datatype);

    newdocumentHashmap->left = newdocumentHashmap->right = newdocumentHashmap->parent = NULL;
    newdocumentHashmap->bf = 0;
    return newdocumentHashmap;
}

void insertIntoDocumentHashMap(DocumentHashMap *tdocumentHashmap,char* key,char* value,char* datatype)
{

    documentHashmap* newdocumentHashmap = mallocateAdocumentHashmap(tdocumentHashmap, key,value,datatype);

    if (!*tdocumentHashmap)
    {
        *tdocumentHashmap = newdocumentHashmap;
        return;
    }
    documentHashmap* p = *tdocumentHashmap;
    documentHashmap* q = NULL;

    while (p)
    {
        q = p;
        int result = strcmp(p -> key , key);     //Return 0 -> strings are equal , 1 -> First string is greater, 2 -> second string is greater
        if (result == 0)
        {
            free(newdocumentHashmap);
            return;
        }
        else if (result > 0)        //If string 1 is greater , go left
            p = p->left;
        else
            p = p->right;
    }
    int res = strcmp(q-> key, key);
    if (res > 0)
        q->left = newdocumentHashmap;
    else
        q->right = newdocumentHashmap;

    newdocumentHashmap->parent = q;

   
    reassignBalanceFactor(&q);      //Reassinging balanace factor and  getting imbalanced documentHashmap
    getBalancedTree(tdocumentHashmap,q);
}

void inOrder(DocumentHashMap tdocumentHashmap)
{
    if (!tdocumentHashmap)
        return;

    inOrder(tdocumentHashmap->left);
    // printf("documentHashmap: %s , Parent : %s ,BF : %d , Left : %s , Right : %s\n", tdocumentHashmap->data.key,
        //    tdocumentHashmap->parent ? tdocumentHashmap->parent->data.key : "", tdocumentHashmap->bf, tdocumentHashmap->left ? tdocumentHashmap->left->data.key : "", tdocumentHashmap->right ? tdocumentHashmap->right->key : "");
    inOrder(tdocumentHashmap->right);
}
void preOrder(DocumentHashMap tdocumentHashmap)
{

    if (!tdocumentHashmap)
        return;

    // printf("Key : %s ", tdocumentHashmap -> documentName);

    printf(" { KEY : %s , VALUE : %s , DT : %s } \n",tdocumentHashmap->key ,tdocumentHashmap-> value,tdocumentHashmap -> datatype );
    preOrder(tdocumentHashmap->left);
    preOrder(tdocumentHashmap->right);
}

void removedocumentHashmapHelper(DocumentHashMap* parent,DocumentHashMap* tdocumentHashmap)
{
    if(!(*parent))
        return;
    reassignBalanceFactor(parent);
    getBalancedTree(tdocumentHashmap,*parent);

    if((*tdocumentHashmap) && (*tdocumentHashmap) -> parent &&  (*tdocumentHashmap) -> parent == (*parent))
        *tdocumentHashmap = *parent;
}

void removedocumentHashmap(DocumentHashMap *tdocumentHashmap, char *key)
{
    documentHashmap *p, *q;
    if (!*tdocumentHashmap)
        return;

    p = *tdocumentHashmap;
    while (p)
    {
        int result = strcmp(p -> key, key);
        if (result == 0)
            break;
        q = p; // Search for presence of documentHashmap and make pointer q following p
        if (result > 0)
            p = p->left;
        else
            p = p->right;
    }
    // if (p)
        // printf("%s Found\n", p->data);
    
    if (!p){
        // printf("\n %s Not Found\n", data);
        return; // documentHashmap not present
    }
    // Now 4 cases
    
    // leaf documentHashmap
    int flag = 0;
    if (!p->right && !p->left)
    {
        documentHashmap *deletedocumentHashmap = p;
        documentHashmap *temp = deletedocumentHashmap->parent;
        if (p == *tdocumentHashmap) // There is only 1 documentHashmap (root documentHashmap)
                *tdocumentHashmap = NULL;
        else
        {
            if (q->left == p)
                q->left = NULL;
            else
                q->right = NULL;
            
            p -> parent = NULL;
        }
        free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp,tdocumentHashmap);

        return;
    }
        //1 child -> Only left child exists
    if (!p->right && p->left)
    {
        documentHashmap* deletedocumentHashmap = p;
        documentHashmap* temp = deletedocumentHashmap->parent;
        if (p == *tdocumentHashmap) // There is root with only left child
        {
            p -> left -> parent = (*tdocumentHashmap) -> parent;
            *tdocumentHashmap = p->left;
        }
        else
        {
            if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
            p -> left -> parent = q;
        }

        free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp,tdocumentHashmap);

        return;
    }
    //1 Child , Only right child exists
    else if (p->right && !p->left)

    {
        documentHashmap* deletedocumentHashmap = p;
        documentHashmap* temp = deletedocumentHashmap->parent;
        if (p == *tdocumentHashmap)
        {
            p -> right -> parent = (*tdocumentHashmap) -> parent;
            *tdocumentHashmap = (deletedocumentHashmap->right);
        }
        else
        {
            if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
            
            p -> right -> parent = q;
        }
        free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp,tdocumentHashmap);

        return;
    }
    //2 Childs i.e there exits both left and right
    else if (p->right && p->left)
    {
        documentHashmap *temp, *preecedingPointer; // There is root with left and right child
        preecedingPointer = p->left;
        temp = preecedingPointer->right;
        documentHashmap* parentOfTemp = NULL;
        if (!temp)
        {
            p -> key = (char *)malloc(sizeof(preecedingPointer->key));
            strcpy(p -> key, preecedingPointer ->key);
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
            char *tempo = temp-> key;
            p->key = (char *)malloc(sizeof(p-> key));
            strcpy(p-> key, temp-> key);

            parentOfTemp = preecedingPointer;
            if(temp -> left){
                preecedingPointer -> right = temp -> left;
                temp -> left -> parent = preecedingPointer; //EDGE CASE , MISSING CASE
            }
            else
            preecedingPointer->right = NULL;
            free(temp);
        }
        removedocumentHashmapHelper(&parentOfTemp,tdocumentHashmap);
    }
}

void destroyTree(DocumentHashMap *tdocumentHashmap)
{
    if (!(*tdocumentHashmap))
        return;
    destroyTree(&(*tdocumentHashmap)->left);
    destroyTree(&(*tdocumentHashmap)->right);
    printf("\n%s Deleted\n", (*tdocumentHashmap) -> key);
    free(*tdocumentHashmap);
    *tdocumentHashmap = NULL;
    return;
}

Pair findAndFetchDocument(DocumentHashMap tdocumentHashmap,char* key){
    Pair temp ;
    initPair(&temp);
    documentHashmap* p = tdocumentHashmap;
    while(p){
        int result = strcmp(key,tdocumentHashmap  -> key);
        if(result == 0){
            appendToPair(&temp,tdocumentHashmap -> key,tdocumentHashmap -> value,
            tdocumentHashmap -> datatype);
            return temp; 
        }
        else if(result > 0)
            p = p -> left;
        else 
            p = p -> right;
    }
    return temp;
}

void updateValue(DocumentHashMap* tdocumentHashmap,char* key,char* value,char* datatype){
    documentHashmap* p = *tdocumentHashmap;
    while(p){
        int result = strcmp(key,p -> key);
        if(result == 0){
            // p -> value = (char*)malloc(sizeof( value));
            // p -> datatype = (char*)malloc(sizeof( datatype));
            strcpy(p -> value, value);
            strcpy(p -> datatype, datatype);
            return ; 
        }
        else if(result > 0)
            p = p -> left;
        else 
            p = p -> right;
    }
    return ;
}
