#include<termios.h>
#include<stdio.h>
#include<stdlib.h>

#define PASS_LEN 8

int main()
{
	struct termios initialsettings,newsettings;
	char password[PASS_LEN+1];
	tcgetattr(fileno(stdin),&initialsettings);
	newsettings=initialsettings;
	newsettings.c_lflag &=~ECHO;
	printf("Enter your password : ");
	if(tcsetattr(fileno(stdin),TCSAFLUSH, &newsettings)!=0)
	{
		fprintf(stderr , "Could not set attributes\n");
	}
	else
	{
		fgets(password, PASS_LEN, stdin);
		tcsetattr(fileno(stdin), TCSANOW, &initialsettings);
		fprintf(stdout, "\nYou entered %s\n", password);
	}
}