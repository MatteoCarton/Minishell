#include "../../inc/minishell.h"

t_command *init_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);

    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = 0;
    cmd->next = NULL;

    return (cmd);
}

void add_argument(t_command *cmd, char *arg)
{
    size_t i;
    char **new_args;

    i = 0;
    while (cmd->args && cmd->args[i])
        i++;
    new_args = ft_calloc(sizeof(char *), i + 2); // +2 pour le nouvel arg et le NULL
    if (!new_args)
        return ;
    i = 0;
    while (cmd->args && cmd->args[i])
    {
        new_args[i] = ft_strdup(cmd->args[i]);
        if (!new_args[i])
        {
            while (--i >= 0)
                free(new_args[i]);
            free(new_args);
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
            return ;
        }
    free(cmd->args);
    cmd->args = new_args;
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
    if (current->type == IN)  // Pour <
    {
        cmd->input_file = ft_strdup(current->str); // on ecrit le nom du fichier
        if (!cmd->input_file)
            return (0);
    }
    else
    {
        cmd->output_file = ft_strdup(current->str);
        if (!cmd->output_file)
            return (0);
    }
    return (1);
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
    if (cmd->input_file)
        free(cmd->input_file);
    if (cmd->output_file)
        free(cmd->output_file);
    if (cmd->next)
        free_command(cmd->next);
    free(cmd);
}

t_command *parse_tokens(t_token *tokens)
{
    t_command *first_cmd = init_command();
    t_command *cmd = first_cmd;
    t_token *current = tokens;

    while (current)
    {
        if (current->type == WORD)
            handle_argument(cmd, current);
        else if (current->type == PIPE)
        {
            cmd = handle_pipe(cmd);
            if (!cmd)
            {
                free_command(first_cmd);
                return (NULL);
            }
        }
        else if (current->type == IN || current->type == OUT)
        {
            if (!handle_redirection(cmd, current))
            {
                free_command(first_cmd);
                return (NULL);
            }
        }
        current = current->next;
    }
    return (first_cmd);
}