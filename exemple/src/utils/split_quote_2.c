/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:31:57 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/16 17:32:34 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	get_segment_length(const char *str, int i)
{
	int	l;

	l = 0;
	while (str[i + l] && str[i + l] != ' ')
	{
		if (str[i + l] == '\"' || str[i + l] == '\'')
			l += ft_handle_quote(str, i + l);
		else
		{
			while (str[i + l] && str[i + l] != '\'' && str[i + l] != '\"'
				&& str[i + l] != ' ')
				l++;
		}
	}
	return (l);
}

static void	extract_and_store(char ***split, const char *str, int *i, int *nb)
{
	int	l;

	l = get_segment_length(str, *i);
	(*split)[*nb] = ft_substr(str, *i, l);
	(*nb)++;
	*i += l;
	if (str[*i] == ' ')
		(*i)++;
}

void	ft_add_str(char ***split, const char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
		extract_and_store(split, str, &i, &nb);
}
