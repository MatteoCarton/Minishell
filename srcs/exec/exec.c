#include "../../inc/minishell.h"

int execute_builtin(t_command *cmd, t_shell *shell)
{
    (void)shell; // A SUPPRIMER
    
    if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
        return (ft_exit(cmd->args, shell), -1);
    if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        return (ft_echo(cmd->args), 1); 
    if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
        return (ft_pwd(), 1);
    /* if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        return (ft_cd());  */
    if (ft_strncmp(cmd->args[0], "env", 4) == 0)
        return (ft_env(shell->env), 1);
    /*if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
        return (unset_env(cmd->args, &shell->env, cmd->args[1], &shell->exit), 1);
   */if (ft_strncmp(cmd->args[0], "export", 7) == 0)
        return (export_env(cmd->args, &shell->env, cmd->args[1], &shell->exit), 1);
    return 0;
}