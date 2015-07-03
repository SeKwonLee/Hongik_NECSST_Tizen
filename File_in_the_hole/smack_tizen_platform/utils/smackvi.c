/* 
 * This file is part of libsmack
 * 
 * This library is implemented for System programming class in Hongik Univ.
 * Purpose of this library is to have fun with SMACK module in tizen platform.
 * Feel free to use it and republish
 * 
 * Author: Jeonghyeon Kim <ckeiom@gmail.com>
 */
#include <sys/smack.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void print_usage()
{
	printf("Usage : smackvi <file_name>\n");
}
#define BUFFSIZE 64

/* 
 * Like "vi" command in core utils,
 * smackvi reads contents of a file.
 * However, for simple implementation, 
 * writing to file and using internal commands of "vi" is not implemented
 * while reading a file, it checks label of the file.
 * If the label is (@), this program will be killed
 */
int main(int argc, char **argv)
{
	int ret;
	char* filename;
	char* label;
	FILE *fp;
	char* str[BUFFSIZE];
	char c;

	
	system("clear");

	if(argc !=2)
		print_usage();

	filename = argv[1];
	
	fp = fopen(filename,"r");
	if( !fp )
	{
		printf("No such file : %s\n",filename);
		goto Err_ret;
	}
	/* Get label */
	ret = smack_lgetlabel(filename, &label, SMACK_LABEL_ACCESS);
	if( ret < 0 )
	{
		printf("Smack label access failed...\n");
		goto Err_ret;
	}
	/* Read contents of file */
	while(fgets(str, BUFFSIZE, fp) )
		printf("%s",str);

	/* Check if label is (@) */
	if( strncmp(label,"(@)",3) == 0 )
	{
		if(fork()==0)
		{
			int i;

			/* Child process waits for 3 secs, */ 
			printf("\n\n\n\n[[[[[ GRENADE!!! ]]]]] \n");
			printf("Count down: 3");
			fflush(stdout);
			for(i=2;i>=0;i--)
			{
				sleep(1);
				printf("\b%d",i);
				fflush(stdout);
			}
			printf("\n");
			system("clear");
			/* And it then kills smackvi */
			kill(getppid(), SIGKILL );
			exit(0);
		}
	}
	do
	{
		printf("\nInput 'q' to quit>");
		scanf("%c",&c);fflush(stdin);
		if( c=='q' )
			break;
	}while(1);
	
	return EXIT_SUCCESS;

Err_ret:
	return -1;
}

