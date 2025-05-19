/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:44:36 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/19 20:27:25 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    char *line;
    t_cmd *cmd;
    
    while (19)
    {
        line = readline("matteoshell$ ");
        if (!line) // si on CTRL+D (car ca renvoie NULL)
            break ;
        if (*line) // si elle est pas vide
        {
            add_history(line);
            cmd = parse_cmd(line);
            if (cmd)
            {
                // TODO: executer la commande
                
                // DEBUG
                printf("Commande: %s\n", cmd->cmd);
                for (int i = 0; i < cmd->argc; i++)
                    printf("Arg %d: %s\n", i, cmd->args[i]);
        
                // TODO: free la structure cmd
            }
        }
        free(line);
    }
    return (0);
}