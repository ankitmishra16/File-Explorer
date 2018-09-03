#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string>
#include<iostream>
#include "ExeuteCmd.h"
using namespace std;
void mkdier(string  s)
{
	struct stat st = {0};
	//string s;
	/*char t[1000],s[1000];
	cout<<"Current directory is :\t"<<t;
	cout<<"Enter the directory(with folder name) :\n";
	cin>>s;*/
	if (stat(s, &st) == -1) {
	    mkdir(s, 0700);
	    	//cout<<"Directory create";

	}
}
