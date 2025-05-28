/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:39:29 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:55:17 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	//int	i = 1;
// 	char src[3] = "";
// 	char dst[5] = "";
// 	//int	m[4] = {250, 80, 4 ,8};
// 	//int	m2[4] = {65535, 8, 4 ,8};
// 	ft_memcpy(dst, src, 2);
// 	//printf("%s\n", dst);
// 	//ft_memcpy(m, m2, 2);
// 	//printf("%d\n", m[0]);
// 	//printf("%d\n", m[1]);
// 	//printf("%d\n", m[2]);
// 	//printf("%d\n", m[3]);
// 	//ft_memcpy(m, m2, 5);
// 	return (0);
// }
