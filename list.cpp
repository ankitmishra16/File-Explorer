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
#include "Listing.h"
using namespace std;
void list(void)
{
    DIR *d;
    struct stat *buf;
    struct dirent *dir;//dir will get directory names for every directory in the given directory
    char buffer[1000];//it will get the name of current directory from getcwd()
    vector<string> dirname;//vector will use to sort the file name using algorithm STL
    d = opendir(getcwd(buffer,1000));//d will get the current directorie's path
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            dirname.push_back(dir->d_name);//every directory is pushed in vector
        }
        closedir(d);
    }
    vector<string> :: iterator  itr;
    sort(dirname.begin(),dirname.end());//names of directories will be sorted by this
    itr=dirname.begin();
    printf("\x1b[H\x1b[J");//to clear the terminal
    while(itr!=dirname.end())
    {
	    const char *c= (*itr).c_str();//because stat takes const char * type argument
	    stat(c, buf);
	    printf((S_ISDIR(buf->st_mode))  ? "d" : "-");
	    printf((buf->st_mode & S_IRUSR) ? "r" : "-");
	    printf((buf->st_mode & S_IWUSR) ? "w" : "-");
	    printf((buf->st_mode & S_IXUSR) ? "x" : "-");
	    printf((buf->st_mode & S_IRGRP) ? "r" : "-");
	    printf((buf->st_mode & S_IWGRP) ? "w" : "-");
	    printf((buf->st_mode & S_IXGRP) ? "x" : "-");
	    printf((buf->st_mode & S_IROTH) ? "r" : "-");
	    printf((buf->st_mode & S_IWOTH) ? "w" : "-");
	    printf((buf->st_mode & S_IXOTH) ? "x\t" : "-\t");
	    printf("%s",getpwuid(buf->st_uid)->pw_name);
	    printf("\t");
	    cout<<getgrgid(buf->st_gid)->gr_name<<"\t";
	    cout<<(int)buf->st_size<<"\t";
	    cout<<((string)(ctime(&buf->st_mtime))).substr(0,19)<<"\t";
	    cout<<(string)*itr;
	    cout<<"\n";
	    itr++;
    }
}

