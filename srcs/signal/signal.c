#include "../../inc/minishell.h"

/* Gestion du signal SIGINT (Ctrl+C) dans le shell principal */
static void handle_sigint(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_exitcode = 130;
}

/* Gestion du signal SIGINT dans les commandes */
static void handle_sigint_child(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    exit(130);
}

/* Configuration des signaux pour le shell principal */
void setup_shell_signals(void)
{
    signal(SIGINT, handle_sigint);    // Ctrl+C
    signal(SIGQUIT, SIG_IGN);         // Ctrl+ backslash 
    signal(SIGTSTP, SIG_IGN);         // Ctrl+Z
}

/* Configuration des signaux pour les processus enfants (les 
commandes (exemple pendant que on est dans un sleep 100)) */
// setup_child_signals() doit être appelé juste avant d'exécuter une commande (echo, ls, ...)
void setup_child_signals(void)
{
    signal(SIGINT, handle_sigint_child);
    signal(SIGQUIT, SIG_DFL);         // On laisse le comportement par défaut
    signal(SIGTSTP, SIG_DFL);         // On laisse le comportement par défaut
}