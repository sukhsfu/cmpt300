//
//  main.c
//  assignmen1
//
//  Created by Sukhwinder Singh on 2020-01-20.
//  Copyright © 2020 Sukhwinder Singh. All rights reserved.
//

#include <stdio.h>
#include "List.h"

int headptr=-1;           //ptr to number of LISTheads used
int nodeptr=-1;          //ptr to number of NODES used.

LIST* ListCreate(){   //A new empty list is created.
	if(headptr<MAXLISTHEAD-1)
	{
    headptr++;
    listhead[headptr].pointer=headptr;
    listhead[headptr].size=0; //initially set number of nodes in the list to 0;
    listhead[headptr].node_first=NULL;  //initally first node in the list is set as NULL
    listhead[headptr].node_current=NULL;
    listhead[headptr].node_last=NULL;
    listhead[headptr].beforelist=1;
    listhead[headptr].beyondlist=1;
    return &(listhead[headptr]);  //return pointer of new,empty LIST.
      }
      return NULL;
}


int ListCount(LIST* list){   //returns the number  of items stored in the list .
    return list->size;
}


void* ListFirst(LIST* list){  //return pointer to the firstnode in the list,make current.
    list->node_current=list->node_first;
    return list->node_first->item;
}

void* ListNext(LIST* list){
    //advances pointer to current node by 1;if the current nodepointer reached beyond the end of list,return NULL.
    if(list->node_current==list->node_last){
        list->beyondlist=1;
        return (list->node_current=NULL);
    }
    list->node_current=list->node_current->next;
    return (list->node_current->item);
    
}

void* ListPrev(LIST* list){
    //backs up pointer to the current node by 1, if current nodepointer reached before the start of the list,return NULL.
    if(list->node_current==list->node_first){
        list->beforelist=1;
        return (list->node_current=NULL);
    }
    list->node_current=list->node_current->prev;
    return list->node_current->item;
}

void* ListCurr(LIST* list){//returns pointer to the current node in the list.

    return list->node_current->item;
}


void* ListLast(LIST* list){  //return pointer to the lastnode in list and make it current.
    list->node_current=list->node_last;
    return list->node_last->item;
}

int ListAdd(LIST* list,void* item){//add new item "after" the  current item
    if(nodeptr<MAXNODE-1)
    {
            nodeptr++;
            node[nodeptr].item=item;
    if(list->size==0){
    node[nodeptr].prev=NULL;
    node[nodeptr].next=NULL;
    list->node_first=&(node[nodeptr]);
    list->node_last=&(node[nodeptr]);
    list->node_current=&(node[nodeptr]);
    list->beforelist=0;
    list->beyondlist=0;
    list->size++;
    return 0;
        }
    if(list->beforelist==1){//if the current before the start

        node[nodeptr].prev=NULL;
        node[nodeptr].next=list->node_first;
        list->node_first->prev=&(node[nodeptr]);
        list->node_first=&(node[nodeptr]);
        list->node_current=list->node_first;    //discussion  forum
        list->size++;
        list->beforelist=0;
        list->beyondlist=0;
        return  0;
    }
    else if(list->beyondlist==1){   //if the current after the end
   
        node[nodeptr].prev=list->node_last;
        node[nodeptr].next=NULL;
        list->node_last->next=&(node[nodeptr]);
        list->node_last=&(node[nodeptr]);
        list->node_current=list->node_last;   //discussion forum
        list->size++;
        list->beforelist=0;
        list->beyondlist=0;
        return 0;
    }
    else{

        node[nodeptr].prev=list->node_current;
        node[nodeptr].next=list->node_current->next;
      
        list->node_current->next=&(node[nodeptr]);
        if(list->node_current==list->node_last){
            list->node_last=&(node[nodeptr]);
        }
        list->beforelist=0;
        list->beyondlist=0;
        list->node_current=&(node[nodeptr]);
        list->size++;
        return 0;
    }
    }
    return -1;
}

int ListInsert(LIST* list,void* item){//add new item "before" the current item.
    if(nodeptr<MAXNODE-1)
    {
    nodeptr++;
    node[nodeptr].item=item;
         if(list->size==0){
            node[nodeptr].prev=NULL;
            node[nodeptr].next=NULL;
            list->node_first=&(node[nodeptr]);
            list->node_last=&(node[nodeptr]);
            list->node_current=&(node[nodeptr]);
            list->beforelist=0;
            list->beyondlist=0;
            list->size++;
            return 0;
        }
    if(list->beforelist==1){//if the current before the start
    
        node[nodeptr].prev=NULL;
        node[nodeptr].next=list->node_first;
        list->node_first->prev=&(node[nodeptr]);
        list->node_first=&(node[nodeptr]);
        list->node_current=list->node_first;    //discussion  forum
        list->beforelist=0;
        list->beyondlist=0;
        list->size++;
        return  0;
    }
    else if(list->beyondlist==1){   //if the current after the end

        node[nodeptr].prev=list->node_last;
        node[nodeptr].next=NULL;
        list->node_last->next=&(node[nodeptr]);
        list->node_last=&(node[nodeptr]);
        list->node_current=list->node_last;   //discussion forum
        list->beforelist=0;
        list->beyondlist=0;
        list->size++;
        return 0;
    }
    else{
        node[nodeptr].prev=list->node_current->prev;
        node[nodeptr].next=list->node_current;
        list->node_current->prev=&(node[nodeptr]);
        if(list->node_current==list->node_first){
            list->node_first=&(node[nodeptr]);
        }
        list->node_current=&(node[nodeptr]);
        list->beforelist=0;
        list->beyondlist=0;
        list->size++;
        return 0;
    }
 }
    
        return -1;
}


int ListAppend(LIST* list,void * item){   //add the new item to the "end" of the list.
    if(nodeptr<MAXNODE-1)
       {
       nodeptr++;
       node[nodeptr].item=item;
           if(list->size==0){
               node[nodeptr].prev=NULL;
               node[nodeptr].next=NULL;
               list->node_first=&(node[nodeptr]);
               list->node_last=&(node[nodeptr]);
               list->node_current=&(node[nodeptr]);
               list->beforelist=0;
               list->beyondlist=0;
               list->size++;
               return 0;
           }
           node[nodeptr].prev=list->node_last;
           node[nodeptr].next=NULL;
           list->node_last->next=&(node[nodeptr]);
           list->node_last=&(node[nodeptr]);
           list->node_current=&(node[nodeptr]);
           list->beforelist=0;
           list->beyondlist=0;
           list->size++;
           return 0;
       }
    return -1;
}


int ListPrepend(LIST* list,void *item){   //add the new item to the "start" of the list
    if(nodeptr<MAXNODE-1)
    {
        nodeptr++;
        node[nodeptr].item=item;
        if(list->size==0){
            node[nodeptr].prev=NULL;
            node[nodeptr].next=NULL;
            list->node_first=&(node[nodeptr]);
            list->node_last=&(node[nodeptr]);
            list->node_current=&(node[nodeptr]);
            list->beforelist=0;
            list->beyondlist=0;
            list->size++;
            return 0;
        }
        node[nodeptr].prev=NULL;
        node[nodeptr].next=list->node_first;
        list->node_first->prev=&(node[nodeptr]);
        list->node_first=&(node[nodeptr]);
        list->node_current=&(node[nodeptr]);
        list->beforelist=0;
        list->beyondlist=0;
        list->size++;
        return 0;
    }
    return -1;
}


void* ListRemove(LIST* list){//return current item,take it out of list, make next current.
    if(list->beforelist==1||list->beyondlist==1)
        return  NULL;
    void* item=list->node_current->item;
    NODE* a=list->node_current->prev;
    NODE* b=list->node_current->next;
    if(list->size==1){
        list->node_first=NULL;
        list->node_last=NULL;
        list->beforelist=1;
        list->beyondlist=1;
    }
    else if(list->node_current==list->node_first){
        b->prev=NULL;
        list->node_first=b;
        list->beforelist=0;
        list->beyondlist=0;
    }
    else if(list->node_current==list->node_last){

        a->next=NULL;
        list->beyondlist=1;
        list->node_last=a;
    }
    else {
        a->next=b;
        b->prev=a;
        list->beforelist=0;
        list->beyondlist=0;
    }
    list->node_current->item=node[nodeptr].item;
    list->node_current->prev=node[nodeptr].prev;
    list->node_current->next=node[nodeptr].next;
    list->node_current=b;
    list->size=list->size-1;
    nodeptr--;
    return item;
}


void ListConcat(LIST* list1,LIST* list2){  //add  list2  to the end of list1.delete list2
    
    list1->size+=list2->size;
    list1->node_last->next=list2->node_first;
    list2->node_first->prev=list1->node_last;
    list1->node_last=list2->node_last;
    int p=list2->pointer;
    listhead[p].node_first=listhead[headptr].node_first;
    listhead[p].node_current=listhead[headptr].node_current;
    listhead[p].node_last=listhead[headptr].node_last;
    listhead[p].size=listhead[headptr].size;
    listhead[p].beforelist=listhead[headptr].beforelist;
    listhead[p].beyondlist=listhead[headptr].beyondlist;
    headptr--;
   
}

void  ListFree(LIST* list,void (*itemfree)(void*)){//delete list, (*itemFree)(itemBeeFreed)
    NODE*  temp;
    while(list->node_first!=list->node_last){
        (*itemfree)(list->node_first->item);
        temp=list->node_first->next;
        list->node_first->item=node[nodeptr].item;
        list->node_first->prev=node[nodeptr].prev;
        list->node_first->next=node[nodeptr].next;
        nodeptr--;
        list->node_first=temp;
    }
     (*itemfree)(list->node_first->item);
     list->node_first->item=node[nodeptr].item;
     list->node_first->prev=node[nodeptr].prev;
     list->node_first->next=node[nodeptr].next;
    nodeptr--;
    int p=list->pointer;
    listhead[p].node_first=listhead[headptr].node_first;
    listhead[p].node_current=listhead[headptr].node_current;
    listhead[p].node_last=listhead[headptr].node_last;
    listhead[p].size=listhead[headptr].size;
    listhead[p].beforelist=listhead[headptr].beforelist;
    listhead[p].beyondlist=listhead[headptr].beyondlist;
    headptr--;
}
void* ListTrim(LIST* list){
    if(list->size==0){
        return NULL;
    }
    if(list->size==1){
        void*  item=list->node_last->item;
        list->node_first=NULL;
        list->node_current=NULL;
        list->node_last=NULL;
        list->size=0;
        list->beforelist=1;
        list->beyondlist=1;
        return item;

    }
    void*  item=list->node_last->item;
    NODE* temp=list->node_last->prev;
    list->node_last->item=node[nodeptr].item;
    list->node_last->prev=node[nodeptr].prev;
    list->node_last->next=node[nodeptr].next;
    nodeptr--;
    list->node_last=temp;
    list->node_current=list->node_last;
    list->size--;
    return  item;
}
void* ListSearch(LIST* list,int(*compartor)(void* ,void*),void* comparisonArg){
    int check=0;
    while(list->node_current!=list->node_last){
        check=(*compartor)(list->node_current->item,comparisonArg);
        if (check==1){
            return list->node_current;
        }
        list->node_current=list->node_current->next;
    }
    check=(*compartor)(list->node_current->item,comparisonArg);
    if (check==1){
        return list->node_current;
    }
    list->node_current=list->node_current->next;
    return  list->node_current;
}



