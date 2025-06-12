#include "../../../inc/minishell.h"

void    remove_line(char ***env, int unset)//cree nouveau tableau on copie tout sauf unset puis on remplace
{
    int i;
    int j;
    int len;
    char **new;

    len = 0;
    i = 0;
    j = 0;
    while((*env)[len])
        len++;
    new = malloc(sizeof(char *) * len);
    if (!new)
        return ;
    while (i < len)
    {
        if (i != unset)
        {
            new[j] = ft_strdup((*env)[i]);
            j++;
        }
        i++;
    }
    new[j] = NULL;
    free_env(*env);
    *env = new;
}

int     get_line_unset(char **env, char *unset)//cherche l index a unset
{
    int i;
    int j;

    i = 0;
    j = ft_strlen(unset);
    while(env[i])
    {
        if (ft_strncmp(env[i], unset, j) == 0 && 
			(env[i][j] == '=' || env[i][j] == '\0'))
			return (i);
        i++;
    }
    return (-19);
}

void    unset_env(char **arg, char ***env, char *var_str, int *exit)
{
    int unset;
    *exit = 0;

    if (arg[1])
    {
        unset = get_line_unset(*env, var_str);
        if (unset == -19)
            return ;
        else
            remove_line(env, unset);
    }
}