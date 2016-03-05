#include "GraphLib.h"
#include "defines.h"

/************************************/
/* Implement for test main purposes */
/************************************/

 /**
 * Creates a properties object
 * number: the number of properties
 * return value: a properties object
 */
Properties* createProperties(int number) {
    Properties* properties;
    properties = malloc(number*sizeof(Properties));
    return properties;
}

/**
 * Sets a string property "property" in position "index"
 * property: the type of the property
 * index: the position of the property
 * p: the properties object
 */
void setStringProperty(char* property, int index, Properties* p) {
    p[index].property = (char*)property;
}

/**
 * Sets an integer property "property" in position "index"
 * property: the value of the property
 * index: the position of the property
 * p: the properties object
 */
void setIntegerProperty(int property, int index, Properties* p) {
    int *temp;
    temp = malloc(sizeof(int));
    *temp = property;
    p[index].property =(int*)temp;
}

/**
 * Gets a string property "property" from position "index"
 * index: the position of the requested property
 * p: the properties object
 * return value: the type of the property
 */
char* getStringProperty(int index, Properties* p) {
    return (char*)(p[index].property);
}

/**
 * Gets an integer property "property" from position "index"
 * index: the position of the requested property
 * p: the properties object
 * return value: the value of the property
 */
int getIntegerProperty(int index, Properties* p) {
     return *((int*)p[index].property);
}

/**
 * Creates a node with specific properties
 * id: the id of the node
 * p: the properties of the node
 * return value: the requested node
 */
Node* createNode(int id, Properties* p) {
    Node* node;
    node = malloc(sizeof(Node));
    node->id = id;
    node->properties = p;
    node->neighbors = createList();
    return node;
}

/**
 * Creates an edge with specific properties
 * startID: the id of the start node
 * endID: the id of the end node
 * p: the properties of the edge
 * return value: the requested edge
 */
Edge* createEdge(int startID, int endID, Properties* p) {
    Edge* edge;
    edge = malloc(sizeof(Edge));
    edge->startNodeID = startID;
    edge->endNodeID = endID;
    edge->propEdge = p;
    return edge;
}

void createBucket(Graph* graph,int position,int size){//creates a new bucket

    graph->HashTable[position]= malloc(sizeof(Bucket));
    if(graph->HashTable[position] == NULL ){
        printf("Error:not available memory\n");
        exit(1);
    }
    graph->HashTable[position]->BucketTable = malloc(size*sizeof(Node*));
    graph->HashTable[position]->size = size;
    graph->HashTable[position]->records = 0;
}
/************************************/
/* Implement for part 1 */
/************************************/

/* Creates an empty graph
 * m: size of hashtable
 * c: size of cells in a bucket
 * return value: an empty graph*/
Graph* createGraph(int m,int c){
    int i;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if(graph == NULL ){
        printf("Error:not available memory\n");
        exit(1);
    }
    graph->pointer = 0;
    graph->HT_Size = graph->Init_HT_Size = graph->NextSplitPointer =  m;
    graph->round = 0;
    graph->HashTable = malloc(m*sizeof(Bucket*));
    if(graph->HashTable == NULL ){
        printf("Error:not available memory\n");
        exit(1);
    }
    graph->InitBucketSize = c;
    for(i=0;i<m;i++)
        createBucket(graph,i,c);
    return graph; //return empty graph
}
/* Destroys a graph
 * g: the graph
 * return value: success/fail status */
int destroyGraph(Graph* graph) {
    int i,j,k;
    if(graph == NULL ){
        printf("Error:Graph already destroyed/empty\n");
        return 1; //return fail
    }
    for(i=0;i<graph->HT_Size;i++){
        for(j=0;j<graph->HashTable[i]->records;j++){
            destroyList(graph->HashTable[i]->BucketTable[j]->neighbors); //destroy neighbor list
            free(graph->HashTable[i]->BucketTable[j]->properties[2].property);
            free(graph->HashTable[i]->BucketTable[j]->properties);
            free(graph->HashTable[i]->BucketTable[j]);
        }
        free(graph->HashTable[i]->BucketTable);
        free(graph->HashTable[i]);
    }
    free(graph->HashTable);
    free(graph);
    return 0; //return success
}

/* Inserts a node in the graph
 * n: the node to insert
 * g: the graph
 * return value: success/fail status */
int insertNode(const Node* const node, Graph* graph) {
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    Bucket* temp,**temp1;
    Node* temp2,*temp3;

    bucket = hashFunction(node->id,graph->round,graph->Init_HT_Size);//find bucket that node should be placed
    if(bucket < graph->pointer)
        bucket = hashFunction(node->id,(graph->round)+1,graph->Init_HT_Size);
    if(graph->HashTable[bucket]->size == graph->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((graph->HashTable[bucket]->records)/(graph->InitBucketSize));
        temp = graph->HashTable[bucket];
        temp->BucketTable = realloc(graph->HashTable[bucket]->BucketTable,(tempNum+1)*graph->InitBucketSize*sizeof(Node*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error:not available memory\n");
            return 1;
        }
        graph->HashTable[bucket]->BucketTable = temp->BucketTable;
        graph->HashTable[bucket]->size += graph->InitBucketSize;
    }
    records = graph->HashTable[bucket]->records;
    position = findPosition(graph->HashTable[bucket]->BucketTable,0,records-1,node->id);//find position that node with given id should be placed
    temp2 = graph->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = graph->HashTable[bucket]->BucketTable[i+1];
        graph->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    graph->HashTable[bucket]->BucketTable[position]= (Node*)node;
    graph->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(graph->HashTable,((graph->HT_Size)+1)*sizeof(Bucket*));
        if(temp1 == NULL){
            printf("Error:not available memory\n");
            return 1;
        }
        graph->HashTable = temp1;
        graph->HT_Size++;
        createBucket(graph,(graph->HT_Size)-1,graph->InitBucketSize);
        records = graph->HashTable[graph->pointer]->records;
        graph->HashTable[graph->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(graph->HashTable[graph->pointer]->BucketTable[i]->id,(graph->round)+1,graph->Init_HT_Size);
            if(graph->HashTable[bucketSplit]->records == graph->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((graph->HashTable[bucketSplit]->records)/(graph->InitBucketSize));
                temp = graph->HashTable[bucketSplit];
                temp->BucketTable = realloc(graph->HashTable[bucketSplit]->BucketTable,(tempNum+1)*graph->InitBucketSize*sizeof(Node*));
                if(temp->BucketTable == NULL ){
                    printf("Error:not available memory\n");
                    return 1;
                }
                graph->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                graph->HashTable[bucketSplit]->size += graph->InitBucketSize;
            }
            //place the record
            graph->HashTable[bucketSplit]->BucketTable[graph->HashTable[bucketSplit]->records++] = graph->HashTable[graph->pointer]->BucketTable[i];
        }
        graph->pointer++;
    }
    if (graph->pointer == graph->NextSplitPointer){ //if HashTable is duplicated
        graph->pointer = 0; //pointer points buck at the beginning
        graph->round++; //a new round starts
        graph->NextSplitPointer*=2;
    }
    return 0;
}
/* Inserts an edge in the graph
 * startID: the id of the start node
 * e: the edge we want to add to the start node
 * g: the graph
 * return value: success/fail status */
int insertEdge(int startID, const Edge* const edge, Graph* graph) {
    Node* node;
    LNode* lnode;

    node = lookupNode(startID,graph);
    lnode = createLNode(edge->endNodeID,edge);//create node
    if (lnode == NULL)
        return 1;
    addNewLNode(node->neighbors,lnode);//and enter that node to list
    return 0;
}

/* Retrieves a node from the graph
 * nodeID: the if of node to retrieve
 * g: the graph
 * return value: the requested node */
Node* lookupNode(int id, const Graph* const graph) {
    int bucket;
    Node* node;

    bucket = hashFunction(id,graph->round,graph->Init_HT_Size);
    if(bucket < graph->pointer)
        bucket = hashFunction(id,(graph->round)+1,graph->Init_HT_Size);
    node = partition(graph->HashTable[bucket]->BucketTable,0,graph->HashTable[bucket]->records-1,id);
    if(node == NULL){
        printf("Node has not been found\n");
        return NULL;
    }
    else
        return node;
}

/* Finds shortest path distance between two nodes in an undirected graph with no edge weights
 * startID: the id of the start node
 * endID: the id of the end node
 * g: the graph
 * return value: the shortest path */
int reachNode1(int startID, int endID, const Graph* const g) {
    Node* node;
    LNode* temp;
    DNode* dnode,*tempL;
    DList* dlist;
    int dist,distance;

    if (startID == endID)
        return 0;
    dlist = createDList();
    dnode = createDNode(startID,0);
    addNewDNode(dlist,dnode);
    tempL = dlist->head;

    while(tempL!=NULL){//while DList is not empty
        node = lookupNode(tempL->id,g);
        temp = node->neighbors->head;
        while(temp !=NULL){ //for every neighbor of node
            if(temp->edge->endNodeID == endID){ //if targetID has been found
                distance = tempL->dist+1; //calculate shortest path
                destroyDList(dlist);
                return distance;//and return distance of shortest path
            }
            dnode = check(dlist,temp->edge->endNodeID);//else,check if neighbor is already in the list
            if(dnode == NULL){//if neighbor is not in the list
                dist = tempL->dist + 1;//calculate shortest path
                dnode =  createDNode(temp->edge->endNodeID,dist);//create node
                addNewDNode(dlist,dnode);//and add it to list
            }
            temp = temp->next;//if neighbor is already in the list, jump to the next neighbor
        }
        tempL = tempL->next;//when all neighbors are checked,go to the next node of Dlist
    }
    destroyDList(dlist);
    return INFINITY_REACH_NODE;
}

/* Finds shortest path distance between all reachable nodes from a given node
 * in an undirected graph with no edge weights
 * startID: the id of the start node
 * endID: the id of the end node
 * g: the graph
 * return value: a resultSet */
ResultSet* reachNodeN(int startID, const Graph* const g) {//return a struct that holds info required for gradual(onw step at a time)bfs
    DList * dlist;
    DNode* tempL,*tempD;
    LNode* temp;
    ResultSet* set;
    Node* node;

    set = (ResultSet*)malloc(sizeof(ResultSet));
    dlist = createDList();
    tempD = createDNode(startID,0);
    addNewDNode(dlist,tempD);
    node = lookupNode(startID,g);
    temp = node->neighbors->head;//1st neighbor of person with startID
    tempL = dlist->head;

    set->dlist = dlist;
    set->tempL = tempL;
    set->graph = g;
    set->temp = temp;
    return set;
}
/* Checks if another result is available
 * resultSet: the ResultSet returned by a reachNodeN call
 * pair: a Pair instance to hold the next result, the space for the Pair is
 * allocated by the caller
 * return value: 0 when the no more record is available, 1 when
 */
int next(ResultSet* resultSet, Pair* pair) {
    DNode* dnode;
    int dist;
    Node* node;

    while(resultSet->tempL!=NULL){//while DList is not empty
        while(resultSet->temp!=NULL){//for every neighbor of node
            dnode = check(resultSet->dlist,resultSet->temp->edge->endNodeID);//check if neighbor is already in the list
            if(dnode == NULL){//if neighbor is not in the list
                dist = resultSet->tempL->dist + 1;//calculate shortest path
                dnode =  createDNode(resultSet->temp->edge->endNodeID,dist);
                addNewDNode(resultSet->dlist,dnode);//and add it to list
                //create next pair and return
                pair->distance = dist;
                pair->ID = resultSet->temp->edge->endNodeID;
                return 1;
            }
            resultSet->temp = resultSet->temp->next;//go to next neighbor
        }
        resultSet->tempL = resultSet->tempL->next;//when all neighbors are checked,go to the next node of Dlist
        if(resultSet->tempL!=NULL){
            node= lookupNode(resultSet->tempL->id,resultSet->graph);
            resultSet->temp = node->neighbors->head;//take first neighbor of next node
        }
    }
    destroyDList(resultSet->dlist);
    free(resultSet);
    return 0;
}
