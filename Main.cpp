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
	getchar();
 char str[1000]="";
 cout<<"In the main\n";
 cout<<str<<"\n";
 getcwd(str,1000);
 cout<<str<<"\n";
 cout<<"\n Calling Cursor";
 Cursor(str);
 //str="home/Documents";
 //vector<string> ls=list(str);
 return 0;
}
