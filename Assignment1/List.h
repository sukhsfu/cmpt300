

#include <stdio.h>


#define MAXLISTHEAD 5
#define MAXNODE 10



typedef struct NODE_{
    void * item;
    struct NODE_ *prev;  //pointer to the node before this
    struct NODE_ *next;    //pointer to the node after this
}NODE;


typedef struct LIST_{
    NODE* node_first;  //pointer to the first node in the list.
    NODE* node_current;   //pointer to the current node in the list.
    NODE* node_last;  //pointer to the last node in the list.
    int size;       //stores the number of nodes in the list.
    int beforelist;    //1 if  the current pointer is before start of list, 0 otherwise;
    int beyondlist;   //1 if the current pointer is beyound end of list ,0 otherwise;
    int pointer;     //stores  the pointer to the  list.

}LIST;


LIST listhead[MAXLISTHEAD];
NODE node[MAXNODE];

LIST* ListCreate();//A new empty list is created.
int ListCount(LIST* ); //returns the number  of items stored in the list .
void* ListFirst(LIST*);  //return pointer to the firstnode in the list,make current.
void* ListNext(LIST*);//advances pointer to current node by 1;if the current nodepointer reached beyond the end of list,return NULL.
void* ListPrev(LIST*);//backs up pointer to the current node by 1, if current nodepointer reached before the start of the list,return NULL.
void* ListCurr(LIST*);//returns pointer to the current node in the list.
void* ListLast(LIST*); //return pointer to the lastnode in list and make it current.
int ListAdd(LIST*,void*);//add new item "after" the  current item
int ListInsert(LIST*,void*);//add new item "before" the current item.
int ListAppend(LIST*,void *);   //add the new item to the "end" of the list.
int ListPrepend(LIST*,void*);   //add the new item to the "start" of the list
void* ListRemove(LIST*);//return current item,take it out of list, make next current.
void ListConcat(LIST*,LIST*); //add  list2  to the end of list1.delete list2
void  ListFree(LIST*,void (*itemfree)(void*));//delete list, (*itemFree)(itemBeeFreed)
void* ListTrim(LIST*);
void* ListSearch(LIST* list,int(*compartor)(void* ,void*),void* comparisonArg);
