/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:17:45 by alama             #+#    #+#             */
/*   Updated: 2024/08/02 15:10:23 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char)c;
	while (s && s[i])
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	*s = "";
// 	printf("%s\n", strchr(s, 0));
// 	printf("%s\n", ft_strchr(s, 0));
// }
