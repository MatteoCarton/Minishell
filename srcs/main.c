#include "../inc/minishell.h"

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

int start(char *line, t_shell *m)
{
    t_token *lexed;
    t_command *cmd;

    if (!(*line))
        return (1);
    if (!check_quotes(line))
        return (0);
    expand_dollar(&line, *m);
    lexed = get_token(line);
    if (lexed) // si pas d'erreur
    {
        cmd = parse_tokens(lexed);
        if (cmd)
        {
            // ici l'exec
            free_command(cmd);
        }
        free_token(&lexed);
        return (1);
    }
    else
        return (0);
}


int main(int argc, char **argv, char **envp)
{
    (void)argv;
    char *line;
    t_shell m;
    
    if (argc != 1)
        return (0);
    m.env = cpy_env(envp);
    //setup_shell_signals();
    while (19)
    {
        line = readline("matteoshell$ ");
        if (!line) // si on CTRL+D (car ca renvoie NULL)
        {
            printf("exit\n");
            break ;
        }
        if (*line && !is_only_spaces(line))
        {
            add_history(line);
            start(line, &m);
        }
    }
    free_env(m.env);
    rl_clear_history(); 
    return (0);
}