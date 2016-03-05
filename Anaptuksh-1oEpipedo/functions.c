#include "defines.h"
#include "GraphLib.h"

List* createList(){
    List* list = (List *)malloc( sizeof( List ) );
    list->head = NULL;
    list->_size = 0;
    return list;
}

DList* createDList(){
    DList* list = (DList *)malloc( sizeof( DList ) );
    list->head = NULL;
    list->_size = 0;
    return list;
}

LNode* createLNode(int id,Edge* edge){
    LNode* lnode = (LNode *)malloc( sizeof( LNode ) ); // Allocate memory for an LNode
    lnode->next = lnode->prev = NULL;
    lnode->edge = edge;
    lnode->edge->endNodeID = id;
    lnode->edge->propEdge = edge->propEdge;
    return lnode;
}

DNode* createDNode(int id,int dist){

    DNode* dnode = (DNode *)malloc( sizeof( DNode )); // Allocate memory for an DNode
    dnode->next = dnode->prev = NULL;
    dnode->dist = dist;
    dnode->id = id;
    return dnode;
}

void addNewLNode(List* list,LNode* node){ //add a new LNode to list

    if (list->head == NULL)// If list is empty, change both head and tail pointers
        list->tail = list->head = node;
    else  // Else change the tail
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->_size++;
}

void addNewDNode(DList* list,DNode* dnode){ //add a new DNode to Dlist

    if (list->head == NULL)// If list is empty, change both head and tail pointers
        list->tail = list->head = dnode;
    else  // Else change the tail
    {
        list->tail->next = dnode;
        dnode->prev = list->tail;
        list->tail = dnode;
    }
    list->_size++;
}

void deleteLNode(List* list,LNode* node){ //delete a node from list
    if( list->head == NULL ) // if list is empty return without deleting
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node == list->tail){
        list->tail = node->prev;
    }
    if (node == list->head){
        list->head = node->next;
    }
    if (node->edge != NULL){
        free((int*)(node->edge->propEdge[1].property));
        free(node->edge->propEdge);
        free(node->edge);
    }
    free(node);
    list->_size--;
}

void deleteDNode(DList* list,DNode* node){ //delete a Dnode from list
    if( list->head == NULL ) // if list is empty return without deleting
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node == list->tail){
        list->tail = node->prev;
    }
    if (node == list->head){
        list->head = node->next;
    }
    free(node);
    list->_size--;
}

void destroyList(List *list){
    LNode* node = list->head;
    LNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteLNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyDList(DList *list){
    DNode* node = list->head;
    DNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteDNode(list,node);
        node = temp;
    }
    free(list);
}

DNode* check(DList* dlist,int id){ //check list for a particular id
    DNode* temp = dlist->head;
    DNode* node = NULL;
    while (temp != NULL){
        if(temp->id == id){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list
}

int hashFunction(int key,int round, int size){
    int i;
    i =  ldexp(size ,round);
    return ( key%i);
}

Node* partition(Node** array,int low,int high,int id){ //rearch array for a given id
    int mid;
    Node* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->id == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->id == id)
            return  array[mid];
        if(array[mid]->id > id)
            node = partition(array,low,mid,id); //next search the left part of array
        else
            node = partition(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

int findPosition(Node** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->id > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->id > id)
            value = findPosition(array,low,mid,id);//next search the left part of array
        else
            value = findPosition(array,mid+1,high,id);//next search the right part of array
    }
    return value;
}
