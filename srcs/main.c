#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    char *line;
    
    if (argc != 1)
        return (0);

    setup_shell_signals();
    while (19)
    {
        line = readline("matteoshell$ ");
        if (!line) // si on CTRL+D (car ca renvoie NULL)
        {
            printf("exit\n");
            break ;
        }
        if (check_line(line))
            break;
        add_history(line);
        if (!start(line))
        free(line);
    }
    return (g_excode);
}