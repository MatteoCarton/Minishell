#include "../../../inc/minishell.h"

void    add_env_var(char ***env, char *str)
{
    int i;
    int j;
    char **new;

    i = 0;
    j = 0;
    if (!check_line(env, str))
        return ;
    while ((*env)[i])
        i++;
    new = malloc(sizeof(char *) * (i + 2));
    if (!new)
        return ;
    while (j < i)
    {
        new[j] = ft_strdup((*env)[j]);
        j++;
    }
    new[j] = ft_strdup(str);
    new[j + 1] = NULL;
    free_env(*env);
    *env = new;
}

int valid_env(char *str)//check pas trop de = et les char
{
    int i;
    int equal;

    i = 0;
    equal = 0;
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    while(str[i])
    {
        if (str[i] == '=')
        {
            equal++;
            if (equal > 1)
                return (0);
        }
        else if (!(ft_isalnum(str[i]) 
            || ft_strchr(EXTRA_CHAR, str[i]) == 0))
            return (0);
        i++;
    }
    return (1);
}

void    all_export(char ***env)
{
    int i;
    int j;
    char **output;
    char *quoted;

    i = 0;
    j = 0;
    while((*env)[i])
        i++;
    output = malloc(sizeof(char *) * (i + 1));
    if (!output)
        return;
    while(j < i)
    {
        quoted = get_quoted((*env)[j]);
        if (!quoted)
            output[j] = NULL;
        else
        {
            output[j] = ft_strjoin("declare -x ", quoted);
            free(quoted);
        }
        j++;
    }
    output[j] = NULL;
    show_env(output);
    free(output);
}

void    export_env(char **arg, char ***env, char *var_str, int *exit)
{
    int check;

    check = 0;
    if (arg[1])
    {
        check = valid_env(var_str);
        if (!check)
        {
            *exit = 1;
            printf("minishell: export: '%s' : not a valid identifier\n", var_str);
            return ;
        }
        if(var_str)
        {
            add_env_var(env, var_str);
            *exit = 0;
        }
    }
    else
    {
        all_export(env);
        return ;
    }
}