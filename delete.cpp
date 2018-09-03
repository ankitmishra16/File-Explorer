#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include<iostream>
#include "ExeuteCmd.h"
using namespace std;

int main()
{
    // These are data types defined in the "dirent" header
    char s[1000];
    getcwd(s,sizeof(s));
    cout<<"Current directory :\t"<<s;
    cout<<"\n Enter the path of the folder you want to delete :\t";
    cin>>s;
    DIR *theFolder = opendir(s);
    struct dirent *next_file;
    char filepath[256];

    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s",s , next_file->d_name);
        remove(filepath);
        cout<<"Deleted directory :\t"<<filepath<<"\n";
    }
    closedir(theFolder);
    return 0;
}