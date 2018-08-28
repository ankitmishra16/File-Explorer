#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<termios.h>
#include "Cursor.h"
#include "Listing.h"
using namespace std;
void Cursor(char c[], char rootm[], char fpath[][1000], int forwardstacktop, char bpath[][1000], int backwardstacktop)
{
	char root[]="";
	int counter;
	strcpy(root,c);
	cout<<"\n In cursor and root is :"<<root;
	cout<<"\n Calling list using argument :"<<root;
	printf("\033[0;0");
	vector<string> ls=list(root);
	struct termios new_attr,org_attr,aft_attr;
	tcgetattr(0,&org_attr);
	new_attr=org_attr;
	new_attr.c_lflag &=~ICANON;//goin to non-canonical mode
	new_attr.c_lflag &=~ECHO;//hiding the input
	new_attr.c_cc[VMIN] =1;//due to this only one character to be  red
	new_attr.c_cc[VTIME]=0;
	unsigned int nline=ls.size();
	printf("\033[1;1H");
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
	        		 	Cursor(fpath[--forwardstacktop],rootm,fpath,forwardstacktop,bpath,backwardstacktop);
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

	        		 }
	        		 else
	        		 {
	        			printf("\033[1D");
	        		}
	            break;
	        case '\n':	char r[1000];

						strcpy(r,ls[counter-1].c_str());
						strcat(c, "/");
						strcat(c, r);
						strcpy(bpath[backwardstacktop++],c);
						Cursor(bpath[backwardstacktop-1],rootm,fpath,forwardstacktop,bpath,backwardstacktop);  
						break;
			case 'h' :Cursor(rootm,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
						break;			
		}
		//cout<<"After if   \n";
	}while(inp!='q');
    if(inp=='q'||inp=='Q')
    {
    	tcgetattr(0,&new_attr);
    	aft_attr=new_attr;
    	aft_attr.c_lflag&=ICANON;
    	aft_attr.c_lflag&=ECHO;
    	tcsetattr(0, TCSANOW, &aft_attr);
    	exit(0);
    }
}