/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:57:28 by alama             #+#    #+#             */
/*   Updated: 2024/04/17 18:11:31 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lenght_src;

	i = 0;
	lenght_src = ft_strlen(src);
	if (size > 0)
	{
		while (size - 1 > i && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (lenght_src);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dst[15];
	ft_strlcpy(dst, "", 15);
	printf("%s\n", dst);
}
*/