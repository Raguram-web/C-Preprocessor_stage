#include "header.h"
extern int cnt;
void writeToFile(char(*line)[200],char*filename)
{
	char str[20],*pt=NULL;
	strcpy(str,filename);
	pt=strchr(str,'.');
	pt++;
	*pt='i';

	printf(".i file is created\n");
	FILE*fp;
	fp=fopen(str,"w");
	if(fp==NULL)
	{
		printf("filed to open the file\n");
		exit(0);
	}
	char*p;
	for(int i=0;i<cnt;i++)
	{
		fputs(line[i],fp);
	}
	fclose(fp);
}
