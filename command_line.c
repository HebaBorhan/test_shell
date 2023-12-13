#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

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
        freemalloc(cmd);
        return (NULL);
    }
    remove_newline(cmd);
    /*if (_strcmp(cmd, "exit") == 0) 
    {
        exit(1);
    }*/
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
        /*freemalloc(args, 0);*/
        return (NULL);
    }
    token = strtok(cmdcpy, delim);
    i = 0; 
    while (token)
    {
        args[i] = _strdup(token); 
        token = strtok(NULL, delim);
        i++;
    }
    args[i] = NULL;
    freemalloc(cmd);
    freemalloc(cmdcpy);
    

   return (args);
}

/**
 * execution - function that parse and excute commands
 * @cmd: command to be parsed and executed
 * Return: void
*/

int execution(char **args, char **argv)
{
    pid_t pid;
    int status;
    extern char **environ;

    /*if (access(args, X_OK) == 0)*/
    
         pid = fork();
         if (pid == -1) 
         {
            perror("fork");
            return(-1);
         }
        if (pid == 0) 
        {
            if (execve(args[0], args, environ) == -1)
				{
					perror(argv[0]);
                    freemalloc2d(args);
                    exit(EXIT_FAILURE);
				}
            }
                     
        else 
        {            
            wait(&status); 
            freemalloc2d(args);
        }
    

    return (WEXITSTATUS(status));
}
