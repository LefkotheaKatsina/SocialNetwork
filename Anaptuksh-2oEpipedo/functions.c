#include "defines.h"

List* createList(){
    List* list = (List *)malloc( sizeof( List ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

TagList* createTagList(){
    TagList* list = (TagList *)malloc( sizeof( TagList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

CList* createCList(){
    CList* list = (CList *)malloc( sizeof( CList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

HList* createHList(){
    HList* list = (HList *)malloc( sizeof( HList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

DList* createDList(){
    DList* list = (DList *)malloc( sizeof( DList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

Matches* createMatches(){
    Matches* list = (Matches *)malloc( sizeof( Matches ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

InfoList* createInfoList(){
    InfoList* list = (InfoList *)malloc( sizeof( InfoList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

PointerPostInfoList* createPointerPostInfoList(){
    PointerPostInfoList* list = (PointerPostInfoList *)malloc( sizeof( PointerPostInfoList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

GenPostInfoList* createGenPostInfoList(){
    GenPostInfoList* list = (GenPostInfoList *)malloc(sizeof(GenPostInfoList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}


LikeList* createLikeList(){
    LikeList* list = (LikeList *)malloc(sizeof(LikeList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

ForumList* createForumList(){
    ForumList* list = (ForumList *)malloc(sizeof(ForumList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

StalkerList* createStalkerList(){
    StalkerList* list = (StalkerList *)malloc(sizeof(StalkerList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

WorkPlaceList* createWorkPlaceList(){
    WorkPlaceList* list = (WorkPlaceList *)malloc(sizeof(WorkPlaceList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

WorkPlaceNode* createWorkPlaceNode(int workplace){
    WorkPlaceNode* node = (WorkPlaceNode *)malloc( sizeof( WorkPlaceNode )); // Allocate memory for an DNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->workPlace = workplace;
    return node;
}

TagNode* createTagNode(int tag){
    TagNode* node = (TagNode *)malloc( sizeof( TagNode )); // Allocate memory for an DNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->tag = tag;
    return node;
}

NameForumNode* createNameForumNode(int forum,int person){
    NameForumNode* node = (NameForumNode*)malloc(sizeof(NameForumNode));
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->forumId = forum;
    node->personId = person;
    return node;
}

LNode* createLNode(int id,Edge* edge){
    LNode* lnode = (LNode *)malloc( sizeof( LNode ) ); // Allocate memory for an LNode
    if(lnode == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    lnode->next = lnode->prev = NULL;
    lnode->edge = edge;
    lnode->edge->endNodeID = id;
    lnode->edge->propEdge = edge->propEdge;
    return lnode;
}

CNode* createCNode(Node* node,int dist){
    CNode* cnode = (CNode *)malloc( sizeof( CNode ) ); // Allocate memory for an CNode
    if(cnode == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    cnode->next = cnode->prev = NULL;
    cnode->node = node;
    cnode->bridges = 0;
    cnode->dist = dist;
    cnode->paths = 0;
    return cnode;
}

DNode* createDNode(Node* node,int dist){
    DNode* dnode = (DNode *)malloc( sizeof( DNode )); // Allocate memory for an DNode
    if(dnode == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    dnode->next = dnode->prev = NULL;
    dnode->node = node;
    dnode->dist = dist;
    return dnode;
}

HNode* createHNode(int neighbors){
    HNode* hnode = (HNode *)malloc( sizeof( HNode ) ); // Allocate memory for an LNode
    if(hnode == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    hnode->next = hnode->prev = NULL;
    hnode->vertices = 1;
    hnode->neighbors = neighbors;
    return hnode;
}

InfoNode* createInfoNode(int id,int livePlace){
    InfoNode* node = (InfoNode *)malloc( sizeof( InfoNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->id = id;
    node->livePlace = livePlace;
    node->studyPlace = -1;
    node->workPlace = createWorkPlaceList();
    return node;
}

ForumNode* createForumNode(int forum){
    ForumNode* node = (ForumNode *)malloc( sizeof( ForumNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->forum = forum;
    return node;
}


MatchNode* createMatchNode(int id,double similarityScore){
    MatchNode* node = (MatchNode *)malloc( sizeof( MatchNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->id = id;
    node->similarityScore = similarityScore;
    return node;
}

PostInfoNode* createPostInfoNode(int postId,int personId){
    PostInfoNode* node = (PostInfoNode *)malloc( sizeof( PostInfoNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->post = postId;
    node->creator = personId;
    node->forum = -1;
    return node;
}

PointerPostInfoNode* createPointerPostInfoNode(PostInfoNode* postInfoNode){
    PointerPostInfoNode* node = (PointerPostInfoNode *)malloc( sizeof( PointerPostInfoNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->postInfoNode = postInfoNode;
    return node;
}

CommentNode* createCommentNode(int id,PointerPostInfoNode* pointerPostInfoNode){
    CommentNode* node = (CommentNode *)malloc( sizeof( CommentNode ) ); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->pointerPostInfoNode = pointerPostInfoNode;
    node->commentId = id;
    return node;
}

GenPostInfoNode* createGenPostInfoNode(int id){
    GenPostInfoNode* node = (GenPostInfoNode *)malloc(sizeof(GenPostInfoNode )); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->id = id;
    node->likePostList = createPointerPostInfoList();
    node->replyPostList = createPointerPostInfoList();
    return node;
}

LikeNode* createLikeNode(int creator){
    LikeNode* node = (LikeNode *)malloc(sizeof(LikeNode )); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->creator = creator;
    node->likes = 0;
    return node;
}

StalkerNode* createStalkerNode(Node* node,float centralityScore,int likes){
    StalkerNode* stalkerNode = (StalkerNode *)malloc(sizeof(StalkerNode )); // Allocate memory for an LNode
    if(stalkerNode == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    stalkerNode->next = stalkerNode->prev = NULL;
    stalkerNode->node = node;
    stalkerNode->centralityScore = centralityScore;
    stalkerNode->stalkerScore = likes;
    stalkerNode->forumList = createForumList();
    return stalkerNode;
}


NameInterestNode* createNameInterestNode(int id,char* name){
    NameInterestNode* node = (NameInterestNode *)malloc(sizeof(NameInterestNode )); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->InterestId = id;
    node->name = malloc(strlen(name)+1);
    strcpy(node->name,name);
    return node;
}

void addNewWorkPlaceNode(WorkPlaceList* list,WorkPlaceNode* node){
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

void addNewGenPostInfoNode(GenPostInfoList* list,GenPostInfoNode* node){
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

void addNewForumNode(ForumList* list,ForumNode* node){
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

void addNewCNode(CList* list,CNode* node){ //add a new LNode to list
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

void addNewDNode(DList* list,DNode* node){ //add a new DNode to Dlist
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

void addNewHNode(HList* list,HNode* node){ //add a new DNode to Dlist
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


void addNewTagNode(TagList* list,TagNode* node){ //add a new DNode to Dlist
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

void addNewInfoNode(InfoList* list,InfoNode* node){
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

void addNewLikeNode(LikeList* list,LikeNode* node){
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

void addNewPointerPostInfoNode(PointerPostInfoList* list,PointerPostInfoNode* node){
    if (list->head == NULL)// If list is empty, change both head and tail pointers
        list->tail = list->head = node;
    else  // Else change the tail
    {
        list->tail->next = node;
        list->tail = node;
    }
    list->_size++;
}

void addNewStalkerNode(StalkerList* list,StalkerNode* node, int limit){
    StalkerNode* temp;

    if(list->head == NULL)
        list->tail = list->head = node;
    else{
        temp = list->head;
        while(temp!=NULL){
            if(node->centralityScore >= temp->centralityScore){
                if(temp->prev){
                    temp->prev->next = node;
                    node->prev = temp->prev;
                }
                else
                    list->head = node;
                temp->prev = node;
                node->next = temp;
                list->_size++;
                return;
            }
            temp = temp->next;
        }
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->_size++;
    return;
}

void EditStalkersList(StalkerList* stalkerList,int topStalkers){
    StalkerNode* tempNode,*NodeToDelete;
    int tempStalkerScore;

    tempNode = stalkerList->head;
    while(topStalkers!=0 && tempNode!=NULL){
        tempNode = tempNode->next;
        topStalkers--;
    }
    if(tempNode==NULL)
        return;
    tempStalkerScore = tempNode->stalkerScore;

    while(tempNode!=NULL){
        NodeToDelete = tempNode;
        tempNode = tempNode->next;
        deleteStalkerNode(stalkerList,NodeToDelete);
    }
    tempNode = stalkerList->head;
    while(tempNode!=NULL){
        if(tempNode->stalkerScore == tempStalkerScore){
            NodeToDelete = tempNode;
            tempNode = tempNode->next;
            deleteStalkerNode(stalkerList,NodeToDelete);
        }
        else
            tempNode = tempNode->next;
    }
}

void InsertToMatches(Matches * list , MatchNode* node,int limit){
    MatchNode* temp;
    int flag = 0;

    temp = list->head;
    if(limit == 0)
        return;
    if(list->head == NULL)
        list->tail = list->head = node;
    else{
        while(temp!=NULL){
            if(node->similarityScore >= temp->similarityScore){
                if(temp == list->head){
                    temp->prev = node;
                    node->next = temp;
                    list->head = node;
                    flag = 1;
                    break;
                }
                else{
                    temp->prev->next = node;
                    node->prev = temp->prev;
                    temp->prev = node;
                    node->next = temp;
                    flag = 1;
                    break;
                }
            }
            temp = temp->next;
        }
        if(flag == 0){
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
    }
    list->_size++;
    if(list->_size > limit){
        temp = list->tail->prev;
        temp->next = NULL;
        free(list->tail);
        list->tail = temp;
    }
}

void deleteLNode(List* list,LNode* node,int flag){ //delete a node from list
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
        if(flag == 1){
            free((char*)(node->edge->propEdge[0].property));
            free((int*)(node->edge->propEdge[1].property));
        }
        else
            free((double*)(node->edge->propEdge[0].property));
        free(node->edge->propEdge);
        free(node->edge);
    }
    free(node);
    list->_size--;
}

void deleteCNode(CList* list,CNode* node){ //delete a Dnode from list
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

void deleteWorkPlaceNode(WorkPlaceList* list,WorkPlaceNode* node){
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

void deleteHNode(HList* list,HNode* node){ //delete a Dnode from list
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

void deleteTagNode(TagList* list,TagNode* node){ //delete a Dnode from list
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

void deleteInfoNode(InfoList* list,InfoNode* node){ //delete a Infonode from list
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
    destroyWorkPlaceList(node->workPlace);
    free(node);
    list->_size--;
}

void deleteMatchNode(Matches* list ,MatchNode* node){
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

void deleteGenPostInfoNode(GenPostInfoList* list,GenPostInfoNode* node){
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

void deleteStalkerNode(StalkerList* list,StalkerNode* node){
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
    destroyForumList(node->forumList);
    free(node);
    list->_size--;
}

void deleteLikeNode(LikeList* list,LikeNode* node){
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

void deleteForumNode(ForumList* list,ForumNode* node){
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

void destroyWorkPlaceList(WorkPlaceList* list){
    WorkPlaceNode* node = list->head;
    WorkPlaceNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteWorkPlaceNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyForumList(ForumList* list){
    ForumNode* node = list->head;
    ForumNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteForumNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyStalkerList(StalkerList* list){
    StalkerNode* node = list->head;
    StalkerNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteStalkerNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyList(List *list,int flag){
    LNode* node = list->head;
    LNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteLNode(list,node,flag);
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

void destroyHList(HList *list){
    HNode* node = list->head;
    HNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteHNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyCList(CList *list){
    CNode* node = list->head;
    CNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteCNode(list,node);
        node = temp;
    }
    free(list);
}


void destroyTagList(TagList *list){
    TagNode* node,*temp;
    if(list == NULL)
        return;
    node = list->head;
    while (node != NULL){
        temp = node->next;
        deleteTagNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyInfoList(InfoList *list){
    InfoNode* node = list->head;
    InfoNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteInfoNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyMatches(Matches *list){
    MatchNode* node = list->head;
    MatchNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteMatchNode(list,node);
        node = temp;
    }
    free(list);
}

void destroylikePostList(PointerPostInfoList* list){
    PointerPostInfoNode* node = list->head;
    PointerPostInfoNode* temp;
    while (node != NULL){
        temp = node->next;
        free(node);
        node = temp;
    }
    free(list);
}

void destroyGenPostInfoList(GenPostInfoList* list){
    GenPostInfoNode* node = list->head;
    GenPostInfoNode* temp;
    while (node != NULL){
        temp = node->next;
        destroylikePostList(node->likePostList);
        destroylikePostList(node->replyPostList);
        deleteGenPostInfoNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyLikeList(LikeList* list){
    LikeNode* node = list->head;
    LikeNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteLikeNode(list,node);
        node = temp;
    }
    free(list);
}

CreatorList* createCreatorList(){
    CreatorList* list = (CreatorList *)malloc( sizeof( CreatorList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

CreatorNode* createCreatorNode(int creator){
    CreatorNode* node = (CreatorNode*)malloc(sizeof(CreatorNode));
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->creator = creator;
    return node;
}

void addNewCreatorNode(CreatorList* list,CreatorNode* node){
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

void deleteCreatorNode(CreatorList* list,CreatorNode* node){
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

void destroyCreatorList(CreatorList* list){
    CreatorNode* node = list->head;
    CreatorNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteCreatorNode(list,node);
        node = temp;
    }
    free(list);
}

void destroyTrends(char** Trends,int size){
    int i;
    for(i=0;i<size;i++)
        free(Trends[i]);
    free(Trends);
}

int checkWorkPlaceList(InfoNode* node,WorkPlaceList * list){
    WorkPlaceNode* temp1,*temp2;
    temp1 = list->head;
    temp2 = node->workPlace->head;
    while(temp2!=NULL){
            while(temp1!=NULL){
                if(temp1->workPlace == temp2->workPlace)
                    return temp1->workPlace;
                temp1 = temp1->next;
            }
            temp2 = temp2->next;
            temp1 = list->head;
    }
    return -1;
}

int checkTagList(TagList* list,int tag){ //check list for a particular id
    TagNode* temp = list->head;

    while (temp != NULL){
        if(temp->tag == tag){
            return 1;
        }
        temp = temp->next;
    }
    return 0; //return node that holds id,NULL if id hasn't been found in list
}

DNode* check(DList* list,int id){ //check list for a particular id
    DNode* temp = list->head;
    DNode* node = NULL;

    while (temp != NULL){
        if(temp->node->id == id){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list
}

CNode* checkCList(CList* list,int id){ //check list for a particular id
    CNode* temp = list->head;
    CNode* node = NULL;

    while (temp != NULL){
        if(temp->node->id == id){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list
}

HNode* checkHList(HList* hashlist,int neighbors){

    HNode* temp = hashlist->head;
    HNode* node = NULL;
    while (temp != NULL){
        if(temp->neighbors == neighbors){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list

}

InfoNode* checkInfoList(InfoList* list,int id){
    InfoNode* temp = list->head;
    InfoNode* node = NULL;
    while (temp != NULL){
        if(temp->id == id){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list
}

int checkList(List* list,int id){
    LNode* temp = list->head;
    while (temp != NULL){
        if(temp->edge->endNodeID == id){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

ForumNode* checkForumList(ForumList* list,int forum){ //check list for a particular id
    ForumNode* temp,*node;

    temp = list->head;
    node = NULL;
    while (temp != NULL){
        if(temp->forum == forum){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node; //return node that holds id,NULL if id hasn't been found in list
}

LikeNode* checkLikeList(LikeList* list,int creator){
    LikeNode* temp = list->head;
    LikeNode* node = NULL;
    while (temp != NULL){
        if(temp->creator == creator){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node;
}

StalkerNode* checkStalkerList(StalkerList* list,int id){
    StalkerNode* temp = list->head;
    StalkerNode* stalkerNode = NULL;
    while (temp != NULL){
        if(temp->node->id == id){
            stalkerNode = temp;
            break;
        }
        temp = temp->next;
    }
    return stalkerNode;
}

GenPostInfoNode* checkGenPostInfoNode(GenPostInfoList* list,int id){
    GenPostInfoNode* temp = list->head;
    GenPostInfoNode* node = NULL;
    while (temp != NULL){
        if(temp->id == id){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node;
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

CNode* partition2(CNode** array,int low,int high,int id){ //rearch array for a given id

    int mid;
    CNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->node->id == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->node->id == id)
            return  array[mid];
        if(array[mid]->node->id > id)
            node = partition2(array,low,mid,id); //next search the left part of array
        else
            node = partition2(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

DNode* partition3(DNode** array,int low,int high,int id){ //rearch array for a given id

    int mid;
    DNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->node->id == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->node->id == id)
            return  array[mid];
        if(array[mid]->node->id > id)
            node = partition3(array,low,mid,id); //next search the left part of array
        else
            node = partition3(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

PostInfoNode* partition4(PostInfoNode** array,int low,int high,int id){ //rearch array for a given id
    int mid;
    PostInfoNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->post == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->post == id)
            return  array[mid];
        if(array[mid]->post > id)
            node = partition4(array,low,mid,id); //next search the left part of array
        else
            node = partition4(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

NameInterestNode* partition5(NameInterestNode** array,int low,int high,int id){ //rearch array for a given id
    int mid;
    NameInterestNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->InterestId == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->InterestId == id)
            return  array[mid];
        if(array[mid]->InterestId > id)
            node = partition5(array,low,mid,id); //next search the left part of array
        else
            node = partition5(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

CommentNode* partition6(CommentNode** array,int low,int high,int id){
    int mid;
    CommentNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->commentId == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->commentId == id)
            return  array[mid];
        if(array[mid]->commentId > id)
            node = partition6(array,low,mid,id); //next search the left part of array
        else
            node = partition6(array,mid+1,high,id); //next search the right part of array
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

int findPosition2(CNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->node->id > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->node->id > id)
            value = findPosition2(array,low,mid,id);//next search the left part of array
        else
            value = findPosition2(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

int findPosition3(DNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->node->id > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->node->id > id)
            value = findPosition3(array,low,mid,id);//next search the left part of array
        else
            value = findPosition3(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

int findPosition4(PostInfoNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->post > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->post > id)
            value = findPosition4(array,low,mid,id);//next search the left part of array
        else
            value = findPosition4(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

int findPosition5(NameInterestNode ** array,int low,int high,int id){
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->InterestId > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->InterestId > id)
            value = findPosition5(array,low,mid,id);//next search the left part of array
        else
            value = findPosition5(array,mid+1,high,id);//next search the right part of array
    }
    return value;
}

int findPosition6(NameForumNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->forumId > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->forumId > id)
            value = findPosition6(array,low,mid,id);//next search the left part of array
        else
            value = findPosition6(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

int findPosition7(CommentNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->commentId > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->commentId > id)
            value = findPosition7(array,low,mid,id);//next search the left part of array
        else
            value = findPosition7(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

InterestList* createInterestList(){
    InterestList* list = (InterestList *)malloc(sizeof(InterestList));
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

InterestNode* createInterestNode(int tag){
    InterestNode* node = (InterestNode *)malloc( sizeof( InterestNode ));
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->interest = tag;
    node->interestGraph = createGraph(2,3);
    return node;
}

void addNewInterestNode(InterestList* list,InterestNode* node){
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

void destroyInterestList(InterestList* list){
    InterestNode* node = list->head;
    InterestNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteInterestNode(list,node);
        node = temp;
    }
    free(list);
}

void deleteInterestNode(InterestList* list,InterestNode* node){
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
    destroyGraph(node->interestGraph,1);  //diagrafei ta tag tou ARXIKOU
    free(node);
    list->_size--;

}

InterestNode* checkInterestList(InterestList* list,int tag){
    InterestNode* temp = list->head;
    InterestNode* node = NULL;

    while (temp != NULL){
        if(temp->interest == tag){
            node = temp;
            break;
        }
        temp = temp->next;
    }
    return node;
}


TempList* createTempList(){
    TempList* list = (TempList *)malloc(sizeof(TempList));
    list->head = NULL;
    list->_size = 0;
    return list;
}

TempNode* createTempNode(int interest,int interestSize){
    TempNode* node = (TempNode *)malloc( sizeof( TempNode ));
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->interest = interest;
    node->interestSize = interestSize;
    return node;
}

void addNewTempNode(TempList* list,TempNode* node){
    TempNode* temp;

    if(list->head == NULL)//if list is empty
        list->tail = list->head = node;
    else{
        temp = list->head;
        while(temp!=NULL){
            if(node->interestSize >= temp->interestSize){
                if(temp->prev){
                    temp->prev->next = node;
                    node->prev = temp->prev;
                }
                else
                    list->head = node;
                temp->prev = node;
                node->next = temp;
                list->_size++;
                return;
            }
            temp = temp->next;
        }
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->_size++;
    return;
}

void destroyTempList(TempList* list){
    TempNode* node = list->head;
    TempNode* temp;
    while (node != NULL){
        temp = node->next;
        deleteTempNode(list,node);
        node = temp;
    }
    free(list);
}

void deleteTempNode(TempList* list,TempNode* node){
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

TrustList* createTrustList(){
    TrustList* list = (TrustList *)malloc( sizeof( TrustList ) );
    if(list == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->_size = 0;
    return list;
}

TrustNode* createTrustNode(Node* trustNode,int dist,double trust){
    TrustNode* node = (TrustNode *)malloc(sizeof(TrustNode )); // Allocate memory for an LNode
    if(node == NULL){
        printf("Cannot allocate memory");
        exit(1);
    }
    node->next = node->prev = NULL;
    node->dist = dist;
    node->trust = trust;
    node->node = trustNode;
    return node;
}

void addNewTrustNode(TrustList* list,TrustNode* node){
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

void destroyTrustList(TrustList* list){
    TrustNode* node = list->head;
    TrustNode* temp;

    while (node != NULL){
        temp = node->next;
        deleteTrustNode(list,node);
        node = temp;
    }
    free(list);
}

void deleteTrustNode(TrustList* list,TrustNode* node){
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

TrustNode* lookupNode7(int id, HashStructTrust* hashStruct) {
    int bucket;
    TrustNode* node;

    bucket = hashFunction(id,hashStruct->round,hashStruct->Init_HT_Size);
    if(bucket < hashStruct->pointer)
        bucket = hashFunction(id,(hashStruct->round)+1,hashStruct->Init_HT_Size);
    node = partition7(hashStruct->HashTable[bucket]->BucketTable,0,hashStruct->HashTable[bucket]->records-1,id);
    return node;
}

int findPosition8(TrustNode** array,int low,int high,int id){ //find position that node with given id should be placed
    int mid;
    int value;
    if (low > high)
        return 0;
    if (low == high){
        if (array[low]->node->id > id)
            return low;
        else
            return low+1;
    }
    if (low < high ){
        mid = (low+high)/2;
        if (array[mid]->node->id > id)
            value = findPosition8(array,low,mid,id);//next search the left part of array
        else
            value = findPosition8(array,mid+1,high,id);//next search the right part of array
    }
    return value;

}

TrustNode* partition7(TrustNode** array,int low,int high,int id){
    int mid;
    TrustNode* node;
    if (low > high) //if array is empty
        return NULL; //return NULL
    if (low == high){
        if (array[low]->node->id == id) //if id has been found
            return array[low]; //return position
        else //if id hasn't been found
            return NULL; //return NULL
    }
    if (low < high){
        mid = (low+high)/2;
        if(array[mid]->node->id == id)
            return  array[mid];
        if(array[mid]->node->id > id)
            node = partition7(array,low,mid,id); //next search the left part of array
        else
            node = partition7(array,mid+1,high,id); //next search the right part of array
    }
    return node;
}

