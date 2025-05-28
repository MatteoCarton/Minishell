#include "../inc/minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    char *line;
    
    while (19)
    {
        line = readline("matteoshell$ ");
        if (!line) // si on CTRL+D (car ca renvoie NULL)
            break ;
        if (*line) // si elle est pas vide
        {
            add_history(line);
        }
        free(line);
    }
    return (0);
}