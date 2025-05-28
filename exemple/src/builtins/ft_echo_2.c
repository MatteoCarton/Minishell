/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:47:14 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 14:50:33 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	ft_print_arg(char *arg)
{
	char	*arg_without_quotes;

	arg_without_quotes = ft_remove_quotes(arg);
	if (arg_without_quotes)
	{
		printf("%s", arg_without_quotes);
		free(arg_without_quotes);
		arg_without_quotes = NULL;
	}
	else
		printf("%s", arg);
}

void	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && ft_is_valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_print_arg(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
