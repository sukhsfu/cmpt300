
#include "List.h"
int main(int argc, const char * argv[]) {
 LIST* A[MAXLISTHEAD+1]; //creates the pointer array of LIST;
 for(int i=0;i<=MAXLISTHEAD;i++){
    A[i]=ListCreate();      //create the new list for for each pointer                      //ListCreate() checked
 }

if(A[MAXLISTHEAD-1]==NULL){ //to check if i can make list till maxlisthead
	printf("cannot create list at MAXLISTHEAD");
}

if(A[MAXLISTHEAD]==NULL){   //to check if i can make list after maxlisthead                 //ListCreate() case 2 checked
	printf("cannot create list after  MAXLISTHEAD\n");
}
                 

    printf("Size of List Intially: %d\n",ListCount(A[0]));  //to check inital size of A[0]            //ListCount Checked
    char ch1='a';  //adding item 1 in A[0]
    char ch2='b';  //adding item 2 in A[1]
    char ch3='c';
    char ch4='d';
    char ch5='e';
    char ch6='f';
    printf("%d\n",ListAdd(A[0],&ch1));  //adding new item 'f' in A[0]                ListAdd checked
    printf("%d\n",ListAdd(A[0],&ch2));  //adding new item 'e' in A[0] 
    printf("%d\n",ListAdd(A[0],&ch3));  //adding new item in 'd' A[0] 
    printf("%d\n",ListAdd(A[0],&ch4));  //adding new item in  'a' A[0]           
    printf("%d\n",ListAdd(A[0],&ch5));  //adding new item in 'b' A[0] 
    printf("%d\n",ListAdd(A[0],&ch6));  //adding new item in  'c' A[0] 

    printf("Elements in the list are:\n");
    char t=*(char *)ListFirst(A[0]);                        //ListFirst   checked
    printf("%c\n",t);                   
      t=*(char *)ListNext(A[0]);                            //ListNext    checked
    printf("%c\n",t);
     t=*(char *)ListNext(A[0]);
    printf("%c\n",t);
      t=*(char *)ListNext(A[0]);
    printf("%c\n",t);
      t=*(char *)ListNext(A[0]);
    printf("%c\n",t);
      t=*(char *)ListNext(A[0]);
    printf("%c\n",t);

   printf("\n\nElements in the list in the reversed order\n");
   char r=*(char *)ListLast(A[0]);                              //ListLast checked
   printf("%c\n",r);
   r=*(char *)ListPrev(A[0]);                                   //Listprev checked
   printf("%c\n",r);
     r=*(char *)ListPrev(A[0]);
   printf("%c\n",r);
     r=*(char *)ListPrev(A[0]);
   printf("%c\n",r);
     r=*(char *)ListPrev(A[0]);
   printf("%c\n",r);
     r=*(char *)ListPrev(A[0]);
   printf("%c\n",r);

   char ch0='A';
   char ch7='F';

   printf("\n%d\n",ListPrepend(A[0],&ch0));               //ListPrepend checked
   printf("%d\n",ListAppend(A[0],&ch7));                 //ListAppend checked
   r=*(char *)ListCurr(A[0]);                              //ListCurr checked
   printf("New last element %c\n",r);
   r=*(char *)ListFirst(A[0]);
   printf("New First element %c\n",r);
   




   printf("Size of List at end: %d\n",ListCount(A[0]));  //printing new size

   int a=0;
   int b=1;
   int c=2;
   int d=3;
   int e=4;

   printf("\n%d",ListInsert(A[1],&e));       //ListInsert Checked
   printf("\n%d",ListInsert(A[1],&d));
   printf("\n%d",ListInsert(A[1],&c));
   printf("\n%d",ListInsert(A[1],&b));
   printf("\n%d",ListInsert(A[1],&e));
   printf("\n\nSize of the new list%d\n",ListCount(A[1]));   //nodes are recycled  checked.
           //this shows that the nodes that are removed during the ListRemove function are reused. 
   printf("%d\n",*(int*)(ListFirst(A[1])));
   printf("%d\n",*(int*)(ListNext(A[1])));
   ListConcat(A[1],A[0]);                                    //ListConcat Checked
   printf("Size of List at List 1 : %d\n",ListCount(A[0]));
   printf("Size of List at List 2 : %d\n",ListCount(A[1]));
    printf("%d\n",*(int*)(ListFirst(A[1])));
   printf("%d\n",*(int*)(ListNext(A[1])));
 

   printf("%c\n",*(char*)(ListLast(A[1])));
   printf("Elements of the  list Trimmed %c\n",*(char*)(ListTrim(A[1])));    //ListTrim Checked
   printf("Size of List at List 2 : %d\n",ListCount(A[1]));

   printf("Element Removed %c\n",*(char*)(ListRemove(A[1])));    //ListRemove checked

   printf("\n\nSize of the new list%d\n",ListCount(A[1])); 
   



}
