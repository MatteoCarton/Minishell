/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:03:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 17:07:49 by mcarton          ###   ########.fr       */
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
	tot = strlen(s1) + strlen(s2) + 1;
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
		i = strlen(s);
	new_str = malloc(i + 2);
	if (!new_str)
		return (NULL);
	if (s)
		strlcpy(new_str, s, i + 1);
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

static int	len(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
		i++;
	if (nbr == 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		l;
	int		i;
	long	nbr;
	char	*result;

	nbr = n;
	l = len(nbr);
	i = l - 1;
	result = calloc(l + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		result[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	return (result);
}
