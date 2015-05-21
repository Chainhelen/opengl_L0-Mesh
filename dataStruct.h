#ifndef DATASTRUCT_H
#define DATASTRUCT_H
class IndexList{
    public:
        int data;
        IndexList *next;
};

template<class T>
void delList(T *Head){
    if(NULL == Head){
        return;
    }

    T *Node,*pNode;
    Node = Head->next;

    while(NULL != Node){
        pNode = Node->next;
        Head->next = pNode;

        delete Node;
        Node = pNode;
    }
    delete Head;

    Head = NULL;
    pNode = NULL;
    Node = NULL;

};
#endif
