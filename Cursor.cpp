#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<termios.h>
#include<sys/stat.h>
#include "Cursor.h"
#include "Listing.h"
#include "Command.h"
using namespace std;
void Cursor(char c[], char rootm[], char fpath[][1000], int forwardstacktop, char bpath[][1000], int backwardstacktop)
{
	int counter;
	printf("\033[37;1H");//cursor to bottom
	printf("\nNORMAL MODE");
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------");
	printf("\033[0;0");//clear screen
	vector<string> ls=list(c);
	cout<<"Root Directory :"<<rootm;
	unsigned int nline=ls.size();
	printf("\033[1;1H");//cursor to top
	counter=0;
	char inp;
	
	do{// skip the [
		inp=getchar();
	    switch(inp) { // the real value
	        case 'A'://code for up
	        		 if(counter>0){
	        		  	printf("\033[1A");
	        		  	counter--;}


	            break;
	        case 'B'://code for down
	                if(counter<=nline)
	        		{
	        			printf("\033[1B");
	        			counter++;
	        		}

	            break;
	        case 'C': //code for right arrow
	        		 if(forwardstacktop>0)
	        		 {
	        		 	strcpy(bpath[backwardstacktop++],c);
	        		 	//tcsetattr(0, TCSANOW, &org_attr);
	        		 	Cursor(fpath[--forwardstacktop],rootm,fpath,forwardstacktop,bpath,backwardstacktop);
	        		 	return;
	        		 }
	        		 else
	        		 {
	        		 	printf("\033[1C");
	        		 }
	            break;
	        case 'D'://code for left arrow
	        		 if(backwardstacktop>0)
	        		 {
	        		 	strcpy(fpath[forwardstacktop++],c);
	        		 	Cursor(bpath[--backwardstacktop],rootm,fpath,forwardstacktop,bpath,backwardstacktop);
	        		 	return;

	        		 }
	        		 else
	        		 {
	        			printf("\033[1D");
	        		}
	            break;
	        case '\n':	
	        			char r[1000];
	        			strcpy(bpath[backwardstacktop++],c);
	        			struct stat buf;
	        			char V[1024],aa[2]; 
	        			pid_t pid;
	        			strcpy(aa,"/");
	        			strcpy(V,c);
	        			strcat(V,aa);
	        			strcat(V,ls[counter-1].c_str());
	        			stat(V,&buf);
	        			if(!(S_ISDIR(buf.st_mode)))
	        			{
	        				pid=fork();
	        				if(pid==0)
	        				{
	        					execl("/usr/bin/xdg-open","xdg-open",V, (char *)0);
	        				}

	        			}
	        			else
	        			{
	        				if(counter==1)
	        				{
	        		 			Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);	
	        		 			return;
	        				}
		        			if(counter==2)
		        			{
		        				cout<<"going to parent directory";
		        				int i=strlen(c)-1;
		        				while(i>=0)
		        				{
		        					if(c[i]=='/')
		        					{
		        						c[i]='\0';
		        						break;
		        					}
		        					i--;
		        				}
		        			}
		        			else
		        			{
								strcpy(r,ls[counter-1].c_str());
								strcat(c, "/");
								strcat(c, r);
							}
								forwardstacktop=0;
								Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);  
								return;
						}

						break;
			case 'h' :   
						 cout<<"Root Directory :"<<rootm;
						 strcpy(bpath[backwardstacktop++],c);
						 strcpy(c,rootm);
						 forwardstacktop=0;
						 Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
						 break;
			case 127 :	
						{
							int j=strlen(c)-1;
							cout<<"in backspace\n";
							if(!strcmp(c,rootm))
							{
								Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
								return;
							}
							else
							{
								strcpy(fpath[forwardstacktop++],c);
		        				while(j>=0)
		        				{
		        					if(c[j]=='/')
		        					{
		        						c[j]='\0';
		        						break;
		        					}
		        					j--;
		        				}
		        				Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
	        					return;
	        				} 
	        			}
	        case ':' : cmd(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
	        			return;							 
								
		}
	}while(inp!='q');
    if(inp=='q'||inp=='Q')
    {
    	return;
    }
}