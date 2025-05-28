#include "../inc/minishell.h"

int start(char *line)
{
    t_token *token;

    token = get_token(line);
    if (!token)
    {
        //exit
    }
    //parser

}



int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;


    while (19)
    {
        line = readline("matteoshell$ ");
        if (!line) // si on CTRL+D (car ca renvoie NULL)
            break ;
        if (!line || check_line(line))
            break;
        add_history(line);
        if (!start(line))
        free(line);
    }
    return (0);
}