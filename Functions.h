#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "MemoryRegion.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>

long long hex_to_deci( char *);
long long getnumber(char);
int countofchar(char [],char);
int convertalphabets(char );
char convertnum(int );
int hexsubtraction(char[],char[] );
void finalMethod(char[],int);
//void lala(char[],char[],char[]);
int fdw;

static int sizereadonlymem=0;
static int sizereadwritemem=0;



int count=0;
struct MemoryRegion memarr[5000];
int countarr=0;




void finalMethod(char mem[],int prg)
{

		char buffer1[5000]="";
		int numberofspaces1=0;
		char me[1000]="";
		char pe[1000]="";
		int posofdash1=0;

		for(int i=0;i<strlen(mem);i++){
		if(mem[i] != ' ')
		{

			numberofspaces1++;


		}
		if(mem[i]==' ')
		{
			break;
		}


	}


		strncpy(me,mem,numberofspaces1);
		me[numberofspaces1]='\0';
		strcpy(pe,(mem+numberofspaces1)+1);
		pe[4]='\0';

	for(int i=0;i<strlen(me);i++){
		if(me[i] != '-')
		{

			posofdash1++;
int countarr=0;


		}
		if(me[i]=='-')
		{
			break;
		}


	}
		char startmemory1[100]="";
		char endmemory1[100]="";
		strncpy(startmemory1,me,posofdash1);
		startmemory1[posofdash1]='\0';


		strcpy(endmemory1,me+posofdash1+1);


		//struct MemoryRegion memrn;

		//printf("%d\n",countarr);
		strcpy(memarr[countarr].startAddr,startmemory1);
		strcpy(memarr[countarr].endAddr,endmemory1);
		if(pe[0]=='r'){
			memarr[countarr].isReadable=1;
		}
		else
		{
			memarr[countarr].isReadable=0;
		}
		if(pe[1]=='w'){
			memarr[countarr].isWriteable=1;
		}
		else
		{
			memarr[countarr].isWriteable=0;
		}
		if(pe[2]=='x'){
			memarr[countarr].isExecutabl=1;
		}
		else
		{
			memarr[countarr].isExecutabl=0;
		}
			memarr[countarr].size=hexsubtraction(endmemory1,startmemory1);


			/*long long hexnumber=hex_to_deci(memarr[countarr].startAddr);
            printf("************* %llx 8888888   %d \n",hexnumber,memarr[countarr].size );
                 if(memarr[countarr].isReadable){
                         char *po=(char *)hexnumber;
						 memcpy (&memarr[countarr].memorydatacontent,po,memarr[countarr].size);
					 }*/

					 if(prg==0){

			 			strcat(buffer1,memarr[countarr].startAddr);
			 			strcat(buffer1,"-");
			 			strcat(buffer1,memarr[countarr].endAddr);
			 			strcat(buffer1," ");
			 			strcat(buffer1, pe);
			 			strcat(buffer1," ");
			 			//strcat(buffer1,memarr[countarr].size+'0');
			 			strcat(buffer1,"\n");
			 			//strcat(buffer1,content);
			 			//strcat(buffer1,"\n");

			 			write(fdw,buffer1,strlen(buffer1));
			 		}
		countarr++;

		//printf("READING FROM THE START MEMORY REGION: %s\n\n",(char *)memrn.startAddr );
		//printf("READING FROM THE END MEMORY REGION: %s\n\n",(char *)memrn.endAddr );
		//printf("READING FROM THE ISREADABLE MEMORY REGION: %d\n\n",memrn.isReadable);
		//printf("READING FROM THE ISWRITABLE REGION: %d\n\n",memrn.isWriteable );
		//printf("READING FROM THE ISEXECUTABLE REGION: %d\n\n",memrn.isExecutabl );

		//if(memrn.isReadable==1&&memrn.isWriteable==0){
		//sizereadonlymem=sizereadonlymem+hexsubtraction(memrn.endAddr,memrn.startAddr);
		//}
		//if(memrn.isReadable==1&&memrn.isWriteable==1){
		//sizereadwritemem =sizereadwritemem+hexsubtraction(memrn.endAddr,memrn.startAddr);

		//}
		/*char sizeofmemblock[10];
		int memblk=hexsubtraction(memrn.endAddr,memrn.startAddr);
		sprintf(sizeofmemblock, "%d", memblk);
		//char hexstart[100]="0x";
		//strcpy(hexstart+2,memrn.startAddr);lear

		long long hexnumber= strtoll(memrn.startAddr, NULL, 16);




		   fp = fopen("file.txt", "w");


 if(memrn.isReadable&&hexnumber!=9223372036854775807){
			 //long long hexnumlla=4194304;
			 printf("%s ------>> %llu\n",memrn.startAddr,hexnumber);
		char *po=(char *)hexnumber;
		for(int i=33;i<100;i++){
		fputc(i, fp);
	}
		for(int i=0;i<memblk;i++){
		fputc(po[i], fp);
	}
}else{
	printf("not gonna happen!!\n" );
}
		/*for(int i=0;i<memblk;i++){

		//printf("%c",*po);
		po++;
	}*/


		//printf("END OF THE MEMORY\n");


/*
		if(prg==0){

			strcat(buffer1,memrn.startAddr);
			strcat(buffer1,"-");
			strcat(buffer1,memrn.endAddr);
			strcat(buffer1," ");
			strcat(buffer1, pe);
			strcat(buffer1," ");
			strcat(buffer1,sizeofmemblock);
			strcat(buffer1,"\n");
			//strcat(buffer1,content);
			//strcat(buffer1,"\n");

			write(fdw,buffer1,strlen(buffer1));
		}
*/

}


int convertalphabets(char hex)
{

		if(isalpha(hex)){

			 return toupper(hex)-'A'+10;
		}
		else
		{
			return hex-'0';
		}



}

char convertnum(int a)
{
	if(a >=10){


						if(a==10)
						{
							return 'A';
						}
						if(a==11)
						{
							return 'B';
						}
						if(a==12)
						{
							return 'C';
						}
						if(a==13)
						{
							return 'D';
						}
						if(a==14)
						{
							return 'E';
						}
						if(a==15)
						{
							return 'F';
						}
	}
		else
		{

			return a+'0';
		}

}

int hexsubtraction(char hex1[],char hex2[])
{


	int num1[strlen(hex1)];
	int num2[strlen(hex2)];
	int num[strlen(hex1)];
	char resultarr[50]="";
	char finalresult[50]="";
	int x=0;
	int y=strlen(hex1)-1;

	for(int i=strlen(hex1)-1;i>=0;i--)
	{

		num1[x]=convertalphabets(hex1[i]);
		num2[x]=convertalphabets(hex2[i]);

		x++;
	}



	for(int i=0;i<strlen(hex1);i++)
	{

		int d1=num1[i];
		int d2=num2[i];
		int result=0;

		if(d2>d1)
		{

				result= d1+16-d2;
				resultarr[y]=convertnum(result);
				num1[i+1]=num1[i+1]-1;
				y--;
		}
		else
		{
			result=d1-d2;
			resultarr[y]=convertnum(result);

			y--;
		}


	}
	resultarr[strlen(hex1)]='\0';

	int sigcounter=0;
	for(int k=0;k<strlen(resultarr);k++)
	{
		if(resultarr[k]-'0'<1)
		{
			sigcounter++;
		}
		else
		{
			break;
		}
	}
	int g=0;
	for(int h=sigcounter;h<strlen(resultarr);h++)
	{
		finalresult[g]=resultarr[h];
		g++;
	}
	finalresult[g]='\0';


	return hex_to_deci(finalresult);
}


long long hex_to_deci(char * hex)
{
	//printf("***********%d*****\n",strlen(hex) );
	long long decimal=0;
	long long pow=1;
	for(int i=strlen(hex)-1;i>=0;i--)
	{
		decimal=decimal+convertalphabets(hex[i])*pow;
		pow=pow*16;

	}

	 return decimal;
}
