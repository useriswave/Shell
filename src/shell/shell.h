#ifndef SHELL_H
#define SHELL_H

char* sh_read_line();
char** sh_split_line(char* const line);
void sh_cleanup(char* line, char** args);

#endif

