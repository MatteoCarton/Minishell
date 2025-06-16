#include "../inc/minishell.h"

void free_env(char **env)
{
    int i;
    
    i = 0;
    if (!env)
        return;
    while (env[i])
    {
        free(env[i]);
        env[i] = NULL;
        i++;
    }
    free(env);
}

void	clean_token(t_token *token)
{
	if (!token)
		return ;
		
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
	
	token->next = NULL;
	token->type = 0;
}

void	free_token(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;

	current = *head;
	while (current)
	{
		next = current->next;
		clean_token(current);
		free(current);
		current = next;
	}
	
	*head = NULL;
}

/*on cree token malloc size de la struct puis on dup str , def le type et set le next a NUll 
puis on return*/
t_token *create_token (t_token_type type, char *str)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->str = ft_strdup(str);
    if(!new->str)
        return (free(new), NULL);
    new->type = type;
    new->next = NULL;
    return (new);
}
/*add a la liste, si la liste est vide on set le premier a la tete ensuite on dit on add next ect*/
void add_token(t_token **head, t_token **actual, t_token *new)
{
    if (*head == NULL)
    {
        *head = new;
        *actual = new;
    }
    else if (*actual)
    {
        (*actual)->next = new;
        *actual = new;
    }
}
/*pour printf les token test*/
void    printoken(t_token *head)
{
    t_token *actual;

    actual = head;
    while(actual)
    {
        printf("type: %d, value: %s\n", actual->type, actual->str);
		actual = actual->next;
    }
}

/*dans la fonction handle quotes juste gerer les char*/
int is_valid_word(char c)
{
	return (ft_isalnum(c) || c == '"' || c == '\'' || ft_strchr(EXTRA_CHAR, c));
}

int    check_quotes(char *line)
{
    int		i;
	char	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"'))
		{
			if (!open)
				open = line[i];
			else if (line[i] == open)
				open = 0;
		}
		i++;
	}
    if (open == 0)
        return(1);
	else
        return (0);
}

// fonction qui fusionne les morceaux entre quotes et hors quotes en un seul token WORD
void word_token(char *str, t_token **head, t_token **actual, int *i)
{
	char	buff[4096];
	int		j;
	char	q;

	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			q = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != q && j < 4095)
				buff[j++] = str[(*i)++];
			if (str[*i] == q)
				(*i)++;
		}
		else
			buff[j++] = str[(*i)++];
	}
	buff[j] = '\0';
	if (j > 0)
	{
		t_token *new = create_token(WORD, buff);
		add_token(head, actual, new);
	}
}
