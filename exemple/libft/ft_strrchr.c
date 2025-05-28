/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:56:45 by alama             #+#    #+#             */
/*   Updated: 2024/04/16 17:00:25 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	c = (unsigned char)c;
	str = (char *)s;
	i = ft_strlen(str);
	if (c == 0 && s)
		return (&str[i]);
	if (!str && !c)
		return (str);
	while (i >= 0)
	{
		if (str[i] == c)
			return (&str[i]);
		i--;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str2 = "bonjour";
	char	*str = ft_strrchr(str2, 'b');
	printf("%s\n", str);
}
*/