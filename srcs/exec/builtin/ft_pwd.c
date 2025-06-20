/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:54:52 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 15:47:58 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_pwd(void)
{
	char	*pwd_env;
	char	buffer[PATH_MAX];
	size_t	len_env;
	size_t	len_buf;
	size_t	max_len;

	pwd_env = getenv("PWD");
	if (pwd_env && getcwd(buffer, PATH_MAX))
	{
		len_env = ft_strlen(pwd_env);
		len_buf = ft_strlen(buffer);
		max_len = len_env > len_buf ? len_env : len_buf;
		if (ft_strncmp(pwd_env, buffer, max_len) == 0)
			printf("%s\n", pwd_env);
		else
			printf("%s\n", buffer);
	}
	else if (getcwd(buffer, PATH_MAX))
		printf("%s\n", buffer);
	else
		perror("matteoshell: pwd (getcwd)");
}
