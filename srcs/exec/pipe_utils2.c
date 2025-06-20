/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:44:30 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 02:44:36 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_last_status(int status, int *last_status)
{
	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_status = 128 + WTERMSIG(status);
}
