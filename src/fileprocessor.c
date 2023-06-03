#include "fileprocessor.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

char buffer[200][MAX_FILELENGTH];

void scandirMy(char *dirname)
{
	DIR *dir;
	struct dirent *ent;
	
	printf("Reading '%s':\n", dirname);
	
	if ((dir = opendir(dirname)) == NULL)
	{
		perror("Error opening");
		exit(1);
	}
	
	size_t dirLen = strlen(dirname);
	char pathTmp[MAX_FILELENGTH];
	strcpy(pathTmp, dirname);
	
	while ((ent = readdir(dir)) != NULL)
	{
		strcpy(pathTmp+dirLen, ent->d_name);
		if(isFile(pathTmp)) {
			strcpy(buffer[bufferIndex++], pathTmp);
		}
	}
	if (closedir(dir) != 0)
	{
		perror("Error closing");
	}
	
	printf("Files:\n");
	for(int i=0; i<bufferIndex; ++i) {
		printf("%s\n", buffer[i]);
	}
}
