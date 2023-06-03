#include "fileprocessor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

