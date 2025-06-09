#include "../../inc/minishell.h"

/*pipe token on cree et on ajt a la liste*/
void    pipe_token(char *line,t_token **head, t_token **actual, int *i)
{
    t_token *new;

    if ((line[*i]) == '|')
    {
        new = create_token(PIPE, "|");
        add_token(head, actual, new);
        (*i)++;
    }
}
/*redirect token, on cree et on ajt a la liste*/
void in_out_token(char *str, t_token **head, t_token **actual, int *i)
{
    t_token *new;
    
    if (str[*i] == '<')
    {
        if (str[*i + 1] == '<')
        {
            new = create_token(HEREDOC, "<<");
            (*i) += 2;
        }
        else
        {
            new = create_token(IN, "<");
            (*i)++;
        }
    }
    else if (str[*i] == '>')
    {
        if (str[*i + 1] == '>')
        {
            new = create_token(APPEND, ">>");
            (*i) += 2;
        }
        else
        {
            new = create_token(OUT, ">");
            (*i)++;
        }
    }
    add_token(head, actual, new);
}
/*on gere les guillemet char buff qui prendra les info dans les quotes grande taille pour gerer un max d erreur sinon 
peut etre opti avec un realloc mais flemme, on met dans le buff tout ce qu il y a dedans si on rencontre pipe redirect ou space
on break , marque la fin puis on cree le token et on ajt a la liste*/

void    quotes_token(char *str, t_token **head, t_token **actual, int *i)
{
    t_token *new;
    char buff[4096];
    int j;
    char q;

    j = 0;
    while(str[*i])
    {
        if (str[*i] == '"' || str[*i] == '\'')
        {
            q = str[*i];
            (*i)++;
            while(str[*i] && str[*i] != q && j < 4095)
                buff[j++] = str[(*i)++];
            if (str[*i] == q)
                (*i)++;
        }
        else if (str[*i] == 32 || str[*i] == '<'
            || str[*i] == '>' || str[*i] == '|')
            break;
        else
            buff[j++] = str[(*i)++];
    }
    buff[j] = '\0';
    new = create_token(WORD, buff);
    add_token(head, actual, new);
}
/*le reste on check si c est des char valide puis on extrait et on met dans word
ensuite on cree le token et on l ajoute a la liste puis free car substr*/
void    other_token(char *str, t_token **head, t_token **actual, int *i)
{
    t_token *new;
    int begun;
    char *word;

    begun = *i;
    while (str[*i] && is_valid_word(str[*i]))
        (*i)++;
    if(!(word = ft_substr(str, begun, *i - begun)))
        return;
    new = create_token(WORD, word);
    add_token(head, actual, new);
    free(word);
}

void    check_token(char *line,t_token **head, t_token **actual, int *i)
{
    while (line[*i])
    {
        if ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)
            (*i)++;
        else if (line[*i] == '|')
            pipe_token(line, head, actual, i);
        else if (line[*i] == '>' || line[*i] == '<')
            in_out_token(line, head, actual, i);
        else if (line[*i] == '"' || line[*i] == '\'')
            quotes_token(line, head, actual, i);
        else
            other_token(line, head, actual, i);
    }
}
/*init une tete de list et le pos actuel ensuite on parcour toute la ligne
skip les espace on cree des token pour chaque char check si c est un pipe, redirection
guillemet et le reste sera word*/
t_token *get_token(char *line)
{
    int i;
    t_token *head;
    t_token *actual;

    i = 0;
    head = NULL;
    actual = NULL;
    check_token(line, &head, &actual, &i);
    printoken(head);
    return(head);
}
