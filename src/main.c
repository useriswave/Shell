#include "shell/shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_args(char** args)
{
    printf("[");
    const char* sep = "";

    for (size_t i = 0; args[i]; ++i) {
        printf("%s\"%s\"", sep, args[i]);
        sep = ", ";
    }

    printf("]\n");
}

int main()
{
    char* line = NULL;
    char** args = NULL;

    while (true) {
        printf("$ ");
        line = sh_read_line();

        if (!line) {
            break;
        }

        if (strncmp(line, "exit", 5) == 0) {
            break;
        }

        args = sh_split_line(line);
        if (!args) return 1;

        sh_cleanup(line, args);
        line = NULL;
        args = NULL;
    }

    sh_cleanup(line, args);
    return 0;
}
