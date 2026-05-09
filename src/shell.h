#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>

#define SH_MAX_BUFFSIZE 1024
#define SH_MAX_TOKEN_BUFFSIZE 80
#define SH_TOKEN_DELIM " \a\r\n"
#define SH_BUILTINS_LEN 2

typedef int (*builtin_fn) (char **args);

typedef struct {
    const char *identifier;
    builtin_fn fn;
} Builtin;

int sh_run();
char *sh_read_line();
char **sh_split_line(char *line);
int sh_execute(char **args);
int sh_run_process(char **args);
int sh_cd(char **args);
int sh_help(char **args);
size_t builtin_cmds_len();

#endif // !SHELL_H
