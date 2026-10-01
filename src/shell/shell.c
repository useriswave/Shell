#include "shell.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFF_SIZE 256

static char* try_realloc_buffer(char* buffer, size_t position, size_t capacity)
{
    if (position >= capacity) {
        size_t temp_cap = capacity == 0 ? 2 : capacity * 2;
        void* temp =  realloc(buffer, temp_cap);

        if (!temp) {
            return NULL;
        }

        buffer = temp;
        capacity = temp_cap;
    }

    return buffer;
}

char* sh_read_line()
{
    char* buffer = (char*) malloc(INITIAL_BUFF_SIZE);

    if (!buffer) {
        return NULL;
    }

    size_t position = 0;
    size_t capacity = INITIAL_BUFF_SIZE;
    int c = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (!try_realloc_buffer(buffer, position, capacity)) {
            free(buffer);
            return NULL;
        }

        buffer[position++] = c;
    }

    buffer[position] = '\0';
    return buffer;
}

char** sh_split_line(char* const line)
{
    char** args = (char**) malloc(INITIAL_BUFF_SIZE * sizeof(char*));

    if (!args) {
        return NULL;
    }

    char* token = strtok(line, " ");
    size_t pos = 0;

    while (token) {
        args[pos] = strdup(token);
        token = strtok(NULL, " ");
        ++pos;
    }

    args[pos] = NULL;
    return args;
}

void sh_cleanup(char* line, char** args)
{
    char** temp = args;

    if (temp) {
        while (*temp != NULL) {
            free(*temp++);
        }
    }

    free(args);
    free(line);
}
