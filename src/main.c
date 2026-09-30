#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell/shell.h"

int main()
{
    char* line = sh_read_line();
    printf("line: %s\n", line);
    printf("line len: %lu\n", strlen(line));

    free(line);
    return 0;
}
