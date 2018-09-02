#include<unistd.h>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<fcntl.h>
#include<vector>
#include<termios.h>
#include<sys/stat.h>
#include "Command.h"
#include "Cursor.h"
#include "ExecuteCmd.h"

void executeCmd(string cmd,char c[], char rootm[], char fpath[][1000], int forwardstacktop, char bpath[][1000], int backwardstacktop)
{
	string opcode, dir;
	vector<string> cmdchuncks;
	int i=0;
	istringstream ss(cmd);
	while(ss>>opcode)
	{

		cmdchuncks.push_back(opcode);
	}
	//cout<<cmdchuncks[0];
	//cin>>i;
	if(cmdchuncks[0]=="copy_file")
					{ char file[1000], di[1000], block[1024];
						int in, out, nread;
						for(i=1;i<cmdchuncks.size()-1;i++)
						{
								//cout<<"\n File name :"<<cmdchuncks[i];
								//cout<<"\n Vector entry for Destintion :"<<cmdchuncks[cmdchuncks.size()-1];
								strcpy(file,c);
								strcat(file,"/");
								strcat(file,cmdchuncks[i].c_str());
								//cout<<"\n flie path :"<<file;
								strcpy(di,rootm);
								strcat(di,"/");
								//cout<<"\n Destintion path :"<<di;
								strcat(di,cmdchuncks[cmdchuncks.size()-1].c_str());
								//cout<<"\n Destination directory :"<<cmdchuncks[cmdchuncks.size()-1];
								//cout<<"\n Destintion path(before appending file name) :"<<di;
								strcat(di,cmdchuncks[i].c_str());
								//cout<<"\n Destintion path :"<<di;
								//cin>>in;
								in=open(file,O_RDONLY);
								out=open(di,O_WRONLY|O_CREAT, S_IRUSR| S_IXUSR|S_IRGRP|S_IWUSR|S_IWGRP|S_IXGRP);
								while(((nread=read(in,block,sizeof(block))))>0)
									write(out,block,nread);
								di[0]=NULL;
						}
					
					}
		else if(cmdchuncks[0]=="goto")
					{
						cout<<"IN GOTO MODULE";
					strcpy(bpath[backwardstacktop++],c);
					forwardstacktop=0;
					char pt[1000];
					strcpy(pt,c);
					strcat(pt,"/");
					strcat(pt,cmdchuncks[1].c_str());
					cout<<pt<<"\n";
					 Cursor(pt,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
					 return;

					}
		else if(cmdchuncks[0]=="create_dir")
					{
						char di[1000];
						strcpy(di,c);
						strcat(di,"/");
						strcat(di,cmdchuncks[1].c_str());
					 	struct stat st = {0};
						if (stat(di, &st) == -1) {
						    mkdir(di, 0700);
						}		
					}					
		else if(cmdchuncks[0]=="delete_file")
					{
						char di[1000];
						strcpy(di,c);
						strcat(di,"/");
						strcat(di,cmdchuncks[1].c_str());
					 	remove(di);
					}
		else if(cmdchuncks[0]=="rename")
					{
						char old[1000], newn[1000];
						strcpy(old,c);
						strcat(old,"/");
						strcat(old,cmdchuncks[1].c_str());
						strcpy(newn,c);
						strcat(newn,"/");
						strcat(newn,cmdchuncks[2].c_str());
						rename(old,newn);

					}			
		else if(cmdchuncks[0]=="create_file")
					{
						char path[1000];
						strcpy(path, c);
						strcat(path,"/");
						strcat(path,cmdchuncks[1].c_str());
						struct stat buf;
						fopen(path,"w+");
						
					}	
		else if(cmdchuncks[0]=="move_file")
					{
						char file[1000], di[1000], block[1024];
						int in, out, nread;
						for(i=1;i<cmdchuncks.size()-1;i++)
						{
								strcpy(file,c);
								strcat(file,"/");
								strcat(file,cmdchuncks[i].c_str());
								strcpy(di,rootm);
								strcat(di,"/");
								strcat(di,cmdchuncks[cmdchuncks.size()-1].c_str());
								strcat(di,cmdchuncks[i].c_str());
								in=open(file,O_RDONLY);
								out=open(di,O_WRONLY|O_CREAT, S_IRUSR| S_IXUSR|S_IRGRP|S_IWUSR|S_IWGRP|S_IXGRP);
								while(((nread=read(in,block,sizeof(block))))>0)
									write(out,block,nread);
								if(out)
								    remove(file);
						}
					}		
														
	

}