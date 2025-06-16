#include "../../inc/minishell.h"

static t_redirection *add_redirection(t_redirection **redirection_list, t_token_type type, char *filename)
{
    t_redirection *new;
    t_redirection *tmp;

    new = malloc(sizeof(t_redirection));
    if (!new)
        return (NULL);
    new->type = type;
    new->filename = ft_strdup(filename);
    new->heredoc_fd = -1;
    new->next = NULL;
    if (!*redirection_list)
        *redirection_list = new;
    else
    {
        tmp = *redirection_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (new);
}

t_command *init_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->redirection = NULL;
    cmd->next = NULL;
    return (cmd);
}

void add_argument(t_command *cmd, char *arg)
{
    int i;
    char **new_args;
    int j;

    i = 0;
    while (cmd->args && cmd->args[i])
        i++;
    new_args = ft_calloc(sizeof(char *), i + 2); // +2 pour le nouvel arg et le NULL
    if (!new_args)
    {
        free_command(cmd);
        return ;
    }
    i = 0;
    while (cmd->args && cmd->args[i])
    {
        new_args[i] = ft_strdup(cmd->args[i]);
        if (!new_args[i])
        {
            while (--i >= 0)
                free(new_args[i]);
            free(new_args);
            free_command(cmd);
            return ;
        }
        i++;
    }
    new_args[i] = ft_strdup(arg);
    if (!new_args[i])
    {
        while (--i >= 0)
            free(new_args[i]);
        free(new_args);
        free_command(cmd);
        return ;
    }
    j = 0;
    if (cmd->args)
    {
        while (cmd->args[j])
        {
            free(cmd->args[j]);
            j++;
        }
        free(cmd->args);
    }
    cmd->args = new_args;
}

void free_redirections(t_redirection *redir)
{
    t_redirection *tmp;
    while (redir)
    {
        tmp = redir->next;
        if (redir->filename)
            free(redir->filename);
        free(redir);
        redir = tmp;
    }
}

void free_command(t_command *cmd)
{
    int i;
    if (!cmd)
        return ;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    if (cmd->redirection)
        free_redirections(cmd->redirection);
    if (cmd->next)
        free_command(cmd->next);
    free(cmd);
}

void handle_argument(t_command *cmd, t_token *current)
{
    add_argument(cmd, current->str);
}

t_command *handle_pipe(t_command *cmd)
{
    cmd->next = init_command();
    if (!cmd->next)
        return (NULL);
    cmd = cmd->next;
    return (cmd);
}

int handle_redirection(t_command *cmd, t_token *current)
{
    t_token *next = current->next;
    if (!next || next->type != WORD)
        return (0);
    if (!add_redirection(&cmd->redirection, current->type, next->str))
        return (0);
    return (1);
}

t_command *parse_tokens(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    // Erreur : pipe en début de ligne
    if (tokens->type == PIPE)
    {
        write(2, "minishell: syntax error\n", 24);
        return (NULL);
    }

    t_command *first_cmd = init_command();
    t_command *cmd = first_cmd;
    t_token *current = tokens;
    while (current)
    {
        if (current->type == WORD)
            handle_argument(cmd, current);
        else if (current->type == PIPE)
        {
            // Erreur : pipe à la fin ou double pipe
            if (!current->next || current->next->type == PIPE)
            {
                write(2, "minishell: syntax error\n", 24);
                free_command(first_cmd);
                return (NULL);
            }
            cmd = handle_pipe(cmd);
            if (!cmd)
            {
                free_command(first_cmd);
                return (NULL);
            }
        }
        else if (current->type == IN || current->type == OUT || 
                 current->type == APPEND || current->type == HEREDOC)
        {
            if (!handle_redirection(cmd, current))
            {
                free_command(first_cmd);
                return (NULL);
            }
            current = current->next;
        }
        current = current->next;
    }
    return (first_cmd);
}
