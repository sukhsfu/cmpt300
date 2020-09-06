#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "List.h"
#include <pthread.h>
#include <netdb.h>

struct sockaddr_in myaddr,destaddr;
int portserver,portclient;
int a;
int pexit;


socklen_t addrlen;
//deleted char buffer

LIST* sk;
LIST* rp;

pthread_mutex_t mutexsk= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexrp= PTHREAD_MUTEX_INITIALIZER;

//function to send the data
void* sendserver(void* args){
    int check=*(int*)args;
    if(check==1){
        while(1){
            
            if(ListCount(sk)!=0){
                
        pthread_mutex_lock(&mutexsk);
        //
        ListFirst(sk);//
        sendto(a,(void*)ListRemove(sk),1024,0,(struct sockaddr *)&destaddr,sizeof(destaddr));
              if(pexit==1){
            exit(0);
        }
        pthread_mutex_unlock(&mutexsk);

        }


        }

    }
 
}
void* recieveserver(void* args){
    int check=*(int*)args;
    char buffer1[1024];
    if(check==1){
        while(1){

            
            if(ListCount(rp)==0){
                
        pthread_mutex_lock(&mutexrp);
        
      recvfrom(a,buffer1,1024,0,(struct sockaddr* )&destaddr,&addrlen);
      ListAppend(rp,buffer1);
       
            if(buffer1[0]=='!'){
          exit(0);
      }
       
           
      pthread_mutex_unlock(&mutexrp);

            }



        }
    }
    
}

void* printserver(void* args){
    int check=*(int*)args;
    char* buffer;
    if(check==1){
        while(1){

             if(ListCount(rp)!=0){
                 
        pthread_mutex_lock(&mutexrp);
         //
          ListFirst(rp);//
          buffer=(char*)ListRemove(rp);

         printf("%s\n",buffer);
          
        pthread_mutex_unlock(&mutexrp);

          }


        }

    }

}

void* keywordserver(void* args){
    int check=*(int*)args;
    char buffer[1024];
    if(check==1){
        while(1){
           
            if(ListCount(sk)==0){
              
        pthread_mutex_lock(&mutexsk);
        
        scanf("%[^\n]%*c",buffer);
        ListAppend(sk,buffer);
        

  
        pthread_mutex_unlock(&mutexsk);


            }
               if(buffer[0]=='!'){
           pexit=1;

        }
    }
    
}
}


int main(int argc, char **argv){
   
        if(argc!=5){
        printf("Incorrect number of arguements");
        exit(-1);
    }
    
    char* name= argv[1];
    char* namecheck;
    strcpy(namecheck,"s-talk");
    int check=strcmp(name,namecheck);
    if(check!=0){
        printf("do you mean: s-talk");
        exit(-1);
    }
       portserver = atoi(argv[2]);
   portclient =atoi(argv[4]);
/*
    char remote[1024];
    strcpy(remote,"csil-cpu1.cs.surrey.sfu.ca");
   
struct in_addr **addr_list;
   struct hostent* ht=gethostbyname(remote);
    addr_list = (struct in_addr **)ht->h_addr_list;
 */
   
   //section for reviever
   a=socket(AF_INET,SOCK_DGRAM,0);
   memset(&myaddr,'\0',sizeof(myaddr));
   myaddr.sin_family=AF_INET;
   myaddr.sin_port=htons(portserver);
   myaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   bind(a,(struct sockaddr*)&myaddr,sizeof(myaddr));
    
    
   // printf("%s",inet_ntoa(*addr_list[0]));
   
   //section for sender
   memset(&destaddr,'\0',sizeof(destaddr));
   destaddr.sin_family=AF_INET;
   destaddr.sin_port=htons(portclient);
   destaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  // destaddr.sin_addr.s_addr=inet_addr(inet_ntoa(*(struct in_addr*)ht->h_addr));
   
   
   addrlen=sizeof(destaddr);
   pthread_t sendthread,recievethread,printthread,keywordthread;
   int s,r,i,k;
   int check1=1;
   int check2=1;
   int check3=1;
   int check4=1;
   pexit=0;
   

   sk=ListCreate();
   rp=ListCreate();
 



   r=pthread_create(&recievethread,NULL,recieveserver,&check1);

   i=pthread_create(&printthread,NULL,printserver,&check2);
  
   s=pthread_create(&sendthread,NULL,sendserver,&check3);
   k=pthread_create(&keywordthread,NULL,keywordserver,&check4); 
   
   pthread_join(keywordthread,NULL);
 
   pthread_join(recievethread,NULL);
   pthread_join(printthread,NULL);
   pthread_join(sendthread,NULL);  
  
  
    
   
    return 0;
   

}






















