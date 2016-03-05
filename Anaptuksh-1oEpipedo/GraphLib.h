
#ifndef GRAPHLIB_H_
#define GRAPHLIB_H_

/**
 * Properties (for test main)
 * Contains the properties/attributes of a node or edge
 */

struct properties {
    void* property;
};
typedef struct properties Properties;

/**
 * Pair of integers
 */
struct pair {
    int ID; // the id of a node
    int distance; //the distance from the node
};
typedef struct pair Pair;

typedef struct DNode{
    int id;
    int dist;
    struct DNode* next,*prev;
}DNode;

struct edge {
    int startNodeID;
    int endNodeID;
    Properties* propEdge;
};
typedef struct edge Edge;

typedef struct LNode{
    struct LNode *next,*prev;
    Edge* edge;
}LNode;

typedef struct List{
    LNode *head,*tail;
    int _size; //this shows number of neighbors of a person
}List;

typedef struct DList{
    DNode *head,*tail;
    int _size; //this shows number of neighbors of a person
}DList;

struct node {
    int id;
    Properties* properties; //properties of a person
    List* neighbors;
};
typedef struct node Node;

typedef struct Bucket{
    Node **BucketTable;
    int size;
    int records;
}Bucket;

struct graph {
    Bucket **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
    int records;
};
typedef struct graph Graph;

/**
 * ResultSet
 */
struct resultSet {
    DList* dlist;
    DNode* tempL;
    LNode* temp;
    Graph const*  graph;
};
typedef struct resultSet ResultSet;


/*Help functions for test main*/
Properties* createProperties(int number);
void setStringProperty(char* property, int index, Properties* p);
void setIntegerProperty(int property, int index, Properties* p);
char* getStringProperty(int index, Properties* p);
int getIntegerProperty(int index, Properties* p);
Node* createNode(int id, Properties* p);
Edge* createEdge(int startID, int endID, Properties* p);

/*Functions for implementation of part 1*/
Graph* createGraph(int m, int c);
int destroyGraph(Graph* g);
int insertNode(const Node* const n, Graph* g);
int insertEdge(int startID, const Edge* const e, Graph* g);
Node* lookupNode(int id, const Graph* const g);
int reachNode1(int startID, int endID, const Graph*  const g);
ResultSet* reachNodeN(int startID, const Graph*  const g);
int next(ResultSet* resultSet, Pair* pair);

List* createList();
LNode* createLNode();
void deleteLNode(List* list,LNode* node);
void addNewNode(List* list,LNode* node);
void destroyList(List *list);
int hashFunction(int key,int round, int size);
Node* partition(Node** array,int low,int high,int id);
int findPosition(Node** array,int low,int high,int id);
void addNewLNode(List* list,LNode* node);
DList* createDList();
DNode* createDNode(int id,int dist);
void addNewDNode(DList* list,DNode* node);
void deleteDNode(DList* list,DNode* node);
void destroyDList(DList *list);
DNode* check(DList* dlist,int id);
#endif /* GRAPHLIB_H_ */
