#include "../../inc/minishell.h"

static int count_pipes(t_command *cmd)
{
    int i;
    t_command *current;
    
    i = 0;
    current = cmd;
    while (current && current->next)
    {
        i++;
        current = current->next;
    }
    return (i);
}

static void execute_child_pipe(t_command *cmd, int *pipes, int index, int n_pipes, t_shell *shell)
{
    int i;
    char *path;

    i = 0;
        setup_child_signals();
    if (index > 0) // pas la premier du pipe, 
        dup2(pipes[(index - 1) * 2], STDIN_FILENO);
    if (index < n_pipes) // redirection output vers le pipe suivant
        dup2(pipes[index * 2 + 1], STDOUT_FILENO);

    // puis les redirections a la fin pour qu'elles ecrasent les pipes si necessaire
    // du coup si ya "cmd > file.txt | wc -l", le > file.txt va ecraser la sortie vers le pipe
    exec_redirections(cmd);

    while (i < n_pipes * 2)
    {
        close(pipes[i]);
        i++;
    }

    if (is_builtin(cmd->args[0])) // check builtin
    {
        g_exitcode = execute_builtin(cmd, shell);
        exit(g_exitcode);
    }
    path = get_exec_path(cmd->args[0], shell->env);
    if (!path)
    {
        g_exitcode = 127;
        exit(127);
    }
    execve(path, cmd->args, shell->env); // fonction sys POSIX qui switch processus courant par un autre programme
    perror("minishell: execve"); // message erreur basé sur la dernière erreur système
    free(path);
    exit(EXIT_FAILURE);
}

static void wait_all_children(int n_cmd)
{
    int status;
    int i = 0;
    
    while (i < n_cmd)
    {
        if (wait(&status) > 0)
        {
            if (WIFEXITED(status))
                g_exitcode = WEXITSTATUS(status);
            else
                g_exitcode = 1;
        }
        i++;
    }
}

static int init_pipe_data(t_command *cmd, int **pipes, int *n_pipes, int *n_cmd)
{
    int i;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);
    i = 0;
    *n_pipes = count_pipes(cmd);
    *n_cmd = *n_pipes + 1;
    *pipes = malloc(sizeof(int) * (*n_pipes) * 2);
    if (!*pipes)
    {
        perror("minishell: malloc");
        g_exitcode = 1;
        return (1);
    }
    while (i < *n_pipes)
    {
        if (pipe(&(*pipes)[i * 2]) == -1) // pour chaque pipe read end et write end qui sont des descripteurs
        {
            perror("minishell: pipe");
            g_exitcode = 1;
            return (free(*pipes), 1);
        }
        i++;
    }
    return (0);
}

static int fork_children(t_command *cmd, int *pipes, int n_pipes, t_shell *shell)
{
    int i = 0;
    pid_t pid;
    t_command *current = cmd;

    while (current)
    {
        pid = fork(); // return un int qui permet de savoir dans quel process on est genre child ou parent
        if (pid < 0)
        {
            perror("minishell: fork");
            g_exitcode = 1;
            free(pipes);
            return (1);
        }
        if (pid == 0) // on est dans process enfant
            execute_child_pipe(current, pipes, i, n_pipes, shell);
        current = current->next; // parcour chaque cmd comme ça
        i++;
    }
    return (0);
}

int exec_pipe(t_command *cmd, t_shell *shell)
{
    int *pipes;
    int n_pipes;
    int n_cmd;
    int i;

    i = 0;
    if (init_pipe_data(cmd, &pipes, &n_pipes, &n_cmd) == 1)
        return (1);
    if (fork_children(cmd, pipes, n_pipes, shell) == 1)
        return (1);
    while (i < n_pipes * 2) // ferme descripteurs dans le processus parent après avoir lancé les enfants
        close(pipes[i++]);
    wait_all_children(n_cmd); // attend la fin de tous les processus enfant
    free(pipes);
    return (g_exitcode);
}

