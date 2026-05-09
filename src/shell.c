#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//TODO: add complete support for cd'ing with tilde (~)
char *builtin_commands[] = {"cd", "help", "exit"};

static const Builtin builtins[SH_BUILTINS_LEN] = {
    {"cd", sh_cd}, {"help", sh_help}
};

int sh_run() {
    int status = 0;
    char *input;
    char **split;

    do {
        printf("$ ");
        

        if((input = sh_read_line()) == NULL) {
            status = 1;
            break;
        }

        if(strlen(input) == 0) continue;
        
        if(strcmp(input, "exit") == 0) {
            free(input);
            input = NULL;
            break;
        }

        if((split = sh_split_line(input)) == NULL) {
            free(input);
            input = NULL;
            status = 1;
            break;
        }

        status = sh_execute(split);

        free(input);
        free(split);
        input = NULL;
        split = NULL;
    } while(status == 0);

    printf("program closed with exit code: %d\n", status);

    return status; 
}

char *sh_read_line(void) {
    size_t max_size = SH_MAX_BUFFSIZE;
    char *buffer = (char *) malloc(max_size * sizeof(char));
    if(!buffer) {
        fprintf(stderr, "ERROR: buffer allocation failed.\n");
        return NULL;
    }

    int c;
    size_t pos = 0;
    while((c = getchar()) != EOF && c != '\n') {        // NOTE: \n is never stored, dont use strcspn to replace '\n'
        if(pos >= max_size) {
            max_size *= 2;
            char *temp = (char *) realloc(buffer,  max_size);
            if(!temp) {
                fprintf(stderr, "ERROR: buffer reallocation failed.\n");
                return NULL;
            } 
            buffer = temp;
        }
        buffer[pos++] = c;
    }
    buffer[pos] = '\0';
    return buffer;
}

char **sh_split_line(char *line) {
    size_t max_size = SH_MAX_TOKEN_BUFFSIZE;
    char **tokens = (char **) malloc(max_size * sizeof(char *));
    if(!tokens) return NULL;
    
    char *token = strtok(line, SH_TOKEN_DELIM);
    
    size_t pos = 0;
    while(token) {                  // split -> store
        if(pos >= max_size) {
            max_size += SH_MAX_TOKEN_BUFFSIZE;
            char **temp = realloc(tokens, max_size * sizeof(char *));
            if(!temp) {
                fprintf(stderr, "ERROR: failed to reallocate to token.\n");
                free(tokens);
                tokens = NULL;
                return NULL;
            }
            tokens = temp;
        }

        tokens[pos] = token;
        token = strtok(NULL, SH_TOKEN_DELIM);
        pos++;
    }

    tokens[pos] = NULL;
    return tokens;
}

int sh_execute(char **args) {
    for(size_t i = 0; i < SH_BUILTINS_LEN; i++) {
        if(strncmp(args[0], builtins[i].identifier, strlen(builtins[i].identifier)) == 0) {
            return builtins[i].fn(args);
        }
    }

    return sh_run_process(args);
}

int sh_run_process(char **args) {
    int status;
    pid_t pid = fork();

    if(pid == 0) {
        if(execvp(args[0], args) == -1) {
            // prints the error that happens at runtime
            perror("sh");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 1) {
        fprintf(stderr, "ERROR: failed forking main process\n");
    }
    else {
        waitpid(pid, &status, WUNTRACED);
    }

    return 0;
}

int sh_cd(char **args) {

    if(args[1] == NULL) {
        fprintf(stderr, "sh: expected argument for \"cd\"\n");
        return 0;
    }

    else if(strcmp("~", args[1]) == 0) {
        if(chdir(getenv("HOME")) != 0) {
            fprintf(stderr, "sh: no such directory \"%s\"\n", args[1]);
        }
    }

    else {
        if(chdir(args[1]) != 0) {
            fprintf(stderr, "sh: no such directory \"%s\"\n", args[1]);
        }
    }
    
    printf("changed directory to: %s\n", args[1]);
    return 0;
}

int sh_help(char **args) {
    (void) args;            // make the compiler shut up because i do whatever i want
    printf("Important Notes:\n\tCommands must be on a single line.\n\tAll arguments must separated by whitespace.\n\tNo quoting arguments.\n");
    printf("\nBuilt in commands:\n");
    printf("\tcd <arg>: change directory\n");
    printf("\thelp: show help menu\n");

    return 0;
}

size_t builtin_cmds_len() {
    return sizeof(builtin_commands) / sizeof(char *);
}
