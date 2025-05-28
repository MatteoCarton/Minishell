/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:57:38 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 16:47:54 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	c = (unsigned char) c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == c)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	*s = "gether";
// 	//printf("%s\n", ft_memchr(NULL, 0, 0));	
// 	printf("%s\n", memchr(0, 0, 0));	
// }