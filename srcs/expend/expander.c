#include "../inc/minishell.h"

char	*find_env_value(char **env, char *var)
{
	int		i;
	int		len;

	if (!env || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char *get_var_name(char *str)
{
    int i = 1;
    int len = 0;
    int j = 0;
    char *name;
    
    if (!str || str[0] != '$')
        return (NULL);
    // Calculer longueur du nom de variable
    while (str[i + len] && (isalnum(str[i + len]) || str[i + len] == '_'))
        len++;
    if (len == 0)
        return (NULL);
    name = malloc(sizeof(char) * (len + 1));
    if (!name)
        return (NULL);
    // Copier le nom
    while (j < len)
    {
        name[j] = str[i + j];
        j++;
    }
    name[len] = '\0';
    return (name);
}

char	*handle_env_var(char **str, t_shell g_env, int *i)
{
	char	*var_name;
	char	*env_value;
	char	*to_add;

	var_name = get_var_name(&(*str)[*i]);
	if (var_name)
	{
		env_value = find_env_value(g_env.env, var_name);
		if (!env_value)
			to_add = strdup("");
		else
			to_add = strdup(env_value);
		*i += strlen(var_name);
		free(var_name);
	}
	else
		to_add = strdup("$");
	return (to_add);
}

char	*get_replacement_value(char **str, t_shell g_env, int *i)
{
	char	*to_add;

	if (!(*str)[*i + 1] || (*str)[*i + 1] == ' ')
		to_add = strdup("$");
	else if ((*str)[*i + 1] == '?')
	{
		to_add = ft_itoa(g_exitcode);
		(*i)++;
	}
	else
		to_add = handle_env_var(str, g_env, i);
	return (to_add);
}

void	replace_dollar(char **str, char **new_str, t_shell g_env, int *i)
{
	char	*to_add;

	to_add = get_replacement_value(str, g_env, i);
	*new_str = join_str(*new_str, to_add);
	free(to_add);
}

int joignable(char **str, char **new_str, t_shell g_env, int *i, int in_single)
{
    if ((*str)[*i] != '$')
        return (0);
    if (in_single)
        return (0);
    if ((*str)[*i + 1])
    {
        replace_dollar(str, new_str, g_env, i);
        (*i)++;
        return (1);
    }
    return (0);
}

int	process_char(char **str, char **new_str, t_shell g_env, int *i, int in_single)
{
	char	*tmp;

	if (!joignable(str, new_str, g_env, i, in_single))
	{
		tmp = join_char(*new_str, (*str)[*i]);
		if (!tmp)
		{
			free(*new_str);
			*str = NULL;
			return (0);
		}
		free(*new_str);
		*new_str = tmp;
		(*i)++;
	}
	return (1);
}

void	expand_dollar(char **str, t_shell g_env)
{
	char	*new_str;
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	if (!str || !*str)
		return ;
	new_str = strdup("");
	if (!new_str)
	{
		*str = NULL;
		return ;
	}
	while ((*str)[i])
	{
		update_quotes_state((*str)[i], &in_single, &in_double);
		if (!process_char(str, &new_str, g_env, &i, in_single))
			return ;
	}
	*str = new_str;
}
