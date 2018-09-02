#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<termios.h>
#include<sys/stat.h>
#include "Cursor.h"
#include "Listing.h"
#include "Command.h"
#include "ExecuteCmd.h"
using namespace std;

void cmd(char c[], char rootm[], char fpath[][1000], int forwardstacktop, char bpath[][1000], int backwardstacktop)
{
	printf("\033[35;1H");//cursor to bottom
	printf("\nCOMMAND MODE");
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------\n$");
	char cm;
	string st1;
	int i=0;
	while(1)
	{
		cm=getchar();
		switch(cm)
		{
			case '\n' : executeCmd(st1.c_str(),c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);//header file to be made for it 
						st1[0]='\0';
						Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
						return;
						break;
			case 27 : Cursor(c,rootm,fpath,forwardstacktop,bpath,backwardstacktop);
					  return;
					  break;
			case 127 :st1.clear();
					  i=0;
					  printf("\033[2K");
					  printf("\033[38;1H");//cursor to bottom
					  printf("$");
					  break;
			default : cout<<cm;
					  st1.push_back(cm);
		}
	}
}