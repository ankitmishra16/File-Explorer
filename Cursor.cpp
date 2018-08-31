#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<termios.h>
#include<sys/stat.h>
#include "Cursor.h"
#include "Listing.h"
using namespace std;
void Cursor(char c[], char rootm[], char fpath[][1000], int forwardstacktop, char bpath[][1000], int backwardstacktop)
{
	//char root[]="";
	int counter;
	//strcpy(root,c);
	//cout<<"\n In cursor and root is :"<<root;
	//cout<<"\n Calling list using argument :"<<root;
	printf("\033[0;0");//clear screen
	vector<string> ls=list(c);
	cout<<"Root Directory :"<<rootm;
	struct termios new_attr,org_attr,aft_attr;
	tcgetattr(0,&org_attr);
	new_attr=org_attr;
	new_attr.c_lflag &=~ICANON;//goin to non-canonical mode
	new_attr.c_lflag &=~ECHO;//hiding the input
	new_attr.c_cc[VMIN] =1;//due to this only one character to be  red
	new_attr.c_cc[VTIME]=0;
	unsigned int nline=ls.size();
	printf("\033[1;1H");//cursor to top
	counter=0;
	if(tcsetattr(0, TCSANOW, &new_attr))
	{
		fprintf(stderr, "could not set attribute");
	}

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
	        		 	tcsetattr(0, TCSANOW, &org_attr);
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
	        		 	tcsetattr(0, TCSANOW, &org_attr);
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
	        			//cout<<"Value of counter :"<<counter;
	        			struct stat buf;
	        			char V[1024],aa[2]; 
	        			//strcpy(V,ls[counter].c_str());
	        			stat(V,&buf);
	        			pid_t pid;
	        			strcpy(aa,"/");
	        			strcpy(V,c);
	        			strcat(V,aa);
	        			strcat(V,ls[counter-1].c_str());
	        			//cout<<(S_ISDIR(buf.st_mode))<<"\n";
	        			if((S_ISDIR(buf.st_mode)))
	        			{

	        				//cout<<"INSIDE IF\n";
	        				pid=fork();
	        				if(pid==0)
	        				{
	        					//cout<<V<<"\n";
	        					//cout<<"INSIDE NESTED IF\n";
	        					execl("/usr/bin/xdg-open","xdg-open",V, (char *)0);
	        				}

	        			}
	        			else
	        			{
	        				if(counter==1)
	        				{
	        					tcsetattr(0, TCSANOW, &org_attr);
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
								tcsetattr(0, TCSANOW, &org_attr);
								forwardstacktop=0;
								Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);  
								return;
						}
						//cout<<"Value of counter :"<<counter;
						break;
			case 'h' :   tcsetattr(0, TCSANOW, &org_attr);
						 cout<<"Root Directory :"<<rootm;
						 strcpy(bpath[backwardstacktop++],c);
						 strcpy(c,rootm);
						 tcsetattr(0, TCSANOW, &org_attr);
						 Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
						 break;
			case 127 :	int i=strlen(c)-1;
							cout<<"in backspace\n";
							strcpy(fpath[forwardstacktop++],c);
	        				while(i>=0)
	        				{
	        					if(c[i]=='/')
	        					{
	        						c[i]='\0';
	        						break;
	        					}
	        					i--;
	        				} 
	        				tcsetattr(0, TCSANOW, &org_attr);
	        				Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
	        				return;
			//default : cout<<"It is default";			 
								
		}
		//cout<<"After if   \n";
	}while(inp!='q');
    if(inp=='q'||inp=='Q')
    {
    	tcsetattr(0, TCSANOW, &org_attr);
    	//cout<<"Inputted for canonical";
    	exit(0);
    }
}