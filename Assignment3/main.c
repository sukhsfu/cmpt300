#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define Maximumprocesses 40

int x;
int xmsg_array;

LIST* L0;
LIST* L1;
LIST* L2;
LIST* Lsend;
LIST* Lreceive;


typedef struct{
    int PID;
    char message[40];
}msgA;

msgA msg_array[40];

typedef struct {
    int PID;
    int priority;//,0,1,2,   3-for init
    int state;
    /* -1 blocked
     0-ready
     1-running
     3-for init.
     */
    char  message[40];
    
    
}PCB;
PCB A[Maximumprocesses];


typedef struct {
    int size;
    LIST* process_waiting;
}semaphore;

semaphore s[4];

int Create(int a){
    if(a==0){
        A[x].PID=x;
        A[x].priority=a;
        A[x].state=0;

        
        if (ListAppend(L0,&A[x])==0){
            ++x;
            printf("process created with PID:%d\n",(A[x-1].PID));
            return x-1;
        }
        else{
            return -1;
        }
        }
    
       else if(a==1){
                A[x].PID=x;
                A[x].priority=a;
                A[x].state=0;
                if (ListAppend(L1,&A[x])==0)
                {
                    ++x;
                    printf("process created with PID:%d\n",(A[x-1].PID));
                    return x-1;
                }
                else{
                    return -1;
                }
                }
    else if(a==2){
         A[x].PID=x;
         A[x].priority=a;
         A[x].state=0;
        if (ListAppend(L2,&A[x])==0){
            ++x;
            printf("process created with PID:%d\n",(A[x-1].PID));
             return x-1;
        }
        else{
             return -1;
        }
         }
    else{
        return -1;
    }
    
}
                   
 
                        
int comparePCB(void* a,void* b){
    PCB* A1=(PCB*)a;
    PCB* B1=(PCB*)b;
                    if (A1->PID==B1->PID){
                        return 1;
                    }
    return 0;
                }

int Kill(int a){
               int ch;
    for(ch=0;ch<=x;ch++){
        if(A[ch].PID==a)
            break;
    }
    
                    if(ch>=x){
                        return -1;
                    }
    if(ListCount(L0)==0&&ListCount(L1)==0&&ListCount(L2)==0&&
       ListCount(Lsend)==0&&ListCount(Lreceive)==0&&A[ch].PID==0){
        A[a].state=-1;
        return 0;
    }
                   int q= A[a].priority;
                   if(A[a].state==1){
                      A[a].PID=(x-1);
                      A[a].priority=A[x-1].priority;
                      A[a].state=A[x-1].state;
                      x--;
                       return 0;
                   }
    
                    
    
                    if (q==0){
                        
                        ListSearch(L0,&comparePCB,&A[a]);
                        ListRemove(L0);
                        if(ListCount(Lsend)!=0){
                        if (ListSearch(Lsend,&comparePCB,&A[a])!=NULL){
                            ListRemove(Lsend);
                        }
                        }
                        if(ListCount(Lreceive)!=0){
                        if (ListSearch(Lreceive,&comparePCB,&A[a])!=NULL){
                            ListRemove(Lreceive);
                        }
                        }
                        A[a].PID=(x-1);
                        A[a].priority=A[x-1].priority;
                        A[a].state=A[x-1].state;
                        x--;
                    }
                   else if (q==1){
                        ListSearch(L1,&comparePCB,&A[a]);
                        ListRemove(L1);
                        if(ListCount(Lsend)!=0){
                                               if (ListSearch(Lsend,&comparePCB,&A[a])!=NULL){
                                                   ListRemove(Lsend);
                                               }
                                               }
                                               if(ListCount(Lreceive)!=0){
                                               if (ListSearch(Lreceive,&comparePCB,&A[a])!=NULL){
                                                   ListRemove(Lreceive);
                                               }
                                               }
                        A[a].PID=(x-1);
                        A[a].priority=A[x-1].priority;
                        A[a].state=A[x-1].state;
                        x--;
                    }
                    else {
                        ListSearch(L2,&comparePCB,&A[a]);
                        ListRemove(L2);
                        
                        if(ListCount(Lsend)!=0){
                                               if (ListSearch(Lsend,&comparePCB,&A[a])!=NULL){
                                                   ListRemove(Lsend);
                                               }
                                               }
                                               if(ListCount(Lreceive)!=0){
                                               if (ListSearch(Lreceive,&comparePCB,&A[a])!=NULL){
                                                   ListRemove(Lreceive);
                                               }
                                               }
                        A[a].PID=(x-1);
                        A[a].priority=A[x-1].priority;
                        A[a].state=A[x-1].state;
                        x--;
                    }
                    return 0;
                    
                }
                        
int Exit(){
    int a;//get the process that is currently running.
    int pid;
    for (int i=0;i<=x;i++){
        if (A[i].state==1){
            a=i;
            break;
        }
    }
    pid=A[a].PID;
    if(ListCount(L0)==0&&ListCount(L1)==0&&ListCount(L2)==0&&
       ListCount(Lsend)==0&&ListCount(Lreceive)==0&&A[a].PID==0){
        A[a].state=-1;
        return 0;
    }
    if(A[a].PID==0){
        if(ListCount(L0)!=0||ListCount(L1)!=0||ListCount(L2)!=0||
           ListCount(Lsend)!=0||ListCount(Lreceive)!=0){
            return -1;
        }
    }
    A[a].PID=(x-1);
    A[a].priority=A[x-1].priority;
    A[a].state=A[x-1].state;
    --x;
  
    return 0;
}
  

int Fork(){
 for (int i=0;i<=x;i++){
     if (A[i].state==1){//process is running
         A[x].PID=x;
         A[x].priority=A[i].priority;
         A[x].state=0;
         if(A[i].priority==0){
             ListAdd(L0,&A[x]);
          }
         if(A[i].priority==1){
           ListAdd(L1,&A[x]);
         }
        if(A[i].priority==2){
         ListAdd(L2,&A[x]);
         }
         x++;
        return (A[x-1].PID);
     }
   }
  return -1;
}

int Quantum(){
    int i;//get the current process
    for(i=0;i<=x;i++){
        if (A[i].state==1)
            break;
    }
    if(A[i].PID==0){
        if(ListCount(L0)!=0||ListCount(L1)!=0||ListCount(L2)!=0||
           ListCount(Lsend)!=0||ListCount(Lreceive)!=0){
            return -1;
        }
    }
    A[i].state=0;
    int q=A[i].priority;
    if(q==0){
        ListAppend(L0,&A[i]);
    }
    if(q==1){
      ListAppend(L1,&A[i]);
    }
    if(q==2){
       ListAppend(L2,&A[i]);
    }

 
    
    return 0;
}

int send(int pid,char* msg){
    int i; //current running process
    for(i=0;i<=x;i++){
        if (A[i].state==1)
            break;
    }
   
    
    msg_array[xmsg_array].PID=pid;
  
    strncpy(msg_array[xmsg_array].message,msg,40);
    xmsg_array++;
    //v sem
    if(A[i].PID!=0){
    ListAppend(Lsend,&A[i]);
    A[i].state=-1;
    }
    int j;//process whose pid is PID
    for(j=0;j<=x;j++){
        if(A[j].PID==pid)
            break;
    }
    if(j>x){
        return -1;
    }
    int q=A[j].priority;
    PCB* check2;
    if(ListCount(Lreceive)==0){
        check2=NULL;
    }
    else{
    check2=(PCB*)ListSearch(Lreceive,&comparePCB,&A[j]);
    }
    if(check2!=NULL){
        ListRemove(Lreceive);
        if(q==0){
             ListAppend(L0,&A[j]);
         }
         if(q==1){
             ListAppend(L1,&A[j]);
         }
         if(q==2){
             ListAppend(L2,&A[j]);
         }
        
    }
    return 0;
    
}
void Procinfo(int pid){
    int i;  //get the prcoess whose pid is given
    for(i=0;i<=x;i++){
        if(A[i].PID==pid)
            break;
    }
    if(A[i].PID==0){
          printf("PID :%d  (init)\n",A[i].PID);
    }
    else{
    printf("PID :%d\n",A[i].PID);
    printf("priority queue :%d\n",A[i].priority);
    }
   
    if(A[i].state==-1)
        printf("state : blocked\n");
     if(A[i].state==0)
         printf("state : ready\n");
    if(A[i].state==1)
        printf("state : running\n");
    if(A[i].state==3)
        printf("state : running\n");
    if(A[i].state==4)
        printf("state : sleep\n");
    printf("message stored :%s\n",A[i].message);
}

int receive(){//two cases- message already there and message not there.
    int i;//get the process that is currently running.
    for(i=0;i<=x;i++){
        if (A[i].state==1)
            break;
    }
    int j;//to check if there is any message
    for(j=0;j<=xmsg_array;j++){
        if(msg_array[j].PID==A[i].PID)
            break;
    }
    if(j>xmsg_array&&A[i].PID!=0){//process gets blocked
        ListAppend(Lreceive,&A[i]);
        A[i].state=-1;
        return -1;
    }
    strncpy(A[i].message,msg_array[j].message,40);
    printf("message is: %s\n",A[i].message);
    msg_array[j].PID=msg_array[xmsg_array].PID;
    strncpy(msg_array[j].message,msg_array[xmsg_array].message,40);
    --xmsg_array;
    return 0;
    
    
}

int reply(int pid,char* msg){
    int i;//sender that was blocked
    for(i=0;i<=x;i++){
        if(A[i].PID==pid)
            break;
    }
       msg_array[xmsg_array].PID=pid;
      strncpy(msg_array[xmsg_array].message,msg,40);
      xmsg_array++;
    A[i].state=0;
    int q=A[i].priority;
    PCB* check=(PCB*)ListSearch(Lsend,&comparePCB,&A[i]);
    if(check!=NULL){
        ListRemove(Lsend);
    if(q==0){
        ListAppend(L0,&A[i]);
    }
    if(q==1){
        ListAppend(L1,&A[i]);
    }
    if(q==2){
        ListAppend(L2,&A[i]);
    }
        return 0;
    }
    return -1;
    
}



int New_Semaphore(int sid,int initial){
    if(sid>=0&&sid<=4){
        s[sid].size=initial;
        s[sid].process_waiting=ListCreate();
        return 0;
    }
    
    return -1;
    
}
int SemaphoreP(int sid){
    if(sid>=0&&sid<=4){
        s[sid].size++;
        int i;
        for(i=0;i<=x;i++){
            if (A[i].state==1)
                break;
        }
        if(s[sid].size!=1&&A[i].PID!=0){
            ListAppend(s[sid].process_waiting,&A[i]);
            A[i].state=-1;
            printf("process PID: %d got blocked on semaphore: %d\n",A[i].PID,sid);
        }
        
        return 0;
    }
    return -1;
    
}

int SemaphoreV(int sid){
    if(sid>=0&&sid<=4){
        s[sid].size--;
        if(ListCount(s[sid].process_waiting)==0)
            return 0;
        int pid=((PCB*) ListFirst(s[sid].process_waiting))->PID;
        ListRemove(s[sid].process_waiting);
        int i;
        for(i=0;i<=x;i++){
            if(A[i].PID==pid){
                break;
            }
        }
        int prior=A[i].priority;
        A[i].state=0;
        if(prior==0){
            ListAppend(L0,&A[i]);
        }
        if(prior==1){
            ListAppend(L1,&A[i]);
        }
        if(prior==2){
            ListAppend(L2,&A[i]);
        }
        printf("process PID: %d got readid on semaphore: %d\n",A[i].PID,sid);
        return 0;
    }
    return -1;
}



void Totalinfo(){
    int ii;
    for(ii=0;ii<=x;ii++){
        if(A[ii].state==1)
            break;
    }

    if(A[0].state==3){
        printf("running process: PID:0 (init)\n");
    }
    else{
    printf("running process: PID:%d\n",A[ii].PID);
    }
    printf("priority queue 0:  ");
    if(ListCount(L0)!=0){
        int pid;
        pid=((PCB *)ListFirst(L0))->PID;
        printf("PID:%d  ",pid);
        for(int j=0;j<(ListCount(L0)-1);j++){
            pid=((PCB*)ListNext(L0))->PID;
            printf("PID:%d  ",pid);
        }
       
    }
     printf("\n");
    printf("priority queue 1:  ");
    if(ListCount(L1)!=0){
        int pid;
        pid=((PCB *)ListFirst(L1))->PID;
        printf("PID:%d  ",pid);
        for(int j=0;j<(ListCount(L1)-1);j++){
            pid=((PCB*)ListNext(L1))->PID;
            printf("PID:%d  ",pid);
        }
        
    }
     printf("\n");
    printf("priority queue 2:  ");
    if(ListCount(L2)!=0){
        int pid;
        pid=((PCB *)ListFirst(L2))->PID;
        printf("PID:%d  ",pid);
        for(int j=0;j<(ListCount(L2)-1);j++){
            pid=((PCB*)ListNext(L2))->PID;
            printf("PID:%d  ",pid);
        }
        
    }
     printf("\n");
    printf("queue of blocked on send:  ");
    if(ListCount(Lsend)!=0){
        int pid;
        pid=((PCB *)ListFirst(Lsend))->PID;
        printf("PID:%d  ",pid);
        for(int j=0;j<(ListCount(Lsend)-1);j++){
            pid=((PCB*)ListNext(Lsend))->PID;
            printf("PID:%d  ",pid);
        }
        
    }
     printf("\n");
    printf("queue of blocked on receive:  ");
    if(ListCount(Lreceive)!=0){
        int pid;
        pid=((PCB *)ListFirst(Lreceive))->PID;
        printf("PID:%d  ",pid);
        for(int j=0;j<(ListCount(Lreceive)-1);j++){
            pid=((PCB*)ListNext(Lreceive))->PID;
            printf("PID:%d  ",pid);
        }
        
    }
     printf("\n");
}
void scheduler(){
    int n;
    for(n=0;n<=x;n++){
        if(A[n].state==1){
            A[0].state=4;
            return;
        }
    }
    if((ListCount(L0)!=0)){
        ListFirst(L0);
        int pid=((PCB*)ListRemove(L0))->PID;
        int i;
        for (i=0;i<=x;i++){
            if(A[i].PID==pid)
                break;
        }
        A[i].state=1;
        A[0].state=4;
    }
    else if((ListCount(L1)!=0)){
        ListFirst(L1);
        int pid=((PCB*) ListRemove(L1))->PID;
        int i;
        for (i=0;i<=x;i++){
            if(A[i].PID==pid)
                break;
        }
        A[i].state=1;
        A[0].state=4;
    }
    else if((ListCount(L2)!=0)){
        ListFirst(L2);
        int pid=((PCB*) ListRemove(L2))->PID;
        int i;
        for (i=0;i<=x;i++){
            if(A[i].PID==pid)
                break;
        }
        A[i].state=1;
        A[0].state=4;
    }
    else{
        A[0].state=3;
    }
}

int main(int argc,char const* argv[]){
    x=0;
    xmsg_array=0;
    L0= ListCreate();
    L1=ListCreate();
    L2=ListCreate();
    Lsend=ListCreate();
    Lreceive=ListCreate();
    char buffer[20];
    A[x].PID=0;
    A[x].priority=3;
    A[x].state=3;//3 for running and 4 for sleep (init)
    x++;

    int a;
    char c;
    while(1){
        scheduler();
       scanf("%[^\n]%*c",buffer);
        if(buffer[0]=='C'){
            printf("Enter the priority of process:0=high,1=normal,2=low\n");
            scanf("%[^\n]%*c",buffer);
            c=buffer[0];
            a=(int)c-48;
            
            int s=Create(a);
            if(s==-1){
            printf("process creation failed:%d\n",s);
            }
        }
        if(buffer[0]=='F'){
           int s= Fork();
            if(s==-1){
            printf("Fork failed: %d\n",s);
            }
            else{
                printf("new fork process with PID: %d\n",s);
            }
            
          }
            if(buffer[0]=='K'){
                printf("enter the PID of the process you want to kill\n");
                scanf("%[^\n]%*c",buffer);
                c =buffer[0];
                 a =(int)c-48;
                
               int s= Kill(a);
                if(s==0){
                    printf("process succesfully killed\n");
                }
                if(s==-1){
                    printf("failed to kill the process\n");
                }
              
                
        }
            if(buffer[0]=='E'){
             
                
                
               int s= Exit();
                if(s==0){
                    printf("successfully exited the current running process\n");
                }
                if(s==-1){
                    printf("cannot exit the current running process\n");
                }
                scheduler();
                Totalinfo();
                
            
                
        }
               if(buffer[0]=='Q'){
                      int s= Quantum();
                   if(s==-1){
                       printf("Quantum failed\n");
                   }
                   if(s==0){
                          printf("Quantum successful\n");
                   }
                   scheduler();
                   Totalinfo();
          }
            if(buffer[0]=='N'){
                printf("Enter the semaphore id from 0 to 4\n");
                scanf("%[^\n]%*c",buffer);
                 c =buffer[0];
                 a =(int)c-48;
                printf("enter the initial value.\n");
                scanf("%[^\n]%*c",buffer);
                char d;
                int t;
                d =buffer[0];
                t =(int)d-48;
                
               int s= New_Semaphore(a,t);
                if(s==0){
                    printf("semaphore initialization successful\n");
                }
                if(s==-1){
                    printf("sempahore initialization failed\n");
                }
               
                
        }
            if(buffer[0]=='P'){
             printf("Enter the semaphore id from 0 to 4\n");
                scanf("%[^\n]%*c",buffer);
                 c =buffer[0];
                 a =(int)c-48;
                
               int s= SemaphoreP(a);
                
                               if(s==0){
                   printf("semaphore P successful\n");
               }
               if(s==-1){
                   printf("sempahore P failed\n");
               }
                
        }
            if(buffer[0]=='V'){
             printf("Enter the semaphore id from 0 to 4\n");
                scanf("%[^\n]%*c",buffer);
                 c =buffer[0];
                 a =(int)c-48;//a is the id of the semaphore
                
               int s= SemaphoreV(a);
                                if(s==0){
                    printf("semaphore V successful\n");
                }
                if(s==-1){
                    printf("sempahore V failed\n");
                }
          
                
        }
            if(buffer[0]=='I'){
                printf("enter the PID\n");
                scanf("%[^\n]%*c",buffer);
                 c =buffer[0];
                 a =(int)c-48;
                Procinfo(a);
        }
           if(buffer[0]=='T'){
               Totalinfo();
                
        }
            if(buffer[0]=='S'){
                printf("Enter the PID of the process you want to send message.\n");
                scanf("%[^\n]%*c",buffer);
                 c =buffer[0];
                 a =(int)c-48;
                printf("enter the message\n");
                char getmessage[40];
                 scanf("%[^\n]%*c",getmessage);
                int s=send(a,getmessage);
                if(s==0){
                    printf("sending successful\n");
                    scheduler();
                    Totalinfo();
                }
                if(s==-1)
                printf("sending failed.\n");
        }
        if(buffer[0]=='R'){
            int s=receive();
            if(s==-1){
                printf("recieve failed\n");
            }
            if(s==0){
            printf("recieve successful\n");
                scheduler();
                Totalinfo();
            }
        }
        if(buffer[0]=='Y'){
            printf("Enter the process PID you want to reply\n");
            scanf("%[^\n]%*c",buffer);
             c =buffer[0];
             a =(int)c-48;
            printf("enter the message\n");
            char getmessage[40];
             scanf("%[^\n]%*c",getmessage);
            int s=reply(a,getmessage);
            if(s==0){
                printf("reply successful\n");
            }
            if(s==-1){
                printf("reply failed\n");
            }
                   
            }
        if(A[0].state==-1){
            printf("simulation terminated\n");
            exit(0);
        }
    
    }
}
