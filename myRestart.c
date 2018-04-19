#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <ucontext.h>
#include <sys/mman.h>
#include "Functions.h"
void restore();
void restoreFile();
void stack_unmap();
ucontext_t myContext;
char ckpt_image[100];
char startAddrmain[20];
char endAddrmain[20];
int stack_s;
int main(int argc, char* argv[])
{


	strcpy(ckpt_image, argv[1]);
    restore();
    void* stackAddr=(void *)0x5300000;
    void* stack_ptr=(void *)0x5301000;
    void* addr= mmap(stackAddr, 4096, PROT_EXEC|PROT_WRITE|PROT_READ, MAP_GROWSDOWN|MAP_PRIVATE|MAP_ANONYMOUS,-1, 0);

       if(addr==MAP_FAILED)
       {
           printf("Error in memory mapping");
           exit(1);
       }


   asm volatile("mov %0,%%rsp;" : : "g" (stack_ptr) : "memory");
   restoreFile();


}


//function to get the stack values. 
void restore()
{



int fd;
    char buffer[200]="";
    int i = 0;
    char *fileName="/proc/self/maps";



  if ((fd = open(fileName, O_RDONLY, 0)) != -1) { //if 1



        while (read(fd, &buffer[i], 1) > 0) {


              if (buffer[i] == '\n') {

              i=0;
              count++;

                char *startAddr;
                char *endAddr;
                int posofdash;
                int posofspace;
                char stackkeycontainer[200];
                char *keyword = "stack";

                if(strstr(buffer, keyword) != NULL) {

                    strcpy(stackkeycontainer,buffer);

                                    startAddr=strtok(buffer,"-");
                                    strcpy(startAddrmain,startAddr);
                                    posofdash = strlen(startAddr)+1;
                                    strcpy(buffer,stackkeycontainer);
                                    int len_line=strlen(buffer);
                                    strncpy(stackkeycontainer,buffer+posofdash,len_line);
                                    endAddr=strtok(stackkeycontainer," ");
                                    strcpy(endAddrmain,endAddr);
                                    break;

                }





                  continue;
              }




          i++;


      }

    }
    else
    {
      printf("THE FILE CANNOT BE OPENED OR DOESNOT EXIST\n");
      exit(0);
    }



close(fd);


}
//function to unmap the stack.
void stack_unmap(){

int stack_size=hexsubtraction(endAddrmain,startAddrmain) ;

long long hex= hex_to_deci(startAddrmain);

void *poi = (void *)hex;
munmap(poi, stack_size);




}


//function to restore file
void restoreFile()
{

stack_unmap();



// 1. Read count from myckpt
 int fd=open(ckpt_image,O_RDONLY,0600);
int count;
read(fd,&count,sizeof(int));




// 2. Read struct of MemRegion from myckpt
struct MemoryRegion memRgn;
for(int j=0;j<count;j++){
read(fd,&memRgn,sizeof(struct MemoryRegion));
       strcpy(memarr[j].startAddr,memRgn.startAddr);
       strcpy(memarr[j].endAddr,memRgn.endAddr);
       memarr[j].isReadable=memRgn.isReadable;
       memarr[j].size=memRgn.size;
}


// 3. Read the context
read(fd,&myContext,sizeof(ucontext_t));




//mmap the allocated space
 for(int c=0;c<count-1;c++){
       long long startAddinhexr=hex_to_deci(memarr[c].startAddr);
        void * addr1= mmap((void *)startAddinhexr, memarr[c].size, PROT_EXEC|PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS,-1, 0);
	if(addr1==MAP_FAILED)
       {
           exit(1);
       }

	}



// 4. copy all the Content of the momory to data.

for(int v=0;v<count-1;v++){

				if(memarr[v].isReadable){


				   long long starinhexa=hex_to_deci(memarr[v].startAddr);
					  int address =read(fd,(void *)starinhexa,memarr[v].size);

				}

}

//setting the context back.
setcontext(&myContext);

    exit(0);

}
