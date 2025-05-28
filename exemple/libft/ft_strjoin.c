/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:34:00 by alama             #+#    #+#             */
/*   Updated: 2024/10/17 17:59:11 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_join(char *s1, char const *s2, int m)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[m] = s2[i];
		i++;
		m++;
	}
	return (m);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (str);
	i = ft_join(str, s1, i);
	i = ft_join(str, s2, i);
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	const s1[] = "salut ";
	char	const s2[] = ", ca va ?";
	char	*str = ft_strjoin(s1, s2);
	printf("%s\n", str);
}
*/
