#include "../../../inc/minishell.h"

static void	change_directory(char *arg1, t_shell *shell)
{
    char *old_pwd;

    old_pwd = update_old_pwd_env(shell->env);
	if (chdir(arg1) == -1)
	{
		perror("minishell: cd");
		shell->exit = 1;
		return ;
	}
    if (update_new_pwd_env(shell->env, old_pwd, arg1) == 1)
	{
		shell->exit = 1;
		return ;
	}
	shell->exit = 0;
}

void	ft_cd(char **args, t_shell *shell)
{
	char *home_path;
	if (number_of_args(args) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		shell->exit = 1;
		return ;
	}
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			shell->exit = 1;
			return ;
		}
		change_directory(home_path, shell);
	}
	else
        change_directory(args[1], shell);
}