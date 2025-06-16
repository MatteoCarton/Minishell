#include "../../../inc/minishell.h"

static void	update_env_var(char **env, const char *name, const char *value)
{
	size_t	i;
	size_t	len;
	char	*new_var;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			new_var = malloc(len + 1 + ft_strlen(value) + 1);
			if (!new_var)
				return ;
			ft_strlcpy(new_var, name, len + 1);
			new_var[len] = '=';
			ft_strlcpy(new_var + len + 1, value, ft_strlen(value) + 1);
			free(env[i]);
			env[i] = new_var;
			return ;
		}
		i++;
	}
}

char	*update_old_pwd_env(char **env)
{
	int		i;
	char	*old_pwd;

	old_pwd = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			old_pwd = env[i] + 4;
			break ;
		}
		i++;
	}
	if (old_pwd)
		update_env_var(env, "OLDPWD", old_pwd);
	return (old_pwd);
}

int	update_new_pwd_env(char **env, const char *old_pwd, const char *path)
{
	char *new_pwd;
	size_t total_len;

	if (path[0] == '/')
		new_pwd = ft_strdup(path);
	else if (old_pwd)
	{
		total_len = ft_strlen(old_pwd) + 1 + ft_strlen(path) + 1;
		new_pwd = malloc(total_len);
		if (!new_pwd)
			return (1);
		ft_strlcpy(new_pwd, old_pwd, total_len);
		ft_strlcat(new_pwd, "/", total_len);
		ft_strlcat(new_pwd, path, total_len);
	}
	else
		new_pwd = ft_strdup(path);
	if (!new_pwd)
		return (1);
	update_env_var(env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}
