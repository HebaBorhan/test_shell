#include "simple_shell.h"
#include <stdlib.h>
/**
* *_strdup - function that returns a pointer to a newly allocated
* space in memory,
* which contains a copy of the string given as a parameter.
* @str: string to be dublicated
* Return: pointer to duplicated string,
* or NULL if insufficient memory was available or str = NULL
*/
char *_strdup(char *str)
{
char *dupstr;
int i, counter = 0;
if (str == NULL)
{
return (NULL);
}
while (str[counter] != '\0')
{
counter++;
}
dupstr = malloc(sizeof(char) * (counter + 1));
if (dupstr == NULL)
{
return (NULL);
}
for (i = 0; str[i]; i++)
{
dupstr[i] = str[i];
}
return (dupstr);
}


/**
* remove_newline - function that removes new line
* @input: string to be checked
* Return: void
*/
void remove_newline(char *input) 
{
    char *newline_ptr = _strchr(input, '\n');
    if (newline_ptr != NULL) 
    {
        *newline_ptr = '\0';
    }
}

/**
* freemalloc - function that free memory allocation
* @arg: string to be freed
* @n: value to be checked for condition
* Return: void
*/

void freemalloc(char **arg, int n)
{
    int i;
    if (n == 1)
    {
        if (arg == NULL)
            return;
        for (i = 0; arg[i]; i++)
        {
            free(arg[i]);
            arg[i] = NULL;
        }
        free(arg);
        arg = NULL;
    }
    else
    {
        free(arg);
        arg = NULL;
    }
}