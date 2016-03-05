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
    p[index].property = malloc(strlen(property)+1);
    strcpy(p[index].property,(char*)property);
}
/**
 * Sets an integer property "property" in position "index"
 * property: the value of the property
 * index: the position of the property
 * p: the properties object
 */
void setDoubleProperty(double property, int index, Properties* p) {
    double *temp;
    temp = malloc(sizeof(double));
    *temp = property;
    p[index].property =(double*)temp;
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
        printf("Error1:not available memory\n");
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
        printf("Error2:not available memory\n");
        exit(1);
    }
    graph->pointer = 0;
    graph->HT_Size = graph->Init_HT_Size = graph->NextSplitPointer =  m;
    graph->round = 0;
    graph->HashTable = malloc(m*sizeof(Bucket*));

    if(graph->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    graph->InitBucketSize = c;
    for(i=0;i<m;i++)
        createBucket(graph,i,c);
    graph->statistics = malloc(sizeof(Statistics));
    graph->statistics->distanceNum = -1;
    graph->statistics->distanceSum = 0;
    graph->statistics->edges = 0;
    graph->statistics->vertices = 0;
    graph->statistics->diameter = -1;
    graph->statistics->CCNum = 0;
    graph->statistics->maxCCvertNum = -1;

    graph->queries = malloc(sizeof(Queries));
    graph->queries->flagQ1 = graph->queries->flagQ2 = graph->queries->flagForum = graph->queries->flagInterest = 0;
    return graph; //return empty graph
}

void destroyTestGraph(Graph* graph,int flag){
    int i,j,hash_size;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    if(graph == NULL ){
        printf("Error4:Graph already destroyed/empty\n");
        return; //return fail
    }
    for(i=0;i<graph->HT_Size;i++){
        for(j=0;j<graph->HashTable[i]->records;j++){
            destroyList(graph->HashTable[i]->BucketTable[j]->neighbors,flag); //destroy neighbor list
            free(graph->HashTable[i]->BucketTable[j]);
        }
        free(graph->HashTable[i]->BucketTable);
        free(graph->HashTable[i]);
    }
    free(graph->HashTable);
    free(graph->statistics);
    free(graph->queries);
    free(graph);
    return;
}

HashStruct* createHashStruct(int m,int c){
    int i;
    HashStruct* hashStruct= (HashStruct*)malloc(sizeof(HashStruct));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucket*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucket(hashStruct,i,c);
    return hashStruct;
}

HashStructD* createHashStructD(int m,int c){
    int i;
    HashStructD* hashStruct= (HashStructD*)malloc(sizeof(HashStructD));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketD*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketD(hashStruct,i,c);
    return hashStruct;
}

HashStructComment* createHashStructComment(int m,int c){
    int i;
    HashStructComment* hashStruct= (HashStructComment*)malloc(sizeof(HashStructComment));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketComment*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketComment(hashStruct,i,c);
    return hashStruct;
}

HashStructInterest* createHashStructInterest(int m , int c){
    int i;
    HashStructInterest* hashStruct= (HashStructInterest*)malloc(sizeof(HashStructInterest));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketInterest*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketInterest(hashStruct,i,c);
    return hashStruct;


}
HashStructPost* createHashStructPost(int m,int c){
    int i;
    HashStructPost* hashStruct= (HashStructPost*)malloc(sizeof(HashStructPost));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketPost*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketPost(hashStruct,i,c);
    return hashStruct;
}

void createHashBucketInterest(HashStructInterest * hashStruct,int position,int size){
    hashStruct->HashTable[position]= malloc(sizeof(HashBucketInterest));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(NameInterestNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

void createHashBucketComment(HashStructComment* hashStruct,int position,int size){//creates a new bucket

    hashStruct->HashTable[position]= malloc(sizeof(HashBucketComment));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(CommentNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}


void createHashBucket(HashStruct* hashStruct,int position,int size){//creates a new bucket

    hashStruct->HashTable[position]= malloc(sizeof(HashBucket));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(CNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

void createHashBucketD(HashStructD* hashStruct,int position,int size){//creates a new bucket

    hashStruct->HashTable[position]= malloc(sizeof(HashBucketD));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(DNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

void createHashBucketPost(HashStructPost* hashStruct,int position,int size){//creates a new bucket

    hashStruct->HashTable[position]= malloc(sizeof(HashBucketPost));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(PostInfoNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

HashStructForum* createHashStructForum(int m,int c){
    int i;
    HashStructForum* hashStruct= (HashStructForum*)malloc(sizeof(HashStructForum));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketForum*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketForum(hashStruct,i,c);
    return hashStruct;
}

HashStructTrust* createHashStructTrust(int m,int c){
    int i;

    HashStructTrust* hashStruct= (HashStructTrust*)malloc(sizeof(HashStructTrust));
    if(hashStruct == NULL ){
        printf("Error2:not available memory\n");
        exit(1);
    }
    hashStruct->pointer = 0;
    hashStruct->HT_Size = hashStruct->Init_HT_Size = hashStruct->NextSplitPointer =  m;
    hashStruct->round = 0;
    hashStruct->HashTable = malloc(m*sizeof(HashBucketTrust*));

    if(hashStruct->HashTable == NULL ){
        printf("Error3:not available memory\n");
        exit(1);
    }
    hashStruct->InitBucketSize = c;
    for(i=0;i<m;i++)
        createHashBucketTrust(hashStruct,i,c);
    return hashStruct;
}

void createHashBucketTrust(HashStructTrust* hashStruct,int position,int size){//creates a new bucket

    hashStruct->HashTable[position]= malloc(sizeof(HashBucketTrust));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(TrustNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

void destroyHashStructTrust(HashStructTrust* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++)
            free(hashStruct->HashTable[i]->BucketTable[j]);
        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

int insertNodeHashTrust(const TrustNode* const node, HashStructTrust* hashStruct) {

    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketTrust* temp,**temp1;
    TrustNode* temp2,*temp3;

    bucket = hashFunction(node->node->id,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(TrustNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition8(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->node->id);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (TrustNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucket*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketTrust(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(TrustNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

void createHashBucketForum(HashStructForum* hashStruct,int position,int size){
    hashStruct->HashTable[position]= malloc(sizeof(HashBucketForum));
    if(hashStruct->HashTable[position] == NULL ){
        printf("Error1:not available memory\n");
        exit(1);
    }
    hashStruct->HashTable[position]->BucketTable = malloc(size*sizeof(NameForumNode*));
    hashStruct->HashTable[position]->size = size;
    hashStruct->HashTable[position]->records = 0;
}

void destroyHashStructComment(HashStructComment* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++)
            free(hashStruct->HashTable[i]->BucketTable[j]);
        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

void destroyHashStructPost(HashStructPost* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++)
            free(hashStruct->HashTable[i]->BucketTable[j]);
        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

void destroyHashStructInterest(HashStructInterest* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++){
            free(hashStruct->HashTable[i]->BucketTable[j]->name);
            free(hashStruct->HashTable[i]->BucketTable[j]);
        }
        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

void destroyHashStruct(HashStruct* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++)
            free(hashStruct->HashTable[i]->BucketTable[j]);
        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

void destroyHashStructForum(HashStructForum* hashStruct){
    int i,j;
    for(i=0;i<hashStruct->HT_Size;i++){
        for(j=0;j<hashStruct->HashTable[i]->records;j++)
            free(hashStruct->HashTable[i]->BucketTable[j]);

        free(hashStruct->HashTable[i]->BucketTable);
        free(hashStruct->HashTable[i]);
    }
    free(hashStruct->HashTable);
    free(hashStruct);
}

void destroyHashStructD(HashStructD* hashStructD){
    int i,j;
    for(i=0;i<hashStructD->HT_Size;i++){
        for(j=0;j<hashStructD->HashTable[i]->records;j++)
            free(hashStructD->HashTable[i]->BucketTable[j]);
        free(hashStructD->HashTable[i]->BucketTable);
        free(hashStructD->HashTable[i]);
    }
    free(hashStructD->HashTable);
    free(hashStructD);
}
/* Destroys a graph
 * g: the graph
 * return value: success/fail status */
int destroyGraph(Graph* graph,int flag) {
    int i,j,hash_size,k;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    if(graph == NULL ){
        printf("Error4:Graph already destroyed/empty\n");
        return 1; //return fail
    }
    for(i=0;i<graph->HT_Size;i++){
        for(j=0;j<graph->HashTable[i]->records;j++){
            destroyList(graph->HashTable[i]->BucketTable[j]->neighbors,flag); //destroy neighbor list
            for(k=0;k<PERSON_PROPERTIES_NUM-1;k++){
                if(graph->HashTable[i]->BucketTable[j]->properties[k].property != NULL)
                    free(graph->HashTable[i]->BucketTable[j]->properties[k].property);
            }
            destroyTagList(graph->HashTable[i]->BucketTable[j]->properties[PERSON_PROPERTIES_NUM-1].property);
            free(graph->HashTable[i]->BucketTable[j]->properties);
            free(graph->HashTable[i]->BucketTable[j]);
        }
        free(graph->HashTable[i]->BucketTable);
        free(graph->HashTable[i]);
    }
    free(graph->HashTable);
    free(graph->statistics);
    if(graph->queries->flagQ1 == 1){
        for(i=0;i<hash_size;i++)
            destroyInfoList(graph->queries->HashTable1[i]);
        free(graph->queries->HashTable1);
    }
    if(graph->queries->flagQ2 == 1){
        destroyHashStructPost(graph->queries->HashTablePost);
        for(i=0;i<hash_size;i++)
            destroyGenPostInfoList(graph->queries->HashTable2[i]);
        free(graph->queries->HashTable2);

    }
    if(graph->queries->flagInterest == 1)
        destroyHashStructInterest(graph->queries->HashTableInterest);
    if(graph->queries->flagForum == 1)
        destroyHashStructForum(graph->queries->HashStructForum);
    free(graph->queries);
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
            printf("Error5:not available memory\n");
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
    graph->statistics->vertices++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(graph->HashTable,((graph->HT_Size)+1)*sizeof(Bucket*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
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
                    printf("Error7:not available memory\n");
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

int insertHashStructComment(const CommentNode* const node, HashStructComment* hashStruct){
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketComment* temp,**temp1;
    CommentNode* temp2,*temp3;

    bucket = hashFunction(node->commentId,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->commentId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(CommentNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition7(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->commentId);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (CommentNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(CommentNode*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketComment(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->commentId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(CommentNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

int insertNodeHashForum(const NameForumNode* const node, HashStructForum* hashStruct) {
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketForum* temp,**temp1;
    NameForumNode* temp2,*temp3;

    bucket = hashFunction(node->forumId,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->forumId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(NameForumNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition6(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->forumId);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (NameForumNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucketD*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketForum(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->forumId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(NameForumNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

int insertNodeHash(const CNode* const node, HashStruct* hashStruct) {
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucket* temp,**temp1;
    CNode* temp2,*temp3;

    bucket = hashFunction(node->node->id,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(CNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition2(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->node->id);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (CNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucket*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucket(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(CNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

int insertNodeHashD(const DNode* const node, HashStructD* hashStruct) {
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketD* temp,**temp1;
    DNode* temp2,*temp3;

    bucket = hashFunction(node->node->id,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(DNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition3(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->node->id);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (DNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucketD*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketD(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->node->id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(DNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

int insertNodeHashPost(const PostInfoNode* const node, HashStructPost* hashStruct) {
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketPost* temp,**temp1;
    PostInfoNode* temp2,*temp3;

    bucket = hashFunction(node->post,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->post,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(PostInfoNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition4(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->post);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (PostInfoNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucketPost*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketPost(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->post,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(PostInfoNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
    }
    return 0;
}

int insertNodeHashInterest(const NameInterestNode* const node, HashStructInterest* hashStruct){
    int bucket,tempNum,records,i,position,bucketSplit,splitCheck = 0;
    HashBucketInterest* temp,**temp1;
    NameInterestNode* temp2,*temp3;

    bucket = hashFunction(node->InterestId,hashStruct->round,hashStruct->Init_HT_Size);//find bucket that node should be placed
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(node->InterestId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    if(hashStruct->HashTable[bucket]->size == hashStruct->HashTable[bucket]->records){ //if bucketTable is full
        splitCheck = 1; //a split should be made
        tempNum = ((hashStruct->HashTable[bucket]->records)/(hashStruct->InitBucketSize));
        temp = hashStruct->HashTable[bucket];
        temp->BucketTable = realloc(hashStruct->HashTable[bucket]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(NameInterestNode*));//realloc bucketTable
        if(temp->BucketTable == NULL ){
            printf("Error5:not available memory\n");
            return 1;
        }
        hashStruct->HashTable[bucket]->BucketTable = temp->BucketTable;
        hashStruct->HashTable[bucket]->size += hashStruct->InitBucketSize;
    }
    records = hashStruct->HashTable[bucket]->records;
    position = findPosition5(hashStruct->HashTable[bucket]->BucketTable,0,records-1,node->InterestId);//find position that node with given id should be placed
    temp2 = hashStruct->HashTable[bucket]->BucketTable[position];
    for(i = position;i<records;i++){
        temp3 = hashStruct->HashTable[bucket]->BucketTable[i+1];
        hashStruct->HashTable[bucket]->BucketTable[i+1] = temp2;
        temp2 = temp3;
    }
    hashStruct->HashTable[bucket]->BucketTable[position]= (NameInterestNode*)node;
    hashStruct->HashTable[bucket]->records++;

    if (splitCheck == 1){ //if a split should be made
        //realloc HashTable
        temp1 = realloc(hashStruct->HashTable,((hashStruct->HT_Size)+1)*sizeof(HashBucketInterest*));
        if(temp1 == NULL){
            printf("Error6:not available memory\n");
            return 1;
        }
        hashStruct->HashTable = temp1;
        hashStruct->HT_Size++;
        createHashBucketInterest(hashStruct,(hashStruct->HT_Size)-1,hashStruct->InitBucketSize);
        records = hashStruct->HashTable[hashStruct->pointer]->records;
        hashStruct->HashTable[hashStruct->pointer]->records = 0;
        //and replace the records
        for(i=0;i<records;i++){
            bucketSplit = hashFunction(hashStruct->HashTable[hashStruct->pointer]->BucketTable[i]->InterestId,(hashStruct->round)+1,hashStruct->Init_HT_Size);
            if(hashStruct->HashTable[bucketSplit]->records == hashStruct->HashTable[bucketSplit]->size){//if an overflow occurs in the new-created bucketTable
                //realloc BucketTable
                tempNum = ((hashStruct->HashTable[bucketSplit]->records)/(hashStruct->InitBucketSize));
                temp = hashStruct->HashTable[bucketSplit];
                temp->BucketTable = realloc(hashStruct->HashTable[bucketSplit]->BucketTable,(tempNum+1)*hashStruct->InitBucketSize*sizeof(NameInterestNode*));
                if(temp->BucketTable == NULL ){
                    printf("Error7:not available memory\n");
                    return 1;
                }
                hashStruct->HashTable[bucketSplit]->BucketTable = temp->BucketTable;
                hashStruct->HashTable[bucketSplit]->size += hashStruct->InitBucketSize;
            }
            //place the record
            hashStruct->HashTable[bucketSplit]->BucketTable[hashStruct->HashTable[bucketSplit]->records++] = hashStruct->HashTable[hashStruct->pointer]->BucketTable[i];
        }
        hashStruct->pointer++;
    }
    if (hashStruct->pointer == hashStruct->NextSplitPointer){ //if HashTable is duplicated
        hashStruct->pointer = 0; //pointer points buck at the beginning
        hashStruct->round++; //a new round starts
        hashStruct->NextSplitPointer*=2;
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
    if (node == NULL)
        return 1;
    lnode = createLNode(edge->endNodeID,edge);//create node
    if (lnode == NULL)
        return 1;
    addNewLNode(node->neighbors,lnode);//and enter that node to list
    graph->statistics->edges++;
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

CNode* lookupNode2(int id, HashStruct* hashStruct) {
    int bucket;
    CNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition2(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
    return node;
}

DNode* lookupNode3(int id, HashStructD* hashStruct) {
    int bucket;
    DNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition3(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
    return node;
}


PostInfoNode* lookupNode4(int id,HashStructPost* hashStruct){
    int bucket;
    PostInfoNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition4(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
    return node;
}
NameInterestNode* lookupNode5(int id,HashStructInterest* hashStruct){
    int bucket;
    NameInterestNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition5(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
    return node;
}

CommentNode* lookupNode6(int id,HashStructComment* hashStruct){
    int bucket;
    CommentNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition6(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
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
    node = lookupNode(startID,g);
    dnode = createDNode(node,0);
    addNewDNode(dlist,dnode);
    tempL = dlist->head;

    while(tempL!=NULL){//while DList is not empty
        temp = tempL->node->neighbors->head;
        while(temp !=NULL){ //for every neighbor of node
            if(temp->edge->endNodeID == endID){ //if targetID has been found
                distance = tempL->dist+1; //calculate shortest path
                destroyDList(dlist);
                return distance;//and return distance of shortest path
            }
            dnode = check(dlist,temp->edge->endNodeID);//else,check if neighbor is already in the list
            if(dnode == NULL){//if neighbor is not in the list
                dist = tempL->dist + 1;//calculate shortest path
                node = lookupNode(temp->edge->endNodeID,g);
                dnode =  createDNode(node,dist);//create node
                addNewDNode(dlist,dnode);//and add it to list
            }
            temp = temp->next;//if neighbor is already in the list, jump to the next neighbor
        }
        tempL = tempL->next;//when all neighbors are checked,go to the next node of Dlist
    }
    destroyDList(dlist);
    return -1;
}
/* Finds shortest path distance between all reachable nodes from a given node
 * in an undirected graph with no edge weights
 * startID: the id of the start node
 * endID: the id of the end node
 * g: the graph
 * return value: a resultSet
 * resultSet is a struct that holds info required for gradual(one step at a time)bfs */
ResultSet* reachNodeN(int startID, const Graph* const g) {
    ResultSet* set;
    DList* list;
    DNode* tempL;
    LNode* neighbor;
    Node* node;
    HashStructD* hashStruct;

    hashStruct = createHashStructD(M,C);
    set = (ResultSet*)malloc(sizeof(ResultSet));//create a ResultSet
    list = createDList();
    node = lookupNode(startID,g);//lookup startNode
    tempL = createDNode(node,0);
    addNewDNode(list,tempL);//and add startNode to List
    insertNodeHashD(tempL,hashStruct);

    neighbor = node->neighbors->head;//get 1st neighbor of person with startID
    tempL = list->head;

    set->list = list;
    set->tempL = tempL;
    set->graph = g;
    set->neighbor = neighbor;
    set->hashStruct = hashStruct;
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
    Node* node;
    int dist;

    while(resultSet->tempL!=NULL){//while DList is not empty
        while(resultSet->neighbor!=NULL){//for every neighbor of node
            dnode = lookupNode3(resultSet->neighbor->edge->endNodeID,resultSet->hashStruct);
            if(dnode == NULL){//if neighbor is not in the list
                dist = resultSet->tempL->dist + 1;//calculate shortest path
                node = lookupNode(resultSet->neighbor->edge->endNodeID,resultSet->graph);//lookup neighborNode
                dnode =  createDNode(node,dist);//create Dnode
                addNewDNode(resultSet->list,dnode);//and add it to list
                insertNodeHashD(dnode,resultSet->hashStruct);
                //create next pair and return
                pair->distance = dist;
                pair->ID = resultSet->neighbor->edge->endNodeID;

                resultSet->hold = resultSet->neighbor;
                resultSet->neighbor = resultSet->neighbor->next;//go to next neighbor
                return 1;
            }
            resultSet->neighbor = resultSet->neighbor->next;//go to next neighbor
        }
        resultSet->tempL = resultSet->tempL->next;//when all neighbors are checked,go to the next node of Dlist
        if(resultSet->tempL!=NULL)//if DList is not empty
           resultSet->neighbor = resultSet->tempL->node->neighbors->head;//get first neighbor of node
    }
    destroyHashStructD(resultSet->hashStruct);
    free(resultSet->list);
    //destroyDList(resultSet->list);
    return 0;
}

double bfs(Node* startNode,Node* bridge,Graph* graph) {
    CList *list;
    CNode *tempL,*cnode,*ctemp;
    LNode *neighbor;
    Node* node;
    HashStruct* hashStruct;
    int dist;
    double sum = 0.0;

    hashStruct = createHashStruct(M,C);
    list = createCList();
    node = lookupNode(startNode->id,graph);
    tempL = createCNode(node,0);
    addNewCNode(list,tempL);
    insertNodeHash(tempL,hashStruct);

    neighbor = node->neighbors->head;
    tempL = list->head;
    tempL->paths = 1;

    while(tempL!=NULL){//while CList is not empty
        while(neighbor!=NULL){//for every neighbor of node
            cnode = lookupNode2(neighbor->edge->endNodeID,hashStruct);
            if(cnode == NULL){//if neighbor is not in hashStruct
                dist = tempL->dist + 1;//calculate shortest path
                node = lookupNode(neighbor->edge->endNodeID,graph);//lookup neighborNode
                cnode = createCNode(node,dist);//calculate node
                addNewCNode(list,cnode);//and add it to list
                insertNodeHash(cnode,hashStruct);
                //the number of paths to the new node are inherited from tempL
                cnode->paths = tempL->paths;
                //if new node is a bridge then bridge variable is increased
                if(cnode->node->id == bridge->id)
                    cnode->bridges = tempL->paths;
                else
                    //the number of bridges to the new node are inherited from tempL
                    cnode->bridges = tempL->bridges;
            }
            else{//if neighbor is in the list
                if((tempL->dist+1) == cnode->dist ){//if a new path of the same distance is found
                    cnode->paths+=tempL->paths;//increase number of paths of node
                    //if new node is a bridge then bridge variable is increased
                    if(cnode->node->id == bridge->id)
                        cnode->bridges+=tempL->paths;
                    else
                        //the number of bridges to the new node are inherited from tempL
                        cnode->bridges+= tempL->bridges;
                }
            }
            neighbor = neighbor->next;//go to next neighbor
        }
        tempL = tempL->next;//when all neighbors are checked,go to the next node of Dlist
        if(tempL!=NULL)
            neighbor = tempL->node->neighbors->head;//get first neighbor of next node
    }
    ctemp = list->head;
    while(ctemp != NULL) {
       // printf("%d %d %d\n",ctemp->id,ctemp->bridges,ctemp->paths);
        if(ctemp->node->id != bridge->id && ctemp->node->id != startNode->id && startNode->id < ctemp->node->id){
            sum += (double)ctemp->bridges / (double)ctemp->paths;
        }
        ctemp = ctemp->next;
    }
    destroyHashStruct(hashStruct);
    free(list);
    return sum;
}

int hash_function(int id,int hash_size){
    return (id%hash_size);
}

HList** createHashTable(int hash_size){
    HList** hashtable;
    int i;

    hashtable = malloc(hash_size*sizeof(HList*));
    if(hashtable == NULL){
        printf("Error8:not available memory\n");
        exit(1);
    }
    for(i=0;i<hash_size;i++){
        hashtable[i] =  createHList();
        if(hashtable[i] == NULL){
            printf("Error9:not available memory\n");
            exit(1);
        }
    }
    return hashtable;
}
//-------------------------------STATISTIC FUNCTIONS-------------------------------------------------//
void degreeDistribution(Graph* graph){
    int i,j,hash_size,position,neighbors = 0;
    HList** array;
    HNode* hnode,*htemp;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    array = createHashTable(hash_size);

    for(i=0;i<graph->HT_Size;i++){
        for(j=0;j<graph->HashTable[i]->records;j++){
            neighbors =  graph->HashTable[i]->BucketTable[j]->neighbors->_size;
            //printf("kombos = %d neighbors == %d\n",graph->HashTable[i]->BucketTable[j]->id,neighbors);
            position = hash_function(neighbors,hash_size);
            hnode = checkHList(array[position],neighbors);
            if (hnode == NULL){
                hnode = createHNode(neighbors);
                addNewHNode(array[position],hnode);
            }
            else
                hnode->vertices++;
        }
    }
    for(i=0;i<hash_size;i++){
        htemp = array[i]->head;
        while(htemp!=NULL){
            //gnuplot
            htemp = htemp->next;
        }
    }
    for(i=0;i<hash_size;i++)
        destroyHList(array[i]);
    free(array);
}

void CalculateStatistics(Graph* graph){
    int i,j,maxDiameter = -1;
    int hash_size,position;
    ResultSet* set;
    Pair pair;
    HList** array;
    HNode* hnode;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    array = createHashTable(hash_size);

    graph->statistics->distanceNum = 0;

    for(i=0;i<graph->HT_Size;i++){
        for(j=0;j<graph->HashTable[i]->records;j++){
                set =  reachNodeN(graph->HashTable[i]->BucketTable[j]->id,graph);
                position = hash_function(graph->HashTable[i]->BucketTable[j]->id,hash_size);
                hnode = checkHList(array[position],graph->HashTable[i]->BucketTable[j]->id);
                if (hnode == NULL){
                    hnode = createHNode(graph->HashTable[i]->BucketTable[j]->id);
                    addNewHNode(array[position],hnode);
                    graph->statistics->CCNum++;
                }
                if(set->neighbor!=NULL){
                    position = hash_function(set->neighbor->edge->endNodeID,hash_size);
                    hnode = checkHList(array[position],set->neighbor->edge->endNodeID);
                    if (hnode == NULL){
                        hnode = createHNode(set->neighbor->edge->endNodeID);
                        addNewHNode(array[position],hnode);
                    }
                }
                else
                    if(graph->statistics->maxCCvertNum < 1)
                        graph->statistics->maxCCvertNum = 1;
                while( next(set,&pair)){
                        position = hash_function(set->hold->edge->endNodeID,hash_size);
                        hnode = checkHList(array[position],set->hold->edge->endNodeID);
                        if (hnode == NULL){
                            hnode = createHNode(set->hold->edge->endNodeID);
                            addNewHNode(array[position],hnode);
                        }
                    graph->statistics->distanceNum++;
                    graph->statistics->distanceSum += pair.distance;
                   // printf("%d\n",pair.distance);
                    if(maxDiameter < pair.distance )
                        maxDiameter = pair.distance;
                    if (set->hold->next == NULL){
                        if (set->list->_size > graph->statistics->maxCCvertNum)
                            graph->statistics->maxCCvertNum = set->list->_size;
                    }
                }
        free(set);
        }
    }
    graph->statistics->diameter = maxDiameter;
    //printf("max vertices %d\n",graph->statistics->maxCCvertNum);
    for(i=0;i<hash_size;i++)
        destroyHList(array[i]);
    free(array);
}

int diameter(Graph* graph){
    if(graph->statistics->diameter == -1)
        CalculateStatistics(graph);
    return graph->statistics->diameter;
}

double averagePathLength(Graph* graph){
    if(graph->statistics->distanceNum == -1)
        CalculateStatistics(graph);
    return (double)graph->statistics->distanceSum/(double)graph->statistics->distanceNum;
}

double density(Graph* graph){
    double Density;
    Density = (double)(2*(graph->statistics->edges))/(double)((graph->statistics->vertices)*(graph->statistics->vertices-1));
    return Density;
}

int numberOfCCs(Graph* graph){
    if(graph->statistics->CCNum == 0)
        CalculateStatistics(graph);
    return graph->statistics->CCNum;
}

int maxCC(Graph* graph){
    if(graph->statistics->maxCCvertNum == -1)
        CalculateStatistics(graph);
    return graph->statistics->maxCCvertNum;
}

double closenessCentrality(Node* node ,Graph* graph){
    ResultSet* set;
    Pair pair;
    double distanceSum = 0;
    double centrality;

    set = reachNodeN(node->id,graph);
    while(next(set,&pair)){
      //  printf("id%d distance%d\n",pair.ID,pair.distance);
        distanceSum += (1.0/(float)(pair.distance));
    }
    centrality = distanceSum/(graph->statistics->vertices - 1);
    free(set);
    return centrality;
}

double betweennessCentrality(Node* node, Graph* graph){
    int i,j;
    double sum = 0,bcTotal = 0;

    for(i=0;i<graph->HT_Size;i++){//for every node in graph except given node
            for(j=0;j<graph->HashTable[i]->records;j++){
                if(graph->HashTable[i]->BucketTable[j]->id == node->id)
                    continue;
                sum = bfs(graph->HashTable[i]->BucketTable[j],node,graph); //bfs search for each node
                bcTotal += sum;
            }
    }
    bcTotal = (double)(bcTotal) / (double)((double)((double)(graph->statistics->vertices-2)*(double)(graph->statistics->vertices-1))/2);
    return bcTotal;
}
//--------------------------------Query functions---------------------------------------------------------------
void createHashTableForum(Graph *graph){
    char temparray[30];
    char id1[10],id2[8],id3[22];
    NameForumNode* nameForumNode;
    FILE* fp1;

    graph->queries->flagForum = 1;
    graph->queries->HashStructForum = createHashStructForum(M,C);
    fp1 = fopen("forum_hasMember_person.csv","r");
    if (fp1 == NULL){
        printf("Error10,file can not be opened");
        exit(1);
    }
    fscanf(fp1,"%s\n",temparray);//fscanf first line of file fp1
    while(1){
        if(fscanf(fp1,"%[^|]|%[^|]|%[^\n]\n",id1,id2,id3) ==  EOF)
            break;
        if(atoi(id1) == 0)
            printf("%d\n",atoi(id1));
        nameForumNode = createNameForumNode(atoi(id1),atoi(id2));
        insertNodeHashForum(nameForumNode,graph->queries->HashStructForum);
    }
    fclose(fp1);
}

void createHashTableQ1(Graph *graph){
    int i,hash_size,position;
    WorkPlaceNode* workPlaceNode;
    char temparray[36];
    char id1[6],id2[6],id3[5];
    InfoNode* infoNode;
    FILE* fp1,*fp2,*fp3;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    graph->queries->flagQ1 = 1;
    graph->queries->HashTable1 = malloc(hash_size*sizeof(InfoList*));
    if(graph->queries->HashTable1== NULL){
        printf("Error8:not available memory\n");
        exit(1);
    }
    for(i=0;i<hash_size;i++){
        graph->queries->HashTable1[i]= createInfoList();
        if(graph->queries->HashTable1[i] == NULL){
            printf("Error9:not available memory\n");
            exit(1);
        }
    }
    fp1 = fopen("person_isLocatedIn_place.csv","r");
    if (fp1 == NULL){
        printf("Error,file can not be opened");
        exit(1);
    }
    fp2 = fopen("person_studyAt_organisation.csv","r");
    if (fp2 == NULL){
        printf("Error,file can not be opened");
        exit(1);
    }
    fp3 = fopen("person_workAt_organisation.csv","r");
    if (fp3 == NULL){
        printf("Error,file can not be opened");
        exit(1);
    }
    fscanf(fp1,"%s\n",temparray);//fscanf first line of file fp1
    while(1){
        if(fscanf(fp1,"%[^|]|%[^\n]\n",id1,id2) ==  EOF)
            break;
        position = hash_function(atoi(id1),hash_size);
        infoNode = createInfoNode(atoi(id1),atoi(id2));//we assume that a person has only one home
        addNewInfoNode(graph->queries->HashTable1[position],infoNode);
    }
    fclose(fp1);

    fscanf(fp2,"%s\n",temparray);//fscanf first line of file fp2
    while(1){
        if(fscanf(fp2,"%[^|]|%[^|]|%[^\n]\n",id1,id2,id3) ==  EOF)
            break;
        position = hash_function(atoi(id1),hash_size);
        infoNode = checkInfoList(graph->queries->HashTable1[position],atoi(id1));
        infoNode->studyPlace = atoi(id2);
    }
    fclose(fp2);

    fscanf(fp3,"%s\n",temparray);//fscanf first line of file fp3
    while(1){
        if(fscanf(fp3,"%[^|]|%[^|]|%[^\n]\n",id1,id2,id3) ==  EOF)
            break;
        position = hash_function(atoi(id1),hash_size);
        infoNode = checkInfoList(graph->queries->HashTable1[position],atoi(id1));
        workPlaceNode = createWorkPlaceNode(atoi(id2));
        addNewWorkPlaceNode(infoNode->workPlace,workPlaceNode);
    }
    fclose(fp3);
    return;
}

void createHashTableInterest(Graph* graph){
    char temparray[10];
    char id1[6],id2[62],id3[90];
    NameInterestNode* nameInterestNode;
    FILE* fp1;

    graph->queries->flagInterest = 1;
    graph->queries->HashTableInterest = createHashStructInterest(M,C);
    fp1 = fopen("tag.csv","r");
    if (fp1 == NULL){
        printf("Error10,file can not be opened");
        exit(1);
    }
    fscanf(fp1,"%s\n",temparray);//fscanf first line of file fp1
    while(1){
        if(fscanf(fp1,"%[^|]|%[^|]|%[^\n]\n",id1,id2,id3) ==  EOF)
            break;
        nameInterestNode = createNameInterestNode(atoi(id1),id2);
        insertNodeHashInterest(nameInterestNode,graph->queries->HashTableInterest);
    }
    fclose(fp1);
}

void createReplyList(Graph* graph){
    char temparray[36];
    char id1[15],id2[15];
    GenPostInfoNode* genPostInfoNode;
    PointerPostInfoNode *pointerPostInfoNode;
    int position,hash_size;
    FILE* fp1,*fp2;
    HashStructComment* hashStructComment;
    CommentNode* commentNode;
    PostInfoNode*  postInfoNode;

    hashStructComment = createHashStructComment(M,C);
    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    fp1 = fopen("comment_hasCreator_person.csv","r");
    if (fp1 == NULL){
        printf("Error10,file can not be opened");
        exit(1);
    }
    fp2 = fopen("comment_replyOf_post.csv","r");
    if (fp2 == NULL){
        printf("Error10,file can not be opened");
        exit(1);
    }

    fscanf(fp1,"%s\n",temparray);//fscanf first line of file "comment_hasCreator_person.csv"
    while(1){
        if(fscanf(fp1,"%[^|]|%[^\n]\n",id1,id2) ==  EOF)
            break;
        position = hash_function(atoi(id2),hash_size);
        genPostInfoNode = checkGenPostInfoNode(graph->queries->HashTable2[position],atoi(id2));
        if(genPostInfoNode==NULL){
            genPostInfoNode = createGenPostInfoNode(atoi(id2));
            addNewGenPostInfoNode(graph->queries->HashTable2[position],genPostInfoNode);
        }
        pointerPostInfoNode = createPointerPostInfoNode(NULL);
        pointerPostInfoNode->data = atoi(id1);
        addNewPointerPostInfoNode(genPostInfoNode->replyPostList,pointerPostInfoNode);
        commentNode = createCommentNode(atoi(id1),pointerPostInfoNode);
        insertHashStructComment(commentNode,hashStructComment);
    }
    fclose(fp1);
    fscanf(fp2,"%s\n",temparray);//fscanf first line of file "comment_replyOf_post.csv"
    while(1){
        if(fscanf(fp2,"%[^|]|%[^\n]\n",id1,id2) ==  EOF)
            break;
        commentNode = lookupNode6(atoi(id1),hashStructComment);
        if(commentNode == NULL)//if comment does not exist
            continue;
        postInfoNode = lookupNode4(atoi(id2),graph->queries->HashTablePost);
        commentNode->pointerPostInfoNode->postInfoNode = postInfoNode;
    }
    fclose(fp2);
    destroyHashStructComment(hashStructComment);
}

void createHashTables(Graph *graph){
    int i,hash_size,position1;
    char temparray[36];
    char id1[10],id2[10],id3[22];
    GenPostInfoNode* genPostInfoNode;
    PostInfoNode* postInfoNode;
    FILE* fp1,*fp2,*fp3;
    PointerPostInfoNode *pointerPostInfoNode;
    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);
    graph->queries->flagQ2 = 1;

    graph->queries->HashTable2 = malloc(hash_size*sizeof(GenPostInfoList*));
    if(graph->queries->HashTable2 == NULL){
        printf("Error8:not available memory\n");
        exit(1);
    }
    for(i=0;i<hash_size;i++){
        graph->queries->HashTable2[i]= createGenPostInfoList();
        if(graph->queries->HashTable2[i] == NULL){
            printf("Error9:not available memory\n");
            exit(1);
        }
    }
    graph->queries->HashTablePost = createHashStructPost(M,C);

    fp1 = fopen("person_likes_post.csv","r");
    if (fp1 == NULL){
        printf("Error10,file can not be opened");
        exit(1);
    }
    fp2 = fopen("post_hasCreator_person.csv","r");
    if (fp2 == NULL){
        printf("Error11,file can not be opened");
        exit(1);
    }
    fp3 = fopen("forum_containerOf_post.csv","r");
    if (fp3 == NULL){
        printf("Error12,file can not be opened");
        exit(1);
    }

    fscanf(fp2,"%s\n",temparray);//fscanf first line of file "post_HasCreator_person"
    while(1){
        if(fscanf(fp2,"%[^|]|%[^\n]\n",id1,id2) ==  EOF)
            break;
        postInfoNode = createPostInfoNode(atoi(id1),atoi(id2));
        insertNodeHashPost(postInfoNode,graph->queries->HashTablePost);
    }
    fclose(fp2);

    fscanf(fp3,"%s\n",temparray);//fscanf first line of file forum_containerOf_post
    while(1){
        if(fscanf(fp3,"%[^|]|%[^\n]\n",id1,id2) ==  EOF)
            break;
        postInfoNode = lookupNode4(atoi(id2),graph->queries->HashTablePost);
        if(postInfoNode == NULL)
            continue;
        postInfoNode->forum = atoi(id1);
    }
    fclose(fp3);

    fscanf(fp1,"%s\n",temparray);//fscanf first line of file fp1
    while(1){
        if(fscanf(fp1,"%[^|]|%[^|]|%[^\n]\n",id1,id2,id3) ==  EOF)
            break;
        position1 = hash_function(atoi(id1),hash_size);
        genPostInfoNode = checkGenPostInfoNode(graph->queries->HashTable2[position1],atoi(id1));
        if(genPostInfoNode==NULL){
            genPostInfoNode = createGenPostInfoNode(atoi(id1));
            addNewGenPostInfoNode(graph->queries->HashTable2[position1],genPostInfoNode);
        }
        postInfoNode = lookupNode4(atoi(id2),graph->queries->HashTablePost);
        if(postInfoNode == NULL)
            continue;
        pointerPostInfoNode = createPointerPostInfoNode(postInfoNode);
        addNewPointerPostInfoNode(genPostInfoNode->likePostList,pointerPostInfoNode);
    }
    fclose(fp1);
    return;
}

TagInfo* IsPossibleMatch(Node* startNode,Node* possibleMatch,int x,int k,Graph* graph){
    char yearStartNode[5],yearPossibleMatch[5];
    int position,hash_size,temp1,temp2,check,sameInterests = 0;
    InfoNode* infoNode1,*infoNode2;
    TagNode* tagNode;
    TagInfo* tagInfo;
    TagList* taglist,*taglistp;

    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);

    if(strcmp(startNode->properties[2].property,possibleMatch->properties[2].property) == 0)//check if people have different genders
        return NULL;
    strncpy(yearStartNode,startNode->properties[3].property,4);
    strncpy(yearPossibleMatch,possibleMatch->properties[3].property,4);
    yearStartNode[4] = '\0';
    yearPossibleMatch[4] = '\0';
    if (abs(atoi(yearStartNode) - atoi(yearPossibleMatch)) > x)//check if people have age difference less than x years
        return NULL;
    position = hash_function(startNode->id,hash_size);
    infoNode1 = checkInfoList(graph->queries->HashTable1[position],startNode->id);
    position = hash_function(possibleMatch->id,hash_size);
    infoNode2 = checkInfoList(graph->queries->HashTable1[position],possibleMatch->id);
     if (infoNode1->livePlace != infoNode2->livePlace){ //check if people live or study/work at the same place
        if(infoNode1->studyPlace==-1 || infoNode2->studyPlace==-1 || (infoNode1->studyPlace != infoNode2->studyPlace)){
            temp1 = checkWorkPlaceList(infoNode1,infoNode2->workPlace);
            temp2 = checkWorkPlaceList(infoNode2,infoNode1->workPlace);
            if(temp1==-1 || temp2==-1 || (temp1 != temp2))
                return NULL;
        }
    }
    taglistp = possibleMatch->properties[7].property;
    taglist = startNode->properties[7].property;
    tagNode = taglist->head;
    while(tagNode!=NULL){
        check = checkTagList((TagList*)possibleMatch->properties[7].property,tagNode->tag);
        if(check)
            sameInterests++;
        tagNode = tagNode->next;
    }
    if(sameInterests<k)
        return NULL;
    else{
        tagInfo = malloc(sizeof(TagInfo));
        tagInfo->Interests = (taglist->_size) + (taglistp->_size) - sameInterests;
        tagInfo->sameInterests = sameInterests;
        return tagInfo;
    }
}

Matches* matchSuggestion(Node* startNode,int k,int h,int x,int limit,Graph *graph){
    DNode *tempL,*dnode;
    LNode* lnode;
    DList* list;
    Node* node;
    Matches* matches;
    MatchNode* matchNode;
    TagInfo* tagInfo;
    int dist;
    double similarityScore;

    matches = createMatches();//create List Matches

    if(graph->queries->flagQ1 == 0)
        createHashTableQ1(graph);

    list = createDList();
    node = lookupNode(startNode->id,graph);
    dnode = createDNode(node,0);
    addNewDNode(list,dnode);

    lnode = node->neighbors->head;
    while(lnode != NULL){
        node = lookupNode(lnode->edge->endNodeID,graph);
        dnode = createDNode(node,1);
        addNewDNode(list,dnode);
        lnode = lnode->next;
    }
    tempL = list->head->next; //tempL points at first neighbor of startNode
    if (tempL != NULL) //if node exists
        lnode = tempL->node->neighbors->head; //and point at it's first neighbor
    while(tempL != NULL){ //while DList is not empty
        while(lnode != NULL){ //for every neighbor of tempL
            dnode = check(list,lnode->edge->endNodeID);//check if neighbor is already in the list
            if(dnode == NULL){//if neighbor is not in the list
                dist = tempL->dist + 1;//calculate shortest path
                if (dist > h){ //if node is more than h steps far
                    destroyDList(list);
                    return matches;
                }
                node = lookupNode(lnode->edge->endNodeID,graph);
                dnode = createDNode(node,dist);//calculate node
                addNewDNode(list,dnode);//and add it to list
                tagInfo = IsPossibleMatch(startNode,dnode->node,x,k,graph);
                if (tagInfo!=NULL){
                    similarityScore = (double)tagInfo->sameInterests/(double)tagInfo->Interests;
                    matchNode = createMatchNode(dnode->node->id,similarityScore);
                    InsertToMatches(matches,matchNode,limit);
                    free(tagInfo);
                }
            }
            lnode = lnode->next;//go to next neighbor
        }
        tempL = tempL->next;//when all neighbors are checked,go to the next node of Dlist
        if(tempL != NULL){//if DList is not empty
            lnode = tempL->node->neighbors->head;//get first neighbor of node
        }
    }
    destroyDList(list);
    return matches;
}

Graph* getTopStalkers(int k,int x,int centralityMode,Graph* graph,StalkerList** stalkerList){
    int i,hash_size,isNeighbor,maxLikes;
    float centralityScore;
    GenPostInfoNode* genPostInfoNode;
    PostInfoNode* postInfoNode;
    PointerPostInfoNode* tempLikePostNode;
    LikeList* likeList;
    LikeNode* likeNode;
    Node* node,*node1;
    Edge* edge;
    StalkerNode* stalkerNode,*neighborStalkerNode;
    ForumNode* forumNode;
    LNode* neighborNode;
    CreatorNode* creatorNode;
    CreatorList* creatorList;

    *stalkerList = createStalkerList();
    Graph* stalkerGraph = createGraph(M,C);
    hash_size = sqrt(graph->statistics->vertices);
    hash_size = round(hash_size);

    if(graph->queries->flagQ2 == 0)
        createHashTables(graph);

    for(i=0;i<hash_size;i++){
        genPostInfoNode = graph->queries->HashTable2[i]->head;
        while(genPostInfoNode!=NULL){//for every possible stalker
            node = lookupNode(genPostInfoNode->id,graph);//get possible stalker node
            likeList = createLikeList();//create list that holds creator-ids and likes
            //inform likeList
            tempLikePostNode = genPostInfoNode->likePostList->head;
            while(tempLikePostNode!=NULL){
                postInfoNode = tempLikePostNode->postInfoNode;//points at first post person likes
                if(postInfoNode->creator == node->id){//if person has liked himself/herself
                    tempLikePostNode = tempLikePostNode->next;
                    continue;
                }
                likeNode = checkLikeList(likeList,postInfoNode->creator);
                if(likeNode == NULL){
                    likeNode = createLikeNode(postInfoNode->creator);//create a likeNode-initial value of likeNode->likes = 0
                    addNewLikeNode(likeList,likeNode);
                }
                likeNode->likes++;
                tempLikePostNode = tempLikePostNode->next;
            }
            //calculate max number of likes to another person that is not possibleStalker's neighbor
            creatorList = createCreatorList();
            likeNode = likeList->head;
            maxLikes = 0;
            while(likeNode!=NULL){
                isNeighbor = checkList(node->neighbors,likeNode->creator);//check if creator is stalker's neighbor
                if( (likeNode->likes > x) && (isNeighbor == 0)){//if person stalks a stranger
                    creatorNode = createCreatorNode(likeNode->creator);
                    addNewCreatorNode(creatorList,creatorNode);
                    if(likeNode->likes > maxLikes)
                        maxLikes = likeNode->likes;
                }
                likeNode = likeNode->next;
            }
            if(maxLikes > x){//if likes at someone's posts are more than x,we've got a stalker!
                if(centralityMode == 1)//calculate centralityScore
                    centralityScore = closenessCentrality(node,graph);
                else
                    centralityScore = betweennessCentrality(node,graph);
                stalkerNode = createStalkerNode(node,centralityScore,centralityScore);
                addNewStalkerNode(*stalkerList,stalkerNode,k);//and add stalker to StalkerList

                creatorNode = creatorList->head;
                //printf("%d\n",creatorNode->creator);
                while(creatorNode!=NULL){
                    tempLikePostNode = genPostInfoNode->likePostList->head;
                    while(tempLikePostNode!=NULL){
                        postInfoNode = tempLikePostNode->postInfoNode;//find forums in which stalkings are found
                        if(postInfoNode->creator == creatorNode->creator){
                            forumNode = checkForumList(stalkerNode->forumList,postInfoNode->forum);
                            if(forumNode==NULL){
                                forumNode = createForumNode(postInfoNode->forum);
                                addNewForumNode(stalkerNode->forumList,forumNode);
                            }
                        }
                        tempLikePostNode = tempLikePostNode->next;
                    }
                    creatorNode = creatorNode->next;
                }
            }
            destroyCreatorList(creatorList);
            destroyLikeList(likeList);
            genPostInfoNode = genPostInfoNode->next;//go to next possible stalker
        }
    }
    EditStalkersList(*stalkerList,k);
    //inform StalkerGraph
    stalkerNode = (*stalkerList)->head;
    while(stalkerNode!=NULL){
        node1 = setPersonProperties(stalkerNode->node->id,stalkerNode->node->properties[0].property,stalkerNode->node->properties[1].property,stalkerNode->node->properties[2].property,stalkerNode->node->properties[3].property,stalkerNode->node->properties[4].property,stalkerNode->node->properties[5].property,stalkerNode->node->properties[6].property);
        insertNode(node1,stalkerGraph);//insert Node to StalkerGraph
        neighborNode = stalkerNode->node->neighbors->head;
        while(neighborNode!=NULL){
            neighborStalkerNode = checkStalkerList(*stalkerList,neighborNode->edge->endNodeID);
            if(neighborStalkerNode!=NULL){
                edge = setEdgeProperties(stalkerNode->node->id,neighborNode->edge->endNodeID,"knows",0);
                insertEdge(stalkerNode->node->id,edge,stalkerGraph);
            }
            neighborNode = neighborNode->next;
        }
        stalkerNode = stalkerNode->next;
    }
    return stalkerGraph;
}

TrendsNum* findTrends(int k,Graph* graph,char*** womenTrends,char*** menTrends){
    int i,j;
    Graph* GraphWomen,*GraphMen;
    InterestList* womenInterestList,*menInterestList;
    InterestNode* interestNode;
    TagNode* tempTagNode;
    TagList* tagList;
    TempList* tempList;
    TempNode* tempNode;
    NameInterestNode* nameInterestNode;
    TrendsNum* trendsNum = malloc(sizeof(TrendsNum));

    if(graph->queries->flagInterest == 0)
        createHashTableInterest(graph);

    *womenTrends = malloc(k*sizeof(char*));
    *menTrends = malloc(k*sizeof(char*));
    if (*womenTrends == NULL || *menTrends == NULL)
        exit(1);

    womenInterestList = createInterestList();
    menInterestList = createInterestList();
    //create Graph for men and women
    GraphWomen = createGraph(10,5);
    GraphMen = createGraph(10,5);

    for(i=0;i<graph->HT_Size;i++){//for every entry in original Graph
        for(j=0;j<graph->HashTable[i]->records;j++){//inform the Graphs GraphWomen and GraphMen
            if(graph->HashTable[i]->BucketTable[j]->properties[2].property == NULL)//if person has no characteristics and no tags
                continue;
            if(strcmp(graph->HashTable[i]->BucketTable[j]->properties[2].property,"female") == 0)
                GraphEntry(graph->HashTable[i]->BucketTable[j],GraphWomen,graph,"female");
            else
                GraphEntry(graph->HashTable[i]->BucketTable[j],GraphMen,graph,"male");
        }
    }
    for(i=0;i<GraphWomen->HT_Size;i++){//for all the women in GraphWomen
        for(j=0;j<GraphWomen->HashTable[i]->records;j++){
            tagList = GraphWomen->HashTable[i]->BucketTable[j]->properties[7].property;
            tempTagNode = tagList->head;
            while(tempTagNode!=NULL){
                interestNode = checkInterestList(womenInterestList,tempTagNode->tag);
                if(interestNode == NULL){
                    interestNode = createInterestNode(tempTagNode->tag);
                    addNewInterestNode(womenInterestList,interestNode);
                }
                InterestEntry(GraphWomen->HashTable[i]->BucketTable[j],GraphWomen,interestNode);
                tempTagNode = tempTagNode->next;
            }
        }
    }
    for(i=0;i<GraphMen->HT_Size;i++){//for all the men in GraphWomen
        for(j=0;j<GraphMen->HashTable[i]->records;j++){
            tagList = GraphMen->HashTable[i]->BucketTable[j]->properties[7].property;
            tempTagNode = tagList->head;
            while(tempTagNode!=NULL){
                interestNode = checkInterestList(menInterestList,tempTagNode->tag);
                if(interestNode == NULL){
                    interestNode = createInterestNode(tempTagNode->tag);
                    addNewInterestNode(menInterestList,interestNode);
                }
                InterestEntry(GraphMen->HashTable[i]->BucketTable[j],GraphMen,interestNode);
                tempTagNode = tempTagNode->next;
            }
        }
    }
    //create womenTrendsOrderedList with Interests
    tempList = createTempList();
    interestNode = womenInterestList->head;
    while(interestNode!=NULL){
        interestNode->interestSize = maxCC(interestNode->interestGraph);
        tempNode = createTempNode(interestNode->interest,interestNode->interestSize);
        addNewTempNode(tempList,tempNode);
        interestNode = interestNode->next;
    }
    EditInterestList(tempList,k);
    //create womenTrends array
    tempNode = tempList->head;
    for(i=0;i<tempList->_size;i++){
        nameInterestNode = lookupNode5(tempNode->interest,graph->queries->HashTableInterest);
        (*womenTrends)[i] = malloc(strlen(nameInterestNode->name)+1);
        strcpy((*womenTrends)[i],nameInterestNode->name);
        tempNode = tempNode->next;
    }
    trendsNum->womenTrendsNum = tempList->_size;
    destroyTempList(tempList);

    //create menTrendsOrderedList with Interests
    tempList = createTempList();
    interestNode = menInterestList->head;
    while(interestNode!=NULL){
        interestNode->interestSize = maxCC(interestNode->interestGraph);
        tempNode = createTempNode(interestNode->interest,interestNode->interestSize);
        addNewTempNode(tempList,tempNode);
        interestNode = interestNode->next;
    }
    EditInterestList(tempList,k);
    //create menTrends array
    tempNode = tempList->head;
    for(i=0;i<tempList->_size;i++){
        nameInterestNode = lookupNode5(tempNode->interest,graph->queries->HashTableInterest);
        (*menTrends)[i] = malloc(strlen(nameInterestNode->name)+1);
        strcpy((*menTrends)[i],nameInterestNode->name);
        tempNode = tempNode->next;
    }
    trendsNum->menTrendsNum = tempList->_size;
    destroyTempList(tempList);

    //destroy everything
    destroyInterestList(womenInterestList);
    destroyInterestList(menInterestList);
    destroyGraph(GraphWomen,1);
    destroyGraph(GraphMen,1);
    return trendsNum;
}

void EditInterestList(TempList* interestList,int k){
    TempNode* tempNode,*NodeToDelete;
    int tempInterestSize,topInterests;

    tempNode = interestList->head;
    topInterests = k;
    while(topInterests!=0 && tempNode!=NULL){
        tempNode = tempNode->next;
        topInterests--;
    }
    if(tempNode==NULL)
        return;
    tempInterestSize = tempNode->interestSize;

    while(tempNode!=NULL){
        NodeToDelete = tempNode;
        tempNode = tempNode->next;
        deleteTempNode(interestList,NodeToDelete);
    }

    tempNode = interestList->head;
    while(tempNode!=NULL){
        if(tempNode->interestSize == tempInterestSize){
            NodeToDelete = tempNode;
            tempNode = tempNode->next;
            deleteTempNode(interestList,NodeToDelete);
        }
        else
            tempNode = tempNode->next;
    }
}

void GraphEntry(Node* node,Graph* graph,Graph* OriginalGraph,char* gender){
    Node* NodeEntry;
    LNode* neighborNode;
    Edge* edge;
    Node* PossibleNeighbor;
    TagList* taglist;
    TagNode* tagNode,*newNode;

    NodeEntry = setPersonProperties(node->id,node->properties[0].property,node->properties[1].property,node->properties[2].property,node->properties[3].property,node->properties[4].property,node->properties[5].property,node->properties[6].property);
    taglist = node->properties[7].property;
    tagNode = taglist->head;
    while(tagNode!=NULL){
        newNode = createTagNode(tagNode->tag);
        addNewTagNode(NodeEntry->properties[7].property,newNode);
        tagNode = tagNode->next;
    }
    insertNode(NodeEntry,graph);
    neighborNode = node->neighbors->head;
    while(neighborNode!=NULL){
        PossibleNeighbor = lookupNode(neighborNode->edge->endNodeID,OriginalGraph);
        if(PossibleNeighbor->properties[2].property != NULL){//if neighbor has characteristics and tags
            if(strcmp(PossibleNeighbor->properties[2].property,gender) == 0){
                edge = setEdgeProperties(node->id,PossibleNeighbor->id,"knows",0);
                insertEdge(node->id,edge,graph);
            }
        }
        neighborNode = neighborNode->next;
    }
}

void TrustGraphEntry(Node* node,Graph* graph,Graph* OriginalGraph,int forum,HashBucketForum* hashBucketForum){
    double weight,fractionLikes,fractionReplies,totalLikes,likes,totalReplies,replies;
    Node* NodeEntry;
    LNode* neighborNode;
    Edge* edge;
    int i,hash_size,position;
    GenPostInfoNode* genPostInfoNode;
    PointerPostInfoNode* pointerPostInfoNode;

    hash_size = sqrt(OriginalGraph->statistics->vertices);
    hash_size = round(hash_size);

    NodeEntry = setPersonProperties(node->id,node->properties[0].property,node->properties[1].property,node->properties[2].property,node->properties[3].property,node->properties[4].property,node->properties[5].property,node->properties[6].property);
    insertNode(NodeEntry,graph);
    neighborNode = node->neighbors->head;

    while(neighborNode!=NULL){
        totalLikes = likes = totalReplies = replies = 0;
        for(i=0;i<hashBucketForum->records;i++){
            if(hashBucketForum->BucketTable[i]->forumId == forum && hashBucketForum->BucketTable[i]->personId == neighborNode->edge->endNodeID){
                position = hash_function(node->id,hash_size);
                genPostInfoNode = checkGenPostInfoNode(OriginalGraph->queries->HashTable2[position],node->id);
                if(genPostInfoNode == NULL)//if person has made no likes and no replies
                    break;
                else{
                    pointerPostInfoNode = genPostInfoNode->likePostList->head;
                    while(pointerPostInfoNode!=NULL){
                        if(pointerPostInfoNode->postInfoNode->forum == forum){
                            totalLikes++;
                            if(pointerPostInfoNode->postInfoNode->creator == neighborNode->edge->endNodeID)
                                likes++;
                        }
                        pointerPostInfoNode = pointerPostInfoNode->next;
                    }
                    pointerPostInfoNode = genPostInfoNode->replyPostList->head;
                    while(pointerPostInfoNode!=NULL){
                        if(pointerPostInfoNode->postInfoNode!=NULL){
                            if(pointerPostInfoNode->postInfoNode->forum == forum){
                                totalReplies++;
                                if(pointerPostInfoNode->postInfoNode->creator == neighborNode->edge->endNodeID)
                                    replies++;
                            }
                        }
                        pointerPostInfoNode = pointerPostInfoNode->next;
                    }
                    if(totalLikes == 0)
                        fractionLikes = 0;
                    else
                        fractionLikes = likes/totalLikes;
                    if(totalReplies == 0)
                        fractionReplies = 0;
                    else
                        fractionReplies = replies/totalReplies;

                    weight = 0.3*fractionLikes + 0.7*fractionReplies; //calculate weight
                    //printf("%f\n",weight);
                }
                if(weight == 0.0)
                    break;
                edge = setEdgeTrustProperties(node->id,neighborNode->edge->endNodeID,weight);
                insertEdge(node->id,edge,graph);
                break;
            }
        }
        neighborNode = neighborNode->next;
    }
}

void InterestEntry(Node* node,Graph* graph,InterestNode* interestNode){
    Node* NodeEntry;
    LNode* NeighborNode;
    TagList* list;
    int tagNode;
    Edge* edge;
    Node* PossibleTag;

    NodeEntry = setPersonProperties(node->id,node->properties[0].property,node->properties[1].property,node->properties[2].property,node->properties[3].property,node->properties[4].property,node->properties[5].property,node->properties[6].property);
    insertNode(NodeEntry,interestNode->interestGraph);
    NeighborNode = node->neighbors->head;
    while(NeighborNode != NULL){
        PossibleTag = lookupNode(NeighborNode->edge->endNodeID,graph);
        list = PossibleTag->properties[7].property;
        tagNode = checkTagList(list,interestNode->interest);
        if(tagNode == 0){
            NeighborNode = NeighborNode->next;
            continue;
        }
        edge = setEdgeProperties(node->id,PossibleTag->id,"knows",0);
        insertEdge(node->id,edge,interestNode->interestGraph);
        NeighborNode = NeighborNode->next;
    }
}

Graph* buildTrustGraph(int forum, Graph* graph){
    Node* node;
    int bucket,i;
    Graph* trustGraph;
    HashStructForum *hashStructForum;

    trustGraph = createGraph(M,C);
    if(graph->queries->flagForum == 0)
        createHashTableForum(graph);
    if(graph->queries->flagQ2 == 0)
        createHashTables(graph);

    createReplyList(graph);
    hashStructForum = graph->queries->HashStructForum;
    bucket = hashFunction(forum,hashStructForum->round,hashStructForum->Init_HT_Size);
    if(bucket < hashStructForum->pointer)
        bucket = hashFunction(forum,(hashStructForum->round)+1,hashStructForum->Init_HT_Size);
    for(i=0;i<hashStructForum->HashTable[bucket]->records;i++){
        if(hashStructForum->HashTable[bucket]->BucketTable[i]->forumId == forum){
            node = lookupNode(hashStructForum->HashTable[bucket]->BucketTable[i]->personId,graph);
            TrustGraphEntry(node,trustGraph,graph,forum,hashStructForum->HashTable[bucket]);
        }
    }
    return trustGraph;
}

double estimateTrust(Node* startNode,Node* endNode,Graph* graph) {
    TrustList *list;
    TrustNode *tempL,*trustNode,*trustTemp;
    LNode *neighbor;
    Node* node;
    HashStructTrust* hashStruct;
    int dist;
    double weight,trust;


    hashStruct = createHashStructTrust(M,C);
    list = createTrustList();
    node = lookupNode(startNode->id,graph);
    tempL = createTrustNode(node,0,1);//create TrustNode with dist = 0,trust = 1
    addNewTrustNode(list,tempL);
    insertNodeHashTrust(tempL,hashStruct);

    trustTemp = malloc(sizeof(TrustNode));
    neighbor = node->neighbors->head;
    tempL = list->head;

    while(tempL!=NULL){//while List is not empty
        if(tempL->node->id == endNode->id)//WE FOUND ENDNODE!!
            break;
        while(neighbor!=NULL){//for every neighbor of node
            trustNode = lookupNode7(neighbor->edge->endNodeID,hashStruct);
            if(trustNode == NULL){//if neighbor is not in hashStruct
                dist = tempL->dist + 1;//calculate shortest path
                node = lookupNode(neighbor->edge->endNodeID,graph);//lookup neighborNode
                trustNode = createTrustNode(node,dist,0);//calculate node
                addNewTrustNode(list,trustNode);//and add it to list
                insertNodeHashTrust(trustNode,hashStruct);
                weight = *((double*)(neighbor->edge->propEdge[0].property));
                trustNode->trust = (tempL->trust) * weight;
            }
            else{//if neighbor is in the list
                if(tempL->dist+1 == trustNode->dist){//if another shortest path is found
                    weight = *((double*)(neighbor->edge->propEdge[0].property));
                    trustTemp->trust = tempL->trust * weight;
                    if(trustTemp->trust > trustNode->trust)
                        trustNode->trust = trustTemp->trust;
                }
            }
            neighbor = neighbor->next;//go to next neighbor
        }
        tempL = tempL->next;//when all neighbors are checked,go to the next node of Dlist
        if(tempL!=NULL)
            neighbor = tempL->node->neighbors->head;//get first neighbor of next node
    }
    if(tempL!=NULL)
        trust = tempL->trust;
    else
        trust = -1;
    destroyHashStructTrust(hashStruct);
    free(list);
    free(trustTemp);
    return trust;
}

Graph* loadGraph(int bucketsNumber, int bucketSize){
    char name[22],surname[20],gender[7],birthday[11],creationdate[25],locationip[16],browser[19];
    char id[6],id1[6],id2[6],id3[6],temparray[80];
    Node* n1;
    Edge* e1;
    FILE *fp1,*fp2,*fp3;

    Graph* g = createGraph(M, C);
    //open files needed
    fp1 = fopen("person.csv","r");
    if(fp1 == NULL){
        printf("Error File can not be opened\n");
        exit(1);
    }
    fp2 = fopen("person_knows_person.csv","r");
    if(fp2 == NULL){
        printf("Error File can not be opened\n");
        exit(1);
    }
    fp3 = fopen("person_hasInterest_tag.csv","r");
    if(fp3 == NULL){
        printf("Error File can not be opened\n");
        exit(1);
    }
    //fscanf first line of file fp1
    fscanf(fp1,"%s\n",temparray);
    while(1){
        if(fscanf(fp1,"%[^|]|",id) == EOF)
            break;
        if(fscanf(fp1,"%[^|]|",name) != 1){
            fscanf(fp1,"%[^\n]\n",temparray);
            n1 = setPersonProperties(atoi(id),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
        }
        else{
            fscanf(fp1,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",surname,gender,birthday,creationdate,locationip,browser);
            n1 = setPersonProperties(atoi(id),name,surname,gender,birthday,creationdate,locationip,browser);
        }
        insertNode(n1,g);
    }
    fclose(fp1);
    // fscanf first line of file fp3
    fscanf(fp3,"%s\n",temparray);
    while(1){
        if(fscanf(fp3,"%[^|]|%[^\n]\n",id,id1) ==  EOF)
            break;
        n1 = lookupNode(atoi(id),g);
        if(n1 == NULL)
            continue;
        TagNode* node = createTagNode(atoi(id1));
        addNewTagNode((TagList*)n1->properties[7].property,node);
    }
    fclose(fp3);
    // fscanf first line of file fp2
    fscanf(fp2,"%s\n",temparray);
    while(1){
        if(fscanf(fp2,"%[^|]|%[^\n]\n",id2,id3) ==  EOF)
            break;
        e1 = setEdgeProperties(atoi(id2), atoi(id3), "knows", 0);
        insertEdge(atoi(id2), e1, g);
    }
    fclose(fp2);
    return g;
}
