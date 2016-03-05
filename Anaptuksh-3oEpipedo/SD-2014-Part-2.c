/*
 ============================================================================
 Name        : SD-2014-Part-2.c
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */
#include "defines.h"
#define TRUST_GRAPH_REL_PROPERTIES_NUM 1

#define CHECKINT(text, actual, expected)                         \
  if (actual != expected) {                                   \
    printf("%-30s: Failed | actual = %3d, expected = %3d\n",  \
           text,                                              \
           actual,                                            \
           expected);                                         \
  } else {                                                    \
    printf("%-30s: Success\n", text);                     \
  }

#define CHECKDOUBLE(text, actual, expected)                         \
if ( (ABS(actual,expected)) > 0.01 ) {                                   \
  printf("%-30s: Failed | actual = %3f, expected = %3f\n",  \
         text,                                              \
         actual,                                            \
         expected);                                         \
} else {                                                    \
  printf("%-30s: Success\n", text);                     \
}

#define ABS(value1, value2) (value1 - value2 < 0 ) ? value2 - value1 : value1 - value2

//global variables
PoolList* poolList;
pthread_mutex_t mtx;
pthread_cond_t cond_nonempty;
pthread_mutex_t mtx2;
pthread_cond_t cond_forumGraphsReady;
int jobsToBeDone = JOBS_TO_BE_DONE;
int countForumGraphs = 0;

int main(void) {
    int i,err;
    pthread_t threads[THREADSNUM];
    TopForumList* topForumList;
    Cpm** cpm;
    Gn **gn = NULL;

    //initialize poolList,mutex and conditionVariable
    poolList = createPoolList();
    pthread_mutex_init(&mtx,0);
    pthread_cond_init(&cond_nonempty,0);
    //create THREADSNUM threads
    for(i=0;i<THREADSNUM;i++)
        if( (err = pthread_create(&threads[i],NULL,threadFunction,NULL))){
            perror2("pthread_create",err);
            exit(1);
        }
    //load graph using files
    int bucketsNumber = 10;
    int bucketSize = 5;
    Graph* g = loadGraph(bucketsNumber, bucketSize);

	topForumList = PreperationFunction(g,NUMBER_OF_TOP_N_FORUMS);
    //printTopNForums(topForumList);
    int cliqueSize[2] = {3, 4};
    cpm =  computeCPMResults(g,cliqueSize,topForumList);
    validateCPMResults(cpm);

    double modularityMax = DBL_MAX;
    gn = computeGNResults(g,modularityMax,topForumList);
    validateGNResults(gn);

    free_memory(topForumList,cpm,gn);//free memory function

/*  Graph* g = createTempGraph();
    EdgeList* edgeList = createEdgeList();
    //find all GraphEdges
    findEdges(g,edgeList);
    //calculate communities of graph
    //printf("%d",DBL_MAX);
    double modularityMax = DBL_MAX;
    Community* communities = GirvanNewman(modularityMax,g,edgeList);
    for(int i=0;i<g->communitiesInfo->communitiesNum;i++){
        for(int j=0;j<communities[i].numberOfGeneralMembers;j++)
            printf("member:%d\n",communities[i].generalMembers[j]);
        fflush(stdout);
        printf("\n");
    }

    destroyGraph(g);
*/
     //wait until all threads are done with their jobs
    for(i=0;i<THREADSNUM;i++)
        if( (err = pthread_join(threads[i],NULL)) ){
            perror2("pthread_join",err);
            exit(1);
        }
    //destroy mutex and conditionVariable
    free(poolList);
    pthread_cond_destroy(&cond_nonempty);
    pthread_mutex_destroy(&mtx);

    return EXIT_SUCCESS;
}

Graph* createTempGraph(){
    int i,j;
    Graph* g = createGraph(M,C,0);
    Node* n1 = createNode(1, NULL);
    Node* n2 = createNode(2, NULL);
    Node* n3 = createNode(3, NULL);
    Node* n4 = createNode(4, NULL);
    Node* n5 = createNode(5, NULL);
    Node* n6 = createNode(6, NULL);
    Node* n7 = createNode(7, NULL);
    Node* n8 = createNode(8, NULL);
    Node* n9 = createNode(9, NULL);

    insertNode(n1,g);
    insertNode(n2,g);
    insertNode(n3,g);
    insertNode(n4,g);
    insertNode(n5,g);
    insertNode(n6,g);
    insertNode(n7,g);
    insertNode(n8,g);
    insertNode(n9,g);

    Edge* e1 = setEdgeProperties(1, 2, "connects",0);
    Edge* e4 = setEdgeProperties(2, 1, "connects",0);
    Edge* e2 = setEdgeProperties(1, 3, "connects",0);
    Edge* e6 = setEdgeProperties(3, 1, "connects",0);
    Edge* e3 = setEdgeProperties(1, 4, "connects",0);
    Edge* e9 = setEdgeProperties(4, 1, "connects",0);
    Edge* e5 = setEdgeProperties(2, 3, "connects",0);
    Edge* e8 = setEdgeProperties(3, 2, "connects",0);
    Edge* e7 = setEdgeProperties(3, 4, "connects",0);
    Edge* e10 = setEdgeProperties(4, 3, "connects",0);
    Edge* e11 = setEdgeProperties(4, 5, "connects",0);
    Edge* e12 = setEdgeProperties(4, 6, "connects",0);
    Edge* e13 = setEdgeProperties(5, 4, "connects",0);
    Edge* e14 = setEdgeProperties(5, 6, "connects",0);
    Edge* e15 = setEdgeProperties(5, 8, "connects",0);
    Edge* e16 = setEdgeProperties(5, 7, "connects",0);
    Edge* e17 = setEdgeProperties(6, 4, "connects",0);
    Edge* e18 = setEdgeProperties(6, 5, "connects",0);
    Edge* e19 = setEdgeProperties(6, 7, "connects",0);
    Edge* e20 = setEdgeProperties(6, 8, "connects",0);
    Edge* e21 = setEdgeProperties(7, 5, "connects",0);
    Edge* e22 = setEdgeProperties(7, 6, "connects",0);
    Edge* e23 = setEdgeProperties(7, 8, "connects",0);
    Edge* e24 = setEdgeProperties(7, 9, "connects",0);
    Edge* e25 = setEdgeProperties(8, 6, "connects",0);
    Edge* e26 = setEdgeProperties(8, 5, "connects",0);
    Edge* e27 = setEdgeProperties(8, 7, "connects",0);
    Edge* e28 = setEdgeProperties(9, 7, "connects",0);

    insertEdge(1, e1, g);
    insertEdge(1, e2, g);
    insertEdge(1, e3, g);
    insertEdge(2, e4, g);
    insertEdge(2, e5, g);
    insertEdge(3, e6, g);
    insertEdge(3, e7, g);
    insertEdge(3, e8, g);
    insertEdge(4, e9, g);
    insertEdge(4, e10, g);
    insertEdge(4, e11, g);
    insertEdge(4, e12, g);
    insertEdge(5, e13, g);
    insertEdge(5, e14, g);
    insertEdge(5, e15, g);
    insertEdge(5, e16, g);
    insertEdge(6, e17, g);
    insertEdge(6, e18, g);
    insertEdge(6, e19, g);
    insertEdge(6, e20, g);
    insertEdge(7, e21, g);
    insertEdge(7, e22, g);
    insertEdge(7, e23, g);
    insertEdge(7, e24, g);
    insertEdge(8, e25, g);
    insertEdge(8, e26, g);
    insertEdge(8, e27, g);
    insertEdge(9, e28, g);

/*    for(i=0;i<g->HT_Size;i++)
        for(j=0;j<g->HashTable[i]->records;j++)
            printf("%d\n",g->HashTable[i]->BucketTable[j]->id);
*/
    return g;
}

void printTopNForums(TopForumList* topForumList){
    TopForumNode* temp;
    int i,j;
    temp = topForumList->head;
    while(temp!=NULL){
        printf("%d , %d , %s\n",temp->nameForumNode->forumId,temp->membersNum,temp->nameForumNode->forumName);
        for(i=0;i<temp->graph->HT_Size;i++)
            for(j=0;j<temp->graph->HashTable[i]->records;j++)
                printf("Member:%d\n",temp->graph->HashTable[i]->BucketTable[j]->id);
        temp = temp->next;
    }
}

void editCommunityMembers(intList* intList,CliqueList* cliqueList){
    CliqueNode* cliqueNode;

    cliqueNode = cliqueList->head;
    while(cliqueNode!=NULL){
        //check intList for id and create one if it doesn't already exist
        checkIntList(intList,cliqueNode->hyperNodeMember);
        cliqueNode = cliqueNode->next;
    }
    return;
}

Edge* setEdgeTrustProperties(int startNodeID, int endNodeID, double trust) {
    Properties* propEdge = createProperties(TRUST_GRAPH_REL_PROPERTIES_NUM);
    setDoubleProperty(trust, 0, propEdge);


    Edge* e = createEdge(startNodeID, endNodeID, propEdge);
    return e;
}

/*void printEdgeProperties(int startID, Edge* e) {
    //TODO
}
*/
void PrintTopTrends(TrendsNum* structTrendsNum,char** womenTrends,char** menTrends){
    int i;
    printf("\nTop WomenInterests are:\n");
    for(i=0;i<structTrendsNum->womenTrendsNum;i++)
        printf("%s\n",womenTrends[i]);

    printf("\nTop MenInterests are:\n");
    for(i=0;i<structTrendsNum->menTrendsNum;i++)
        printf("%s\n",menTrends[i]);
    return;
}

Node* setPersonProperties(int id, char* name,char* surname ,char* gender,char* birthday,char* creationDate,char* locationIP,char* browser) {

    Node* n;
    Properties* prop = createProperties(PERSON_PROPERTIES_NUM);
    if(name != NULL){
        setStringProperty(name, 0, prop);
        setStringProperty(surname, 1, prop);
        setStringProperty(gender, 2, prop);
        setStringProperty(birthday, 3, prop);
        setStringProperty(creationDate,4, prop);
        setStringProperty(locationIP, 5, prop);
        setStringProperty(browser, 6, prop);
        prop[7].property = (TagList*)createTagList();
    }
    else
        prop[0].property = prop[1].property = prop[2].property = prop[3].property = prop[4].property = prop[5].property = prop[6].property = prop[7].property = NULL;
    n = createNode(id,prop);
    return n;
}

void SetTagProperties(Node* node,int id){

    setDoubleProperty(id,7,node->properties);

}
Edge* setEdgeProperties(int startNodeID, int endNodeID, char* type, double weight) {

    /*create edge properties*/
    Properties* propEdge = createProperties(PERSON_REL_PROPERTIES_NUM);
    setStringProperty(type, 0, propEdge);
    setDoubleProperty(weight, 1, propEdge);

    /*create an edge*/
    Edge* e = createEdge(startNodeID, endNodeID, propEdge);
    return e;
}

void printPersonProperties(Node* n) {
    char* name,*surname,*gender,*birthday,*creationDate,*locationIP,*browser;
    TagNode* temp;
    TagList* list;

    if(n == NULL)
        return;
    list = n->properties[7].property;
    name = getStringProperty(0, n->properties);
    surname = getStringProperty(1, n->properties);
    gender = getStringProperty(2, n->properties);
    birthday = getStringProperty(3, n->properties);
    creationDate = getStringProperty(4, n->properties);
    locationIP = getStringProperty(5, n->properties);
    browser = getStringProperty(6, n->properties);
    printf("id:%d,%s,%s,%s,%s,%s,%s,%s",n->id,name,surname,gender,birthday,creationDate,locationIP,browser);
    if(list!=NULL){
        temp = list->head;
        while(temp!=NULL){
            printf(",%d",temp->tag);
            temp =temp->next;
        }
    }
    printf("\n");
}

void printEdgeProperties(int startID, Edge* e) {
    char* type;
    int weight;

    type = getStringProperty(0, e->propEdge);
    weight = getIntegerProperty(1,e->propEdge);
    printf("ID = %d --->%d %s %d\n",startID,e->endNodeID,type,weight);
}
