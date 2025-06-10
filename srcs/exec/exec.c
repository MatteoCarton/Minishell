#include "../../inc/minishell.h"

int execute_builtin(t_command *cmd, t_shell *shell)
{
    (void)shell; // A SUPPRIMER
    
    /* if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
        return (ft_exit()); */
    if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        return (ft_echo(cmd->args), 1); 
    if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
        return (ft_pwd(), 1);
    /* if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        return (ft_cd());  */
    if (ft_strncmp(cmd->args[0], "env", 4) == 0)
        return (ft_env(shell->env), 1);
    /* if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
        return (ft_unset());
    if (ft_strncmp(cmd->args[0], "export", 6) == 0)
        return (ft_export()); */
    return 0;
}