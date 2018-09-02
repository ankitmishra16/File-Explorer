#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include<string>
#include<algorithm>
#include<sys/stat.h>
#include<iostream>
#include<pwd.h>
#include<grp.h>
#include<termios.h>
#include "Cursor.h"
#include "Listing.h"
using namespace std;
int main()
{
 char str[1000]="", fpath[1000][1000], bpath[1000][1000], root[1000]=""; //fpath for forward paths and bpath for backward path
 string rootm;
 int forwardstacktop,backwardstacktop;//fp will be stack top of fpath stack, and bp will be stack top of backward path
 forwardstacktop=0;
 backwardstacktop=0;
 //cout<<str<<"\n";
 getcwd(str,sizeof(str));
 strcpy(bpath[0],str);
 strcpy(root,str);
 //cout<<"\n Calling Cursor";
 //Cursor(path,root,forward stack, forward stack top, backward stack, backward stack top)
 struct termios new_attr,org_attr,aft_attr;
	tcgetattr(0,&org_attr);
	new_attr=org_attr;
	new_attr.c_lflag &=~ICANON;//goin to non-canonical mode
	new_attr.c_lflag &=~ECHO;//hiding the input
	new_attr.c_cc[VMIN] =1;//due to this only one character to be  red
	new_attr.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &new_attr))
	{
		fprintf(stderr, "could not set attribute");
	}

 Cursor(str,root,fpath,forwardstacktop,bpath,++backwardstacktop);
 tcsetattr(0, TCSANOW, &org_attr);
 //str="home/Documents";
 //vector<string> ls=list(str);
 return 0;
}
