#include<stdio.h>
#include <unistd.h>
#include <ucontext.h>
#include<signal.h>
#include"Functions.h"


//constructor to load myconstructor before the main function of the user program.
void __attribute__ ((constructor)) myconstructor();

//function to handle the signal send by the user.
void signal_handle(int mysignal)
{

  ucontext_t myContext;
	int pid=getpid();
//setting the context.
  getcontext(&myContext);

    if(getpid()!=pid){
        return;
    }


     int fd;
    char buffer[200]="";
    int i = 0;

    char *fileName="/proc/self/maps";


    remove("memory");
    fdw=open("memory",O_CREAT|O_WRONLY,0600);

	if ((fd = open(fileName, O_RDONLY, 0)) != -1) {



			  while (read(fd, &buffer[i], 1) > 0) {


					    if (buffer[i] == '\n') {

							i=0;
              count++;

							finalMethod(buffer,0);


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





//clear the myckpt file.
	remove("myckpt");
    int fd1=open("myckpt",O_CREAT|O_WRONLY,0600);







		//1.  wrirting the count

	if( write(fd1,&count,sizeof(int))!= sizeof(int))
	{
		printf("could not write to file");
	}


// 2. Writing the Array of the Memory Reion.
	for(int i=0;i<count;i++){

		if(write(fd1,&memarr[i],sizeof(struct MemoryRegion))!=sizeof(struct MemoryRegion))
		{
			printf(" error while writing");
		}
	}


// 3. Writing the Context
	if(write(fd1,&myContext,sizeof(ucontext_t)) != sizeof(ucontext_t))
	{
		printf("error while saving the registers\n");
	}


// 4. Writing the Memoy Content
  for(int j=0;j<count-1;j++){

    	if(memarr[j].isReadable){

                long long startAddrinHex=hex_to_deci(memarr[j].startAddr);


        	      if(write(fd1,(void *)startAddrinHex,memarr[j].size)!=memarr[j].size){
        			printf("error while writing the memory content\n");
        			}

          }


      }



	close(fd1);

printf("MEMORY CAPTURED!!\n");


}

//signal sent by the user is SIGUSR2.
void myconstructor() {
  signal(SIGUSR2,signal_handle);
}
