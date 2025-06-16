#include "../../../inc/minishell.h"

void ft_pwd(void)
{
    char buffer[PATH_MAX];

    if (getcwd(buffer, PATH_MAX))
        printf("%s\n", buffer);
    else
        perror("minishell: pwd (getcwd)");
}
