#include "shell.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 256

static void* try_realloc_buffer(char* buffer, size_t position, size_t capacity)
{
    if (position >= capacity) {
        size_t temp_cap = capacity == 0 ? 2 : capacity * 2;
        char* temp = (char*) realloc(buffer, temp_cap);

        if (!temp) {
            free(buffer);
            return NULL;
        }

        buffer = temp;
        capacity = temp_cap;
    }

    return buffer;
}

char* sh_read_line()
{
    char* buffer = (char*) malloc(MAX_BUFF_SIZE);
    size_t position = 0;
    size_t capacity = MAX_BUFF_SIZE;
    int c = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (!try_realloc_buffer(buffer, position, capacity)) {
            return NULL;
        }

        buffer[position++] = c;
    }

    buffer[position] = '\0';
    return buffer;
}

char* sh_split_args(const char* const line)
{
    (void) line;
    return NULL;
}

