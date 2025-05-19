/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:43:23 by mcarton           #+#    #+#             */
/*   Updated: 2025/05/19 19:48:26 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd   *parse_cmd(char *line)
{
    t_cmd *cmd;
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    
    if (!copy_command(cmd, line))
        return (NULL);
    if (!copy_arguments(cmd, line))
        return (NULL);
    
    return (cmd);
}