#include "../inc/minishell.h"
#include <fcntl.h>
#include <stdio.h>

int g_exitcode = 0;

int is_only_spaces(char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\n')
            return (0);
        str++;
    }
    return (1);
}

char **cpy_env(char **envp)
{
    int i;
    char **env;

    i = 0;
    while(envp[i])
        i++;
    env = malloc(sizeof(char *) * (i + 1));
    if (!env)
        return(NULL);
    i = 0;
    while(envp[i])
    {
        env[i] = strdup(envp[i]);
        if (!env[i])
        {
            while (i-- > 0)
                free(env[i]);
            free(env);
            return (NULL);
        }
        i++;
    }
    env[i] = NULL;
    return(env);
}

static int start(char **line, t_shell *m)
{
    t_token *lexed;
    t_command *cmd;
    int result;

    if (!(**line))
        return (1);
    if (!check_quotes(*line))
        return (0);
    expand_dollar(line, *m);
    lexed = get_token(*line);
    if (lexed)
    {
        cmd = parse_tokens(lexed);
        if (cmd)
        {
            result = exec(cmd, m);
            free_command(cmd);
            if (result == -19)
            {
                free_token(&lexed);
                return (-19);
            }
        }
        else
            free_command(cmd);
        free_token(&lexed);
        return (1);
    }
    else
        return (0);
}

static int	init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return (0);
	shell->env = cpy_env(envp);
	if (!shell->env)
		return (0);
	setup_shell_signals();
	return (1);
}

static void	run_shell(t_shell *shell)
{
	char	*line;
	int		result;
	int		stdin_backup;
	int		current_stdin;

	result = 0;
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
	{
		perror("minishell");
		exit(1);
	}
	while (19)
	{
		current_stdin = dup(STDIN_FILENO);
		dup2(stdin_backup, STDIN_FILENO);
		line = readline("matteoshell$ ");
		dup2(current_stdin, STDIN_FILENO);
		close(current_stdin);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line && !is_only_spaces(line))
		{
			add_history(line);
			result = start(&line, shell);
			free(line);
			if (result == -19)
			{
				free_env(shell->env);
				rl_clear_history();
				close(stdin_backup);
				exit(g_exitcode);
			}
		}
		else
			free(line);
	}
	free_env(shell->env);
	rl_clear_history();
	close(stdin_backup);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		return (0);
	if (init_shell(&shell, envp) == 0)
		return (1);
	run_shell(&shell);
	return (g_exitcode);
}
