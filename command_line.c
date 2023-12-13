#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * *interpreter - function that reads user input
 * Return: cmd
*/

char *interpreter(void)
{
char *cmd = NULL;
size_t n = 0;
ssize_t input;

    if (isatty(STDIN_FILENO)) 
       write(STDOUT_FILENO, "$ ",2);
    input = getline(&cmd, &n, stdin);
    if (input == -1)
    {
        free(cmd);
        return (NULL);
    }
    remove_newline(cmd);
    if (_strcmp(cmd, "exit") == 0) 
    {
        exit(1);
    }


return(cmd);
}

/**
 * **tokenizer - function that parse and tokenize the command
 * @cmd: command to be parsed and tokinize
 * Return: void
*/
char **tokenizer(char *cmd)
{
    char *cmdcpy = NULL, *token = NULL, *delim = " \n";
    char **args = NULL;
    int i = 0;
    if (cmd == NULL)
    {
        return (NULL);
    }

    cmdcpy = _strdup(cmd);
    token = strtok(cmd, delim);
    while (token)
    {
        i++;
         token = strtok(NULL, delim);
    }
    args = malloc((i + 1) * sizeof(char *));
    if (args == NULL)
    {
        return (NULL);
    }
    token = strtok(cmdcpy, delim);
    i = 0; 
    while (token)
    {
        args[i] = token; /*free cpy will delete everything*/
        token = strtok(NULL, delim);
        i++;
    }
    args[i] = NULL;
    /*free(cmd);*/
    free(cmdcpy);

   return (*args);
}

/**
 * execution - function that parse and excute commands
 * @cmd: command to be parsed and executed
 * Return: void
*/

int execution(char *cmd)
{
    pid_t pid;
    char **args = NULL;
    if (access(cmd, X_OK) == 0) {
         pid = fork();
         if (pid == -1) 
         {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) 
        {
            args = malloc(2 * sizeof(char));
            if (args == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            args[0] = cmd;
            args[1] = NULL;
            execve(cmd, args, NULL);           
            perror("execve");
            free(args);
            exit(EXIT_FAILURE);
        } else {            
            wait(NULL); 
        }
    } 
    else {
        write(STDOUT_FILENO, "./shell: Command not found\n", 27);
    }
}

