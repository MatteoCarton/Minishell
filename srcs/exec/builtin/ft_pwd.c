#include "../../../inc/minishell.h"

int ft_pwd(void)
{
    char buffer[PATH_MAX];

    if (getcwd(buffer, PATH_MAX))
        return (printf("%s\n", buffer), 0);
    else
        return (perror("minishell: pwd (getcwd)"), 1);
}