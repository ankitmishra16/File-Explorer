#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include "ExeuteCmd.h"

void copy(string src, string dst)
{
	char block[1024];
	int in, out;
	int nread;
	in=open(src,O_RDONLY);
	out=open(dst,O_WRONLY|O_CREAT, S_IRUSR| S_IXUSR|S_IRGRP);
	while(((nread=read(in,block,sizeof(block))))>0)
		write(out,block,nread);
}