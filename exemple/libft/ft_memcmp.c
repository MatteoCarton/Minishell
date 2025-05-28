/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:59:48 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:55:08 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	n--;
	while (0 < n && t_s1[i] == t_s2[i])
	{
		i++;
		n--;
	}
	return ((unsigned char)t_s1[i] - (unsigned char)t_s2[i]);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};
// 	printf("%d\n", ft_memcmp(s2, 0, 1));
// 	//printf("%d\n", memcmp(s2, 0, 1));
// }