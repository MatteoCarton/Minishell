/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:54:52 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 16:36:28 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = find_env_value(shell->env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("matteoshell: pwd");
}
