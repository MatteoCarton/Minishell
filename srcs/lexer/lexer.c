#include "../../inc/minishell.h"

void    direction_token(char *line, int i)
{
    
}

void    quotes_token(char *line, int i)
{
    
}

void    other_token(char *line, int i)
{
    
}

t_token *get_token(char *line)
{
    int i = 0;
    
    while (line[i])
    {
        if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
            i++;
        else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
            direction_token(line, i);
        else if (line[i] == '"' || line[i] == '\'')
            quotes_token(line, i);
        else
            other_token(line, i);
    }

    retunr (1);
}