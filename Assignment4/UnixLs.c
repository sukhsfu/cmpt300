#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <stdint.h>


void getAndPrintGroup(gid_t grpNum) {  //information related to group.
  struct group *grp;         //group structure used.

  grp = getgrgid(grpNum); //getgrgid function used.
  
  if (grp) {
    printf("%-11s ",grp->gr_name);
  } else {
    printf("No group name for %u found\t", grpNum);
  }
}



void getAndPrintUserName(uid_t uid) {   //information related to users.

  struct passwd *pw = NULL;      //psswd structure used
  pw = getpwuid(uid);            //getpwuid function used.

  if (pw) {
    printf("%-11s ",pw->pw_name);
  } else {
    perror("Hmm not found???");
    printf("No name found for %u\t", uid);
  }
}

void modeconverter(mode_t mode){
    char p[11]="";
    strncat(p,(S_ISLNK(mode)) ? "l" : ((S_ISDIR(mode)) ? "d" : "-"),1);
    strncat(p,((mode & S_IRUSR) ? "r" : "-"),1);
    strncat(p,((mode & S_IWUSR) ? "w" : "-"),1);
    strncat(p,((mode & S_IXUSR) ? "x" : "-"),1);
    strncat(p,((mode & S_IRGRP) ? "r" : "-"),1);
    strncat(p,((mode & S_IWGRP) ? "w" : "-"),1);
    strncat(p,((mode & S_IXGRP) ? "x" : "-"),1);
    strncat(p,((mode & S_IROTH) ? "r" : "-"),1);
    strncat(p,((mode & S_IWOTH) ? "w" : "-"),1);
    strncat(p,((mode & S_IXOTH) ? "x" : "-"),1);
   
    printf("%-12s",p);
           
}
void printmonth(int a){
    char p[][4]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    printf("%-4s",p[a]);
}
int main(int argc,char **argv){
    if(argc<2){
        printf("Too few arguements\n");
        exit(0);
    }
    int xargc=argc;
        for(int i=3;i<argc;i++){
            if(strcmp(argv[2],"-i")==0){
                if(strcmp(argv[i],"-i")==0){
                    argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-l")==0){
                    argv[2]="-il";
                   argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-il")==0||strcmp(argv[i],"-li")==0){
                    argv[2]="-il";
                    argv[i]="xdr";
                    argc--;
                } }
            if(strcmp(argv[2],"-l")==0){
                if(strcmp(argv[i],"-i")==0){
                    argv[2]="-il";
                    argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-l")==0){
                    argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-il")==0||strcmp(argv[i],"-li")==0){
                    argv[2]="-il";
                    argv[i]="xdr";
                    argc--;
                } }
            if(strcmp(argv[2],"-il")==0||strcmp(argv[2],"-li")){
                if(strcmp(argv[i],"-i")==0){
                    argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-l")==0){
                    argv[i]="xdr";
                    argc--;
                }
                if(strcmp(argv[i],"-il")==0||strcmp(argv[i],"-li")==0){
                    argv[i]="xdr";
                    argc--;
                } }    }
            int cnt=3;
            for(int i=3;i<xargc;i++){
                if(strcmp(argv[i],"xdr")!=0){
                    argv[cnt]=argv[i];
                    cnt++;
                }
            }
    
    if(strcmp(argv[1],"ls")==0){
        int i=2;
    do{
        if(argc==2||((strcmp(argv[2],"-i")!=0)&&(strcmp(argv[2],"-l")!=0)&&(strcmp(argv[2],"-il")!=0)&&(strcmp(argv[2],"-li")!=0))){
            DIR* dirp;
            struct dirent *list;
            if(argc==2){
             dirp=opendir(".");
            }
            else{
                if(argc>3)
                    printf("%s:\n",argv[i]);
                dirp=opendir(argv[i]);
                if(dirp==NULL){
                    printf("ls: %s :No such file or directory.\n",argv[2]);
                    return (0);
                }
            }
            while((list=readdir(dirp))!=NULL){
                if(list->d_name[0]!='.')
                    printf("%s\n",list->d_name);
            }
         closedir(dirp);
       }
       else if(argc>=3){
           if(i==2)
               i++;
            if(strcmp(argv[2],"-i")==0){
                DIR* dirp;
                struct dirent *list;
                if(argc==3){
                 dirp=opendir(".");
                }
                else{
                    if(argc>4)
                        printf("%s:\n",argv[i]);
                    dirp=opendir(argv[i]);
                    if(dirp==NULL){
                        printf("ls: %s :No such file or directory.\n",argv[i]);
                        return (0);
                    }
                }
                while((list=readdir(dirp))!=NULL){
                    if(list->d_name[0]!='.'){
                    printf("%lu %s\n",list->d_fileno,list->d_name);
                    }
                }
                 closedir(dirp);
                
            }
            if(strcmp(argv[2],"-l")==0){
                DIR* dirp;
                struct dirent *list;
                struct stat buf;
                 if(argc==3){
                 dirp=opendir(".");
                }
                else{
                    if(argc>4)
                        printf("%s:\n",argv[i]);
                    dirp=opendir(argv[i]);
                    if(dirp==NULL){
                        printf("ls: %s :No such file or directory.\n",argv[i]);
                        return (0);
                    }
                }
                while((list=readdir(dirp))!=NULL){
                    if(list->d_name[0]!='.'){
                        char name[1024]="";
                        if(argc!=3){
                        strncat(name,argv[i],strlen(argv[i]));
                        char  slash='/';
                        strncat(name,&slash,1);
                        strncat(name,list->d_name,strlen(list->d_name));
                        }
                        else{
                            strncat(name,list->d_name,strlen(list->d_name));
                        }
                        if(lstat(name,&buf)<0){
                            break;
                        }
                        else{
                            struct tm* timeptr=localtime(&buf.st_mtime);
                            modeconverter(buf.st_mode);
                            printf("%5ld ",buf.st_nlink);
                            getAndPrintUserName(buf.st_uid);
                            getAndPrintGroup(buf.st_gid);
                            printf("%11ld ",buf.st_size);
                            printf("%2d ",timeptr->tm_mday);
                            printmonth(timeptr->tm_mon);
                            printf("%02d:%02d ",timeptr->tm_hour,timeptr->tm_min);
                            if(S_ISLNK(buf.st_mode)){
                                char buffer[1024];
                                ssize_t len=readlink(name,buffer,sizeof(buffer)-1);
                                buffer[len]='\0';
                                printf("%s -> %-11s\n",list->d_name,buffer);
                                      }
                                      else{
                            printf("%-11s\n",list->d_name);
                               }
                            
                        }
                    }
                }
            }
            //
            if((strcmp(argv[2],"-il")==0)||(strcmp(argv[2],"-li")==0)){
                DIR* dirp;
                struct dirent *list;
                struct stat buf;
                if(argc==3){
                 dirp=opendir(".");
                }
                else{
                    if(argc>4)
                        printf("%s:\n",argv[i]);
                    dirp=opendir(argv[i]);
                    if(dirp==NULL){
                        printf("ls: %s :No such file or directory.\n",argv[i]);
                        return (0);
                    }
                }
                while((list=readdir(dirp))!=NULL){
                    if(list->d_name[0]!='.'){
                        char name[1024]="";
                        if(argc!=3){
                        
                        strncat(name,argv[i],strlen(argv[i]));
                        char  slash='/';
                        strncat(name,&slash,1);
                        strncat(name,list->d_name,strlen(list->d_name));
                        }
                        else{
                            strncat(name,list->d_name,strlen(list->d_name));
                        }
                        if(lstat(name,&buf)<0){
                            break;
                        }
                        else{
                            struct tm* timeptr=localtime(&buf.st_mtime);
                            printf("%-11lu ",list->d_fileno);
                            modeconverter(buf.st_mode);
                            printf("%5ld ",buf.st_nlink);
                            getAndPrintUserName(buf.st_uid);
                            getAndPrintGroup(buf.st_gid);
                            printf("%11ld ",buf.st_size);
                            printf("%2d ",timeptr->tm_mday);
                            printmonth(timeptr->tm_mon);
                            printf("%02d:%02d ",timeptr->tm_hour,timeptr->tm_min);
                            if(S_ISLNK(buf.st_mode)){
                                char buffer[1024];
                                ssize_t len = readlink(name,buffer,sizeof(buffer)-1);
                                buffer[len] = '\0';
                                printf("%s -> %-11s\n",list->d_name,buffer);
                                      }
                                      else{
                            printf("%-11s\n",list->d_name);
                               }
                            
                        }
                    }
                }
            }
        }
        printf("\n");
        i++;
    }while(i<argc);
  }
    return 0;
}
