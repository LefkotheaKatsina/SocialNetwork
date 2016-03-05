#ifndef GRAPHLIB_H_
#define GRAPHLIB_H_
typedef struct PointerPostInfoList PointerPostInfoList;

typedef struct ForumNode{
    int forum;
    struct ForumNode*next,*prev;
}ForumNode;

typedef struct ForumList{
    ForumNode* head,*tail;
    int _size;
}ForumList;

typedef struct LikeNode{
    int creator;
    int likes;
    struct LikeNode* next,*prev;
}LikeNode;

typedef struct LikeList{
    LikeNode* head,*tail;
    int _size;
}LikeList;

struct properties {
    void* property;
};
typedef struct properties Properties;

struct pair {
    int ID; // the id of a node
    int distance; //the distance from the node
};
typedef struct pair Pair;

struct edge{
    int startNodeID;
    int endNodeID;
    Properties* propEdge;
};
typedef struct edge Edge;

typedef struct TagNode{
    int tag;
    struct TagNode* next,*prev;
}TagNode;

typedef struct TagInfo{
    int sameInterests;
    int Interests;
    struct TagInfo *next,*prev;
}TagInfo;

typedef struct HNode{
    int neighbors;
    int vertices;
    struct HNode* next,*prev;
}HNode;

typedef struct MatchNode{
    int id;
    double similarityScore;
    struct MatchNode *next,*prev;
}MatchNode;

typedef struct Matches{
    MatchNode* head,*tail;
    int _size;
}Matches;

typedef struct LNode{
    Edge* edge;
    struct LNode *next,*prev;
}LNode;

typedef struct List{
    LNode *head,*tail;
    int _size; //this shows number of neighbors of a person
}List;

typedef struct TagList{
    TagNode *head,*tail;
    int _size; //this shows number of neighbors of a person
}TagList;

typedef struct Node{
    int id;
    Properties* properties;
    List* neighbors;
    struct Node* next,*prev;
}Node;

typedef struct StalkerNode{
    Node* node;
    double centralityScore;
    int stalkerScore;
    struct StalkerNode* next,*prev;
    ForumList* forumList;
}StalkerNode;

typedef struct StalkerList{
    StalkerNode* head,*tail;
    int _size;
}StalkerList;

typedef struct DNode{
    Node* node;
    int dist;
    struct DNode* next,*prev;
}DNode;

typedef struct CNode{
    int dist;
    Node* node;
    int paths;
    int bridges;
    struct CNode *next,*prev;
}CNode;

typedef struct DList{
    DNode *head,*tail;
    int _size; //this shows number of neighbors of a person
}DList;

typedef struct HList{
    HNode *head,*tail;
    int _size;
}HList;

typedef struct CList{
    CNode *head,*tail;
    int _size;
}CList;

typedef struct PostInfoNode{
    int post;
    int forum;
    int creator;
    struct PostInfoNode* next,*prev;
}PostInfoNode;

typedef struct PointerPostInfoNode{
    int data;
    PostInfoNode* postInfoNode;
    struct PointerPostInfoNode *next,*prev;
}PointerPostInfoNode;

typedef struct PointerPostInfoList{
    PointerPostInfoNode* head,*tail;
    int _size;
}PostInfoList;

typedef struct GenPostInfoList{
    struct GenPostInfoNode* head,*tail;
    int _size;
}GenPostInfoList;

typedef struct GenPostInfoNode{
    int id;
    PointerPostInfoList* likePostList;
    PointerPostInfoList* replyPostList;
    struct GenPostInfoNode *next,*prev;
}GenPostInfoNode;

typedef struct WorkPlaceNode{
    int workPlace;
    struct WorkPlaceNode *next,*prev;
}WorkPlaceNode;

typedef struct WorkPlaceList{
   WorkPlaceNode* head,*tail;
    int _size;
}WorkPlaceList;

typedef struct InfoNode{
    int studyPlace;
    WorkPlaceList* workPlace;
    int livePlace;
    int id;
    struct InfoNode* next,*prev;
}InfoNode;

typedef struct InfoList{
    InfoNode* head,*tail;
    int _size;
}InfoList;

typedef struct Bucket{
    Node **BucketTable;
    int size;
    int records;
}Bucket;

typedef struct HashBucket{
    CNode **BucketTable;
    int size;
    int records;
}HashBucket;

typedef struct HashBucketD{
    DNode **BucketTable;
    int size;
    int records;
}HashBucketD;

typedef struct HashBucketPost{
    PostInfoNode **BucketTable;
    int size;
    int records;
}HashBucketPost;

typedef struct Statistics{
    int distanceSum;
    int distanceNum;
    int vertices;
    int edges;
    int diameter;
    int CCNum;
    int maxCCvertNum;
}Statistics;

typedef struct NameInterestNode{
    int InterestId;
    char* name;
    struct NameInterestNode* next,*prev;
}NameInterestNode;

typedef struct HashBucketInterest{
    NameInterestNode** BucketTable;
    int size;
    int records;
}HashBucketInterest;

typedef struct HashStructInterest{
    HashBucketInterest **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStructInterest;

typedef struct HashStruct{
    HashBucket **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStruct;

typedef struct HashStructD{
    HashBucketD **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStructD;

typedef struct HashStructPost{
    HashBucketPost **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStructPost;

typedef struct ForumMembersNode{
    int personId;
    struct ForumMembersNode* next,* prev;
}ForumMembersNode;

typedef struct ForumMembersList{
    ForumMembersNode* head,*tail;
    int _size;
}ForumMembersList;

typedef struct NameForumNode{
    int forumId;
    char* forumName;
    ForumMembersList* forumMembersList;
    struct NameForumNode* next,*prev;
}NameForumNode;

typedef struct HashBucketForum{
    NameForumNode** BucketTable;
    int size;
    int records;
}HashBucketForum;

typedef struct CommentNode{
    int commentId;
    struct CommentNode* next,*prev;
    PointerPostInfoNode* pointerPostInfoNode;
}CommentNode;


typedef struct HashBucketComment{
    CommentNode** BucketTable;
    int size;
    int records;
}HashBucketComment;

typedef struct HashStructComment{
    HashBucketComment **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;

}HashStructComment;

typedef struct HashStructForum{
    HashBucketForum **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStructForum;

typedef struct Queries{
    InfoList** HashTable1;
    HashStructPost* HashTablePost; //post info
    GenPostInfoList** HashTable2;
    HashStructInterest* HashTableInterest;
    HashStructForum* HashStructForum;
    int flagForum;
    int flagQ1;
    int flagQ2;
    int flagInterest;
}Queries;

typedef struct CliqueNode{
    struct CliqueNode* next,*prev;
    int hyperNodeMember;
}CliqueNode;

typedef struct CliqueList{
    CliqueNode* head,*tail;
    int _size;
}CliqueList;

typedef struct HyperNode{
    Node* node;
    CliqueList* cliqueList;
    struct HyperNode* next,*prev;
}HyperNode;

typedef struct HyperList{
    HyperNode* head,*tail;
    int _size;
}HyperList;

typedef struct Community{
    int numberOfGeneralMembers;
    int *generalMembers;
    int numberOfMembers;
    int *members;
}Community;

typedef struct CommunitiesInfo{
    int communitiesNum;
    int sizeCount;
    int newCCFlag;
    Community* communities;
}CommunitiesInfo;

struct graph {
    Bucket **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
    Statistics* statistics;
    Queries* queries;
    CommunitiesInfo* communitiesInfo;
};
typedef struct graph Graph;

struct resultSet {
    DList* list;
    DNode* tempL;
    LNode* neighbor;
    LNode* hold;
    HashStructD* hashStruct;
    Graph const* graph;
};
typedef struct resultSet ResultSet;

typedef struct InterestNode{
    int interest;
    int interestSize;
    Graph* interestGraph;
    struct InterestNode *next,*prev;
}InterestNode;

typedef struct InterestList{
    struct InterestNode *head,*tail;
    int _size;
}InterestList;

typedef struct TempNode{
    int interest;
    int interestSize;
    struct TempNode* next,*prev;
}TempNode;

typedef struct TempList{
    struct TempNode *head,*tail;
    int _size;
}TempList;

typedef struct TrendsNum{
    int womenTrendsNum;
    int menTrendsNum;
}TrendsNum;

typedef struct CreatorNode{
    struct CreatorNode* next,*prev;
    int creator;
}CreatorNode;

typedef struct CreatorList{
    CreatorNode* head,*tail;
    int _size;
}CreatorList;

typedef struct TrustNode{
    int dist;
    double trust;
    Node* node;
    struct TrustNode* next,*prev;
}TrustNode;

typedef struct TrustList{
    TrustNode* head,*tail;
    int _size;
}TrustList;

typedef struct HashBucketTrust{
    TrustNode ** BucketTable;
    int size;
    int records;
}HashBucketTrust;

typedef struct HashStructTrust{
    HashBucketTrust **HashTable;
    int Init_HT_Size; //initial size of hash table
    int NextSplitPointer;
    int InitBucketSize; //initial size of BucketTable
    int HT_Size; //dynamic size of hash table
    int pointer;
    int round;
}HashStructTrust;

typedef struct TopForumNode{
    struct TopForumNode * next,*prev;
    NameForumNode* nameForumNode;
    int membersNum;
    Graph *graph;
}TopForumNode;

typedef struct Data{
    TopForumNode* topForumNode;
    Graph* graph;
}Data;

typedef struct TopForumList{
    int _size;
    TopForumNode * head,*tail;
}TopForumList;

typedef struct BronKerNode{
    struct BronKerNode* next,*prev;
    int personId;
}BronKerNode;

typedef struct BronKerList{
    BronKerNode* head,*tail;
    int _size;
}BronKerList;

typedef struct algorithmResults{
    int numberOfCommunities;
    Community *communities;
}algorithmResults;

typedef struct cpm{
    char *forum;
    algorithmResults clique3;
    algorithmResults clique4;
}Cpm;

typedef struct gn{
    char *forum;
    algorithmResults results;
}Gn;

typedef struct intNode{
    struct intNode *next,*prev;
    int memberId;
}intNode;

typedef struct intList{
    int _size;
    struct intNode *head,*tail;
}intList;

typedef struct PoolNode{
    struct PoolNode *next,*prev;
    void* data;
    void (*functionPtr)(void*);
}PoolNode;

typedef struct PoolList{
    int _size;
    struct PoolNode *head,*tail;
}PoolList;

typedef struct EdgeNode{
    struct EdgeNode *next,*prev;
    Node* vertice1;
    Node* vertice2;
    double edgeBetweenness;
}EdgeNode;

typedef struct EdgeList{
    int _size;
    struct EdgeNode *head,*tail;
}EdgeList;

InterestList* createInterestList();
InterestNode* createInterestNode();
void destroyInterestList(InterestList*);
void deleteInterestNode(InterestList*,InterestNode*);
void addNewInterestNode(InterestList*,InterestNode*);
InterestNode* checkInterestList(InterestList*,int);

/*Help functions for test main*/
Properties* createProperties(int);
void setStringProperty(char*,int,Properties*);
void setDoubleProperty(double,int,Properties*);
char* getStringProperty(int,Properties*);
int getIntegerProperty(int,Properties*);
Node* createNode(int,Properties*);
Edge* createEdge(int,int,Properties*);

/*Functions for implementation of part 1*/
Graph* createGraph(int,int,int);
int destroyGraph(Graph*);
int insertNode(const Node* const, Graph*);
int insertEdge(int,const Edge* const,Graph*);
Node* lookupNode(int,const Graph* const);
CNode* lookupNode2(int, HashStruct*);
DNode* lookupNode3(int, HashStructD*);
PostInfoNode* lookupNode4(int,HashStructPost*);
NameInterestNode* lookupNode5(int,HashStructInterest*);
CommentNode* lookupNode6(int,HashStructComment*);
int reachNode1(int,int,const Graph* const);
ResultSet* reachNodeN(int,const Graph* const);
int next(ResultSet*,Pair*);

List* createList();
DList* createDList();
HList* createHList();
CList* createCList();
TagList* createTagList();
InfoList* createInfoList();
Matches* createMatches();
PostInfoList* createPostInfoList();
GenPostInfoList* createGenPostInfoList();
LikeList* createLikeList();
StalkerList* createStalkerList();
ForumList* createForumList();

LNode* createLNode();
HNode* createHNode(int);
DNode* createDNode(Node*,int);
CNode* createCNode(Node*,int);
TagNode* createTagNode(int);
InfoNode* createInfoNode(int,int);
MatchNode* createMatchNode(int,double);
GenPostInfoNode* createGenPostInfoNode(int);
PostInfoNode* createPostInfoNode(int,int);
LikeNode* createLikeNode(int);
StalkerNode* createStalkerNode(Node*,float,int);
ForumNode* createForumNode(int);
NameInterestNode* createNameInterestNode(int,char*);
PointerPostInfoNode* createPointerPostInfoNode(PostInfoNode*);

void addNewLNode(List*,LNode*);
void addNewDNode(DList*,DNode*);
void addNewCNode(CList*,CNode*);
void addNewHNode(HList*,HNode*);
void addNewTagNode(TagList*,TagNode* );
void addNewInfoNode(InfoList*,InfoNode*);
void addNewPostInfoNode(PostInfoList*,PostInfoNode*);
void addNewGenPostInfoNode(GenPostInfoList*,GenPostInfoNode*);
void InsertToMatches(Matches*, MatchNode*,int);
void addNewLikeNode(LikeList*,LikeNode*);
void addNewStalkerNode(StalkerList*,StalkerNode*);
void addNewForumNode(ForumList*,ForumNode*);
void addNewPointerPostInfoNode(PointerPostInfoList*,PointerPostInfoNode*);

void destroyList(List*);
void destroyCList(CList*);
void destroyHList(HList*);
void destroyDList(DList*);
void destroyTagList(TagList *);
void destroyInfoList(InfoList *);
void destroyMatches(Matches*);
void destroyPostInfoList(PostInfoList*);
void destroyGenPostInfoList(GenPostInfoList*);
void destroyLikeList(LikeList*);
void destroyStalkerList(StalkerList*);
void destroyForumList(ForumList*);
void destroyHashBucketPost(HashBucketPost*);
void destroyHashStructPost(HashStructPost*);
void destroyHashStruct(HashStruct*);
void destroyHashBucket(HashBucket*);
void destroyHashBucketD(HashBucketD*);
void destroyHashStructD(HashStructD*);
void destroyHashStructInterest(HashStructInterest*);
void destroyTrends(char**,int);

void deleteLNode(List*,LNode*);
void deleteDNode(DList*,DNode*);
void deleteCNode(CList*,CNode*);
void deleteHNode(HList*,HNode*);
void deleteTagNode(TagList*,TagNode*);
void deleteInfoNode(InfoList*,InfoNode*);
void deleteMatchNode(Matches*,MatchNode*);
void deleteGenPostInfoNode(GenPostInfoList*,GenPostInfoNode*);
void deletePostInfoNode(PostInfoList*,PostInfoNode*);
void deleteLikeNode(LikeList*,LikeNode*);
void deleteStalkerNode(StalkerList*,StalkerNode*);
void deleteForumNode(ForumList*,ForumNode*);
void deleteNameInterestNode(NameInterestNode*);

int checkList(List*,int);
DNode* check(DList*,int);
CNode* checkCList(CList*,int);
HNode* checkHList(HList*,int);
StalkerNode* checkStalkerList(StalkerList*,int);
InfoNode* checkInfoList(InfoList*,int);
int checkTagList(TagList*,int);
LikeNode* checkLikeList(LikeList*,int);
ForumNode* checkForumList(ForumList*,int);
GenPostInfoNode* checkGenPostInfoNode(GenPostInfoList*,int);

int hashFunction(int,int,int);
int hash_function(int,int);

int insertNodeHash(const CNode* const, HashStruct*);
int insertNodeHashD(const DNode* const, HashStructD*);

void createHashBucket(HashStruct*,int,int);
void createHashBucketD(HashStructD*,int,int);
void createHashBucketPost(HashStructPost*,int,int);
HashStruct* createHashStruct(int,int);
HashStructD* createHashStructD(int,int);

HList** createHashTable(int);
Node* partition(Node**,int,int,int);
CNode* partition2(CNode**,int,int,int);
DNode* partition3(DNode**,int,int,int);
PostInfoNode* partition4(PostInfoNode**,int,int,int);
NameInterestNode* partition5(NameInterestNode**,int,int,int);
CommentNode* partition6(CommentNode**,int,int,int);
int findPosition(Node**,int,int,int);
int findPosition2(CNode**,int,int,int);
int findPosition3(DNode**,int,int,int);
int findPosition4(PostInfoNode**,int,int,int);
int findPosition5(NameInterestNode **,int,int,int);
int findPosition6(NameForumNode**,int,int,int);
int findPosition7(CommentNode**,int,int,int);

void CalculateStatistics(Graph* graph);
void degreeDistribution(Graph*);
int diameter(Graph*);
double averagePathLength(Graph*);
double density(Graph*);
int numberOfCCs(Graph*);
double closenessCentrality(Node*,Graph*);
double betweennessCentrality(Node*,Graph*);
double bfs(Node*,Node*,Graph*);
void SetTagProperties(Node*,int);
int maxCC(Graph* );

void createHashTableQ1(Graph*);
void createHashTables(Graph *);
Matches* matchSuggestion(Node*,int,int,int,int,Graph*);
TagInfo* IsPossibleMatch(Node* startNode,Node* possibleMatch,int x,int k,Graph* graph);

Graph* getTopStalkers(int,int,int,Graph*,StalkerList**);
void printTopStalkers(StalkerList*);
void printMatchSuggestion(Matches*);
Edge* setEdgeProperties(int,int,char*,double);
Node* setPersonProperties(int, char*,char*,char*,char*,char*,char*,char*);

void addNewTempNode(TempList* ,TempNode*);
TempNode* createTempNode(int,int);
TempList* createTempList();
void deleteTempNode(TempList*,TempNode*);
void destroyTempList(TempList* );

TrendsNum* findTrends(int ,Graph*,char***,char***);
void TagEntry(Node*,Graph*,int,Graph* );
void GraphEntry(Node*,Graph*,Graph*,char*);
void InterestEntry(Node*,Graph*,InterestNode*);
HashStructInterest* createHashStructInterest(int, int);
void createHashBucketInterest(HashStructInterest *,int,int);

HashStructForum* createHashStructForum(int,int);
NameForumNode* createNameForumNode(int ,int);
void createHashBucketForum(HashStructForum* ,int ,int );
void destroyHashStructForum(HashStructForum* );
void createHashBucketComment(HashStructComment*,int ,int );
CommentNode* createCommentNode(int ,PointerPostInfoNode* );
void createReplyList(Graph* );
Graph* buildTrustGraph(int,Graph*);

void testBetweennessCentrality(int bucketsNumber, int bucketSize);
void testClosenessCentrality(int bucketsNumber, int bucketSize);
Graph* loadGraph(int,int);
int checkWorkPlaceList(InfoNode*,WorkPlaceList *);
void destroyWorkPlaceList(WorkPlaceList*);
WorkPlaceNode* createWorkPlaceNode(int);
void addNewWorkPlaceNode(WorkPlaceList*,WorkPlaceNode*);
void EditInterestList(TempList*,int);

CreatorList* createCreatorList();
CreatorNode* createCreatorNode(int);
void addNewCreatorNode(CreatorList*,CreatorNode*);
void deleteCreatorNode(CreatorList*,CreatorNode*);
void destroyCreatorList(CreatorList*);
void EditStalkersList(StalkerList*,int);
void printPersonProperties(Node*);
void PrintTopTrends(TrendsNum*,char**,char**);

void deleteTrustNode(TrustList*,TrustNode*);
void destroyTrustList(TrustList*);
void createHashBucketTrust(HashStructTrust*,int,int);
int findPosition8(TrustNode**,int,int,int);
TrustNode* partition7(TrustNode**,int,int,int);
TrustNode* lookupNode7(int,HashStructTrust*);
TrustList* createTrustList();
TrustNode* createTrustNode(Node*,int,double);
void addNewTrustNode(TrustList*,TrustNode*);
double estimateTrust(Node*,Node*,Graph*);
Edge* setEdgeTrustProperties(int,int,double);

NameForumNode* lookupForum(int,HashStructForum*);
ForumMembersList* createForumMembersList();
ForumMembersNode* createForumMembersNode(int);
void addNewForumMembersNode(ForumMembersList*,ForumMembersNode*);
void deleteForumMembersNode(ForumMembersList*,ForumMembersNode*);
void destroyForumMembersList(ForumMembersList*);
NameForumNode* partitionForum(NameForumNode**,int,int,int);

void EditTopForumList(TopForumList*,int);
void addNewTopForumNode(TopForumList*,TopForumNode*);
void destroyTopForumList(TopForumList *);
void deleteTopForumNode(TopForumList*,TopForumNode*);
TopForumNode* createTopForumNode(NameForumNode*);
TopForumList* createTopForumList();

TopForumList* PreperationFunction(Graph*,int);
BronKerList* createBronKerList();
BronKerNode* createBronKerNode(int);
void deleteBronKerNode(BronKerList*,BronKerNode*);
void destroyBronKerList(BronKerList*);
void addNewBronKerNode(BronKerList*,BronKerNode*);
BronKerList* makeListCopy(BronKerList*);
void editBronKerList(BronKerList*,BronKerList*,List*);

Community* cliquePercolationMethod(int,Graph*,Graph*);
void BronKerbosch(Graph*,BronKerList*,BronKerList*,int,Graph*,HyperList*);
void editPList(BronKerList*,List*);
void deleteBronKerNode2(int,BronKerList*);

void insertHyperEdges(Node*,Graph*,int,HyperList*);
HyperList* createHyperList();
HyperNode* createHyperNode(Node*);
void addNewHyperNode(HyperList*,HyperNode*);
void deleteHyperNode(HyperList*,HyperNode*);
void destroyHyperList(HyperList*);
HyperNode* checkHyperList(HyperList*,int);

HyperList* copyNodeList(DList*);
Community* createCommunities();
CommunitiesInfo* createCommunitiesInfo();

void printBronList(BronKerList*,char*);
void addClique(BronKerList*,Graph*,HyperList*);

Cpm** computeCPMResults(Graph*,int*,TopForumList*);
HyperList* copyHyperList(DList*);
CliqueNode* createCliqueNode(int);
CliqueList* createCliqueList();
void addNewCliqueNode(CliqueList*,CliqueNode*);
void destroyCliqueList(CliqueList*);
void deleteCliqueNode(CliqueList*,CliqueNode*);

int compareIntegers(const void *, const void *);
void validateGNResults(Gn**);
intList* createIntList();
int* ConvertListToArray(intList*);
void editCommunityMembers(intList*,CliqueList*);
void deleteIntlist(intList*);
void deleteIntNode(intList*,intNode*);
void checkIntList(intList*,int);
int checkForumMembersList(ForumMembersList*,int);

EdgeList* createEdgeList();
EdgeNode* createEdgeNode(Node*,Node*,double);
void addNewEdgeNode(EdgeList*,EdgeNode*);
void findEdges(Graph*,EdgeList*);
Community* GirvanNewman(double,Graph*,EdgeList*);
double CalculateModularity(Graph*);
void addNewEdgeNode(EdgeList*,EdgeNode*);

void removeEdge(Node*,Node*,Graph*);
void deleteEdgeNode(EdgeList*,EdgeNode*);
int InSameCommunity(Node*,Node*,Graph*);
int AreNeighbors(Node*,Node*);

void validateCPMResults(Cpm**);
Gn** computeGNResults(Graph*,double,TopForumList*);
double edgeCentrality(EdgeNode*,Graph*);
void destroyCommunitiesInfo(CommunitiesInfo*);
double edgeCentralityBfs(Node*,EdgeNode*,Graph*);

void *threadFunction(void *);
void place(PoolList*,PoolNode*);
PoolNode* obtain(PoolList*);
void printTopNForums(TopForumList*);
PoolList* createPoolList();
PoolNode* createPoolNode(void*);
void addNewPoolNode(PoolList*,PoolNode*);
PoolNode* getPoolNode(PoolList *);
void createForumGraph(void*);
void free_memory(TopForumList*,Cpm **, Gn **);
Graph* createTempGraph();
void printGraph(Graph*);
int checkList(List*,int);
#endif /* GRAPHLIB_H_ */
