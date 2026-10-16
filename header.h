//header.h
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
extern int cnt;
void * readFromFile(char*filename);
void writeToFile(char(*line)[200],char*filename);
void * remove_comments(char(*line)[200]);
void *replace_macros(char (*line)[200]);
void *include_headers(char (*line)[200]);
