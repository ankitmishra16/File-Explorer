#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<termios.h>
#include "Cursor.h"
#include "Listing.h"
using namespace std;
void Cursor(char c[])
{
	char root[]="";
	int counter;
	strcpy(root,c);
	cout<<"\n In cursor and root is :"<<root;
	cout<<"\n Calling list using argument :"<<root;
	printf("\033[0;0");
	vector<string> ls=list(root);
	struct termios new_attr,org_attr;
	tcgetattr(0,&org_attr);
	new_attr=org_attr;
	new_attr.c_lflag &=~ICANON;//goin to non-canonical mode
	new_attr.c_lflag &=~ECHO;//hiding the input
	new_attr.c_cc[VMIN] =1;//due to this only one character to be  red
	new_attr.c_cc[VTIME]=0;
	//new_attr.c_lflag &=~ISIG;//due to this no secial input/signals are allowed
	unsigned int nline=ls.size();
	if(tcsetattr(0, TCSANOW, &new_attr))
	{
		fprintf(stderr, "could not set attribute");
	}

	char inp;
	do{
		inp=getchar();
		if (inp == '\033')  // if the first value is esc
		{
	    getchar(); // skip the [
	    switch(getchar()) { // the real value
	        case 'A':printf("\033[1A");

	            break;
	        case 'B':printf("\033[1B");

	            break;
	        case 'C':printf("\033[1C");
	            break;
	        case 'D':printf("\033[1D");
	            // code for arrow left
	            break;
	    	}
		}
	}while(inp!='q'||inp!='\n');
	/*if(inp=='\n')
	{
		strcat(path, ls[counter]);
		list(path.s_)
	}*/

}