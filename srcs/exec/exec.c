#include "../../inc/minishell.h"

int execute_builtin(t_command *cmd, t_shell *shell)
{
    if (ft_strcmp(cmd->args[0], "exit") == 0)
        return (ft_exit());
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        return (ft_echo());
    if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return (ft_pwd());
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        return (ft_cd());
    if (ft_strcmp(cmd->args[0], "env") == 0)
        return (ft_env());
    if (ft_strcmp(cmd->args[0], "unset") == 0)
        return (ft_unset());
    if (ft_strcmp(cmd->args[0], "export") == 0)
        return (ft_export());
    return 0;
}