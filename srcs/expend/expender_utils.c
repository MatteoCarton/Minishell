/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:03:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:04:15 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_quotes_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && *in_double == 0)
	{
		if (*in_single == 0)
			*in_single = 1;
		else
			*in_single = 0;
	}
	else if (c == '"' && *in_single == 0)
	{
		if (*in_double == 0)
			*in_double = 1;
		else
			*in_double = 0;
	}
}

char	*join_str(char *s1, char *s2)
{
	size_t	tot;
	size_t	j;
	size_t	i;
	char	*ct;

	if (!s1 || !s2)
		return (NULL);
	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	ct = malloc(sizeof(char) * tot);
	if (!ct)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ct[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ct[j + i] = s2[j];
		j++;
	}
	ct[j + i] = '\0';
	return (free(s1), ct);
}

char	*join_char(char *s, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	if (s)
		i = ft_strlen(s);
	new_str = malloc(i + 2);
	if (!new_str)
		return (NULL);
	if (s)
		ft_strlcpy(new_str, s, i + 1);
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}
