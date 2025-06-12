#include "../../../inc/minishell.h"

static bool  is_n(char *arg)
{
    if (!arg || arg[0] != '-')
        return (false);
    arg++;
    if (*arg == '\0')
        return (false);
    while (*arg)
    {
        if (*arg != 'n')
            return (false);
        arg++;
    }
    return (true);
}

void ft_echo(char **args)
{
    int i;
    int n_or_not;

    i = 1;
    n_or_not = false;
    while (args[i] && is_n(args[i]))
    {
        n_or_not = true;
        i++;
    }

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }

    if (n_or_not == false)
        printf("\n");
}

// A AJOUTER ECHO le $