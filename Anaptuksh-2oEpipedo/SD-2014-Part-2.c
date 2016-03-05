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

void testTidalTrust(int bucketsNumber, int bucketSize);
void stalkersGraphRunMetrics(Graph* gStalkers);

int main(void) {

    //firstly execute a test for centrality metrics on small graphs
    int m = 2;
    int c = 3;

//  testBetweennessCentrality(m, c);
//  testClosenessCentrality(m, c);

   //small example for trust graph estimation
   testTidalTrust(m, c);


    /*create graph from file*/
    int bucketsNumber = 10;
    int bucketSize = 5;
    Graph* g = loadGraph(bucketsNumber, bucketSize);

    //graph metrics calls

    //plot the graph degree distribution
    degreeDistribution(g);

    int diam = diameter(g);
    CHECKINT("Graph diameter", diam, 14);

    double avgPthLgth = averagePathLength(g);
    CHECKDOUBLE("Graph average path length", avgPthLgth, 5.0322);

    int ccNumber = numberOfCCs(g);
    CHECKINT("Graph number of components ", ccNumber, 1);

    int maximumCC = maxCC(g);
    CHECKINT("Graph maximum connected component ", maximumCC, 111);

    double dense = density(g);
    CHECKDOUBLE("Graph density ", dense, 0.073);

    int closenessIds[5] = {1734, 38, 8899, 3501, 75};
    float closenessIdsRes[5] = {0.3430, 0.3439, 0.3147, 0.2667, 0.1594};
    int i;
    for (i = 0; i < 5; ++i) {
        int nodeID = closenessIds[i];
        Node* node = lookupNode(nodeID, g);
        double closCentrty = closenessCentrality(node, g);
        CHECKDOUBLE("Graph closeness centrality ", closCentrty, closenessIdsRes[i]);
    }

    int betweennessIds[5] = {       1734,   38,     8899,   9900,   75};
    float betweennessIdsRes[5] = {  0.306,  0.053,  0.018,  0.005,  0.000};

    for (i = 0; i < 5; ++i) {
        int nodeID = betweennessIds[i];
        Node* node = lookupNode(nodeID, g);
        double betwCentrty = betweennessCentrality(node, g);
        //printf("%3f\n",betwCentrty);
        CHECKDOUBLE("Graph betweenness centrality ", betwCentrty, betweennessIdsRes[i]);
    }

    //graph queries calls
    // Query 1 //
    Matches* match;
    Node *dateNode = lookupNode(3755, g);
    int commonInterests = 1, ageDiff = 30, acquaintanceHops = 3, matchesNum = 1;
    match = matchSuggestion(dateNode, commonInterests, acquaintanceHops, ageDiff, matchesNum, g);
    //match result : 7107 - work_at_organization: 1650
    printMatchSuggestion(match);
    destroyMatches(match);

    // Query 2 //
    //estimate stalkers graph with closeness centrality
    Graph* stalkersGraphCloseCentr;
    StalkerList* stalkersCloseCentr;
    int stalkersNum = 7, likesNumber = 1, centralityMode = 1;
    stalkersGraphCloseCentr = getTopStalkers(stalkersNum, likesNumber, centralityMode, g, &stalkersCloseCentr);
    //int stalkersResultsIds[] = {347, 495, 7768, 8354, 8403, 8899, 9633};
    printf("Print Top Stalkers for closeness centrality:");
    printTopStalkers(stalkersCloseCentr);
    destroyStalkerList(stalkersCloseCentr);

    //run metrics on stalker-graph
    stalkersGraphRunMetrics(stalkersGraphCloseCentr);
    destroyGraph(stalkersGraphCloseCentr,1);
    //estimate stalkers graph with betweenness centrality
    Graph* stalkersGraphBetwCentr;
    StalkerList* stalkersBetwCentr;
    centralityMode = 2;
    stalkersGraphBetwCentr = getTopStalkers(stalkersNum, likesNumber, centralityMode, g, &stalkersBetwCentr);
    printf("Print Top Stalkers for betweenness centrality:");
    printTopStalkers(stalkersBetwCentr);
    destroyStalkerList(stalkersBetwCentr);

    //run metrics on stalker-graph
    stalkersGraphRunMetrics(stalkersGraphBetwCentr);
    destroyGraph(stalkersGraphBetwCentr,1);
    // Query 3 //
    int trendsNum = 4;
    //allocate result tables before calling query and pass them as parameters
    char** womenTrends;
    char** menTrends;
    TrendsNum* structTrendsNum;

    structTrendsNum = findTrends(trendsNum, g, &womenTrends, &menTrends);
    PrintTopTrends(structTrendsNum,womenTrends,menTrends);

/*results for men and women
 {"Sun_Yat-sen", "Constantine_the_Great","Sigmund_Freud", "Hussein_of_Jordan"}; //IDS: {417,11622,468,1398}
 {"Adolf_Hitler", "Chiang_Kai-shek", NULL, NULL}; //IDS: {138,416,null,null}
*/

        // Query 4 //
    Graph* trustGraph;
    int forumID = 34680;

    trustGraph = buildTrustGraph(forumID, g);

    int trustANodeId = 30;
    int trustBNodeId = 9805;
    int trustCNodeId = 9700;
    Node *ta = lookupNode(trustANodeId, trustGraph);
    Node *tb = lookupNode(trustBNodeId, trustGraph);
    Node *tc = lookupNode(trustCNodeId, trustGraph);
    printf("\n");
    double trustAB;
    trustAB = estimateTrust(ta, tb, trustGraph);
    printf("Trust between nodes (%d,%d) is %f\n", trustANodeId, trustBNodeId, trustAB);
    CHECKDOUBLE("Trust: (30,9805) ", trustAB, 0.134);

    double trustAC;
    trustAC = estimateTrust(ta, tc, trustGraph);
    printf("Trust between nodes (%d,%d) is %f\n", trustANodeId, trustCNodeId, trustAC);
    CHECKDOUBLE("Trust: (30,9700) ", trustAC, 0.15);

    destroyTrends(womenTrends,structTrendsNum->womenTrendsNum);
    destroyTrends(menTrends,structTrendsNum->menTrendsNum);
    free(structTrendsNum);
    destroyGraph(g,1);
    destroyGraph(trustGraph,0);
    return EXIT_SUCCESS;
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

void testBetweennessCentrality(int bucketsNumber, int bucketSize) {
    //create small graph for testing betweenness Centrality
    Graph* gBetw = createGraph(bucketsNumber, bucketSize);

    Node* n1Betw = createNode(1, NULL);
    Node* n2Betw = createNode(2, NULL);
    Node* n3Betw = createNode(3, NULL);
    Node* n4Betw = createNode(4, NULL);
    Node* n5Betw = createNode(5, NULL);

    insertNode(n1Betw, gBetw);
    insertNode(n2Betw, gBetw);
    insertNode(n3Betw, gBetw);
    insertNode(n4Betw, gBetw);
    insertNode(n5Betw, gBetw);

    /* Create edges and set properties */
    Edge* e1Betw = createEdge(1, 2, NULL);
    Edge* e2Betw = createEdge(2, 1, NULL);
    Edge* e3Betw = createEdge(2, 3, NULL);
    Edge* e4Betw = createEdge(2, 4, NULL);
    Edge* e5Betw = createEdge(3, 2, NULL);
    Edge* e6Betw = createEdge(3, 5, NULL);
    Edge* e7Betw = createEdge(4, 2, NULL);
    Edge* e8Betw = createEdge(4, 5, NULL);
    Edge* e9Betw = createEdge(5, 3, NULL);
    Edge* e10Betw = createEdge(5, 4, NULL);

    /* Insert edges in graph */
    insertEdge(1, e1Betw, gBetw);
    insertEdge(2, e2Betw, gBetw);
    insertEdge(2, e3Betw, gBetw);
    insertEdge(2, e4Betw, gBetw);
    insertEdge(3, e5Betw, gBetw);
    insertEdge(3, e6Betw, gBetw);
    insertEdge(4, e7Betw, gBetw);
    insertEdge(4, e8Betw, gBetw);
    insertEdge(5, e9Betw, gBetw);
    insertEdge(5, e10Betw, gBetw);

    //printf("%3f",averagePathLength(gBetw));

    double betwCentrty1 = betweennessCentrality(n1Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:1 ", betwCentrty1, 0.0 / 6.0);

    double betwCentrty2 = betweennessCentrality(n2Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:2 ", betwCentrty2, 3.5 / 6.0);

    double betwCentrty3 = betweennessCentrality(n3Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:3 ", betwCentrty3, 1.0 / 6.0);

    double betwCentrty4 = betweennessCentrality(n4Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:4 ", betwCentrty4, 1.0 / 6.0);

    double betwCentrty5 = betweennessCentrality(n5Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:5 ", betwCentrty5, 0.5 / 6.0);
}

void testClosenessCentrality(int bucketsNumber, int bucketSize){
    //create small graph for testing betweenness Centrality
    Graph* gClos = createGraph(bucketsNumber, bucketSize);

    Node* n1Clos = createNode(1, NULL);
    Node* n2Clos = createNode(2, NULL);
    Node* n3Clos = createNode(3, NULL);
    Node* n4Clos = createNode(4, NULL);
    Node* n5Clos = createNode(5, NULL);
    Node* n6Clos = createNode(6, NULL);
    Node* n7Clos = createNode(7, NULL);

    insertNode(n1Clos, gClos);
    insertNode(n2Clos, gClos);
    insertNode(n3Clos, gClos);
    insertNode(n4Clos, gClos);
    insertNode(n5Clos, gClos);
    insertNode(n6Clos, gClos);
    insertNode(n7Clos, gClos);

    /* Create edges and set properties */
    Edge* e1Clos = createEdge(1, 2, NULL);
    Edge* e2Clos = createEdge(1, 3, NULL);
    Edge* e3Clos = createEdge(2, 1, NULL);
    Edge* e4Clos = createEdge(2, 3, NULL);
    Edge* e5Clos = createEdge(3, 1, NULL);
    Edge* e6Clos = createEdge(3, 2, NULL);
    Edge* e7Clos = createEdge(3, 4, NULL);
    Edge* e8Clos = createEdge(4, 3, NULL);
    Edge* e9Clos = createEdge(4, 5, NULL);
    Edge* e10Clos = createEdge(5, 4, NULL);
    Edge* e11Clos = createEdge(5, 6, NULL);
    Edge* e12Clos = createEdge(5, 7, NULL);
    Edge* e13Clos = createEdge(6, 5, NULL);
    Edge* e14Clos = createEdge(6, 7, NULL);
    Edge* e15Clos = createEdge(7, 5, NULL);
    Edge* e16Clos = createEdge(7, 6, NULL);


     /* Insert edges in graph */
    insertEdge(1, e1Clos, gClos);
    insertEdge(1, e2Clos, gClos);
    insertEdge(2, e3Clos, gClos);
    insertEdge(2, e4Clos, gClos);
    insertEdge(3, e5Clos, gClos);
    insertEdge(3, e6Clos, gClos);
    insertEdge(3, e7Clos, gClos);
    insertEdge(4, e8Clos, gClos);
    insertEdge(4, e9Clos, gClos);
    insertEdge(5, e10Clos, gClos);
    insertEdge(5, e11Clos, gClos);
    insertEdge(5, e12Clos, gClos);
    insertEdge(6, e13Clos, gClos);
    insertEdge(6, e14Clos, gClos);
    insertEdge(7, e15Clos, gClos);
    insertEdge(7, e16Clos, gClos);


    double closCentrty1 = closenessCentrality(n1Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:1 ", closCentrty1, 3.33 / 6.0);

    double closCentrty2 = closenessCentrality(n2Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:2 ", closCentrty2, 3.33 / 6.0);

    double closCentrty3 = closenessCentrality(n3Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:3 ", closCentrty3, 4.16 / 6.0);

    double closCentrty4 = closenessCentrality(n4Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:4 ", closCentrty4, 4.0 / 6.0);

    double closCentrty5 = closenessCentrality(n5Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:5 ", closCentrty5, 4.16 / 6.0);

    double closCentrty6 = closenessCentrality(n6Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:6 ", closCentrty6, 3.33 / 6.0);

    double closCentrty7 = closenessCentrality(n7Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:7 ", closCentrty7, 3.33 / 6.0);

}

void testTidalTrust(int bucketsNumber, int bucketSize) {
    //create small graph for testing tidal's trust algorithm result
    Graph* gtt = createGraph(bucketsNumber, bucketSize);

    Node* n1tt = createNode(1, NULL);
    Node* n2tt = createNode(2, NULL);
    Node* n3tt = createNode(3, NULL);
    Node* n4tt = createNode(4, NULL);
    Node* n5tt = createNode(5, NULL);
    Node* n6tt = createNode(6, NULL);
    Node* n7tt = createNode(7, NULL);
    Node* n8tt = createNode(8, NULL);
    Node* n9tt = createNode(9, NULL);
    Node* n10tt = createNode(10, NULL);
    Node* n11tt = createNode(11, NULL);

    insertNode(n1tt, gtt);
    insertNode(n2tt, gtt);
    insertNode(n3tt, gtt);
    insertNode(n4tt, gtt);
    insertNode(n5tt, gtt);
    insertNode(n6tt, gtt);
    insertNode(n7tt, gtt);
    insertNode(n8tt, gtt);
    insertNode(n9tt, gtt);
    insertNode(n10tt, gtt);
    insertNode(n11tt, gtt);


    Edge* e1tt = setEdgeTrustProperties(1, 2, 1.0);
    Edge* e2tt = setEdgeTrustProperties(1, 5, 1.0);
    Edge* e3tt = setEdgeTrustProperties(2, 3, 0.9);
    Edge* e4tt = setEdgeTrustProperties(2, 4, 0.9);
    Edge* e5tt = setEdgeTrustProperties(3, 6, 0.8);
    Edge* e6tt = setEdgeTrustProperties(4, 6, 0.3);
    Edge* e7tt = setEdgeTrustProperties(4, 7, 0.9);
    Edge* e8tt = setEdgeTrustProperties(5, 10, 0.9);
    Edge* e9tt = setEdgeTrustProperties(6, 9, 1.0);
    Edge* e10tt = setEdgeTrustProperties(7, 8, 1.0);
    Edge* e11tt = setEdgeTrustProperties(8, 9, 1.0);
    Edge* e12tt = setEdgeTrustProperties(9, 11, 1.0);
    Edge* e13tt = setEdgeTrustProperties(10, 11, 0.4);

    insertEdge(1, e1tt, gtt);
    insertEdge(1, e2tt, gtt);
    insertEdge(2, e3tt, gtt);
    insertEdge(2, e4tt, gtt);
    insertEdge(3, e5tt, gtt);
    insertEdge(4, e6tt, gtt);
    insertEdge(4, e7tt, gtt);
    insertEdge(5, e8tt, gtt);
    insertEdge(6, e9tt, gtt);
    insertEdge(7, e10tt, gtt);
    insertEdge(8, e11tt, gtt);
    insertEdge(9, e12tt, gtt);
    insertEdge(10, e13tt, gtt);

    Node *att = lookupNode(1, gtt);

    Node *btt = lookupNode(11, gtt);
    //Estimate trust(1,11)
    double trust1_11 = estimateTrust(att, btt, gtt);
    CHECKDOUBLE("Graph estimate trust (1,11)", trust1_11, 0.36);

    //Estimate trust(1,9)
    Node *ctt = lookupNode(9, gtt);
    double trust1_9 = estimateTrust(att, ctt, gtt);
    CHECKDOUBLE("Graph estimate trust (1,9)", trust1_9, 0.72);
    destroyTestGraph(gtt,0);
}

void stalkersGraphRunMetrics(Graph* gStalkers) {

    printf("Stalkers graph executing metrics:\n");
    degreeDistribution(gStalkers);

    int diam = diameter(gStalkers);

    double avgPthLgth = averagePathLength(gStalkers);

    int ccNumber = numberOfCCs(gStalkers);

    int maximumCC = maxCC(gStalkers);

    double dense = density(gStalkers);
    printf("Diameter:%d\nAveragePathLength:%f\nccNumber:%d\nmaximumCC:%d\nDensity:%f\n",diam,avgPthLgth,ccNumber,maximumCC,dense);

}

void printMatchSuggestion(Matches* matches){
    MatchNode* tempmatc;

    printf("\nThis is your MatchSuggestion:\n");
    tempmatc = matches->head;
    if(tempmatc == NULL)
        printf("There are no matches for you!forever alone<3\n\n");
    while(tempmatc!=NULL){
        printf("Suggestion:person id = %d with similarityscore = %f\n\n",tempmatc->id,tempmatc->similarityScore);
        tempmatc = tempmatc->next;
    }
}

void printTopStalkers(StalkerList* stalkerList){
        StalkerNode* stalkerNode;
        ForumNode* temp;

        printf("\nTop Stalkers are:\n");
        stalkerNode = stalkerList->head;
        while(stalkerNode!=NULL){
            printf("Stalker:%d with centrality score:%f in forums:\n ",stalkerNode->node->id,stalkerNode->centralityScore);
            temp = stalkerNode->forumList->head;
            while(temp!=NULL){
                printf("%d\n ",temp->forum);
                temp = temp->next;
            }
            stalkerNode = stalkerNode->next;
            printf("\n");
        }
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
