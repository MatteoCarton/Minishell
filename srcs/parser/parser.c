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
        i++;
    }
    new_args[i] = ft_strdup(arg);
    free(cmd->args);
    cmd->args = new_args;
}


t_command *parse_tokens(t_token *tokens)
{
    t_command *cmd = init_command();
    
    // Parcourir les tokens
    // Pour chaque token :
    // - Si c'est un argument -> add_argument
    // - Si c'est une redirection -> handle_redirection
    // - Si c'est un pipe -> handle_pipe
}