#include "header.h"
int cnt;
int main(int argc,char**argv)
{
	char(*line)[200]=NULL;
	if(argc!=3)
	{
		printf("wrong input\n");
		printf("please provide exe sourcefile_name destination filename\n");
		exit(0);
	}
	line=readFromFile(argv[1]);
	if(line == NULL)
	{
		return 1;
	}
	line=include_headers(line);
	  if(line == NULL)
		  return 1;
	line=remove_comments(line);
	line=replace_macros(line);
	writeToFile(line,argv[2]);
	free(line);

	return 0;
}
