/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:43:23 by mcarton           #+#    #+#             */
/*   Updated: 2025/05/19 20:45:18 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd   *parse_cmd(char *line)
{
    t_cmd *cmd;
    int cmd_end;
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    
    cmd_end = copy_command(cmd, line);
    if (cmd_end == -1)
        return (NULL);
    if (!copy_arguments(cmd, line, cmd_end))
        return (NULL);
    
    return (cmd);
}