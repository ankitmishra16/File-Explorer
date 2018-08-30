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
#include "Cursor.h"
#include "Listing.h"
using namespace std;
int main()
{
 char str[1000]="", fpath[1000][1000], bpath[1000][1000]; //fpath for forward paths and bpath for backward path
 int forwardstacktop,backwardstacktop;//fp will be stack top of fpath stack, and bp will be stack top of backward path
 forwardstacktop=0;
 backwardstacktop=0;
 //cout<<str<<"\n";
 getcwd(str,sizeof(str));
 strcpy(bpath[0],str);
 //cout<<"\n Calling Cursor";
 //Cursor(path,root,forward stack, forward stack top, backward stack, backward stack top)
 Cursor(str,str,fpath,forwardstacktop,bpath,++backwardstacktop);
 //str="home/Documents";
 //vector<string> ls=list(str);
 return 0;
}
