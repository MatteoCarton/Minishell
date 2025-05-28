/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:15:29 by alama             #+#    #+#             */
/*   Updated: 2024/04/19 17:11:40 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ldest;
	size_t	lsrc;

	i = 0;
	j = 0;
	ldest = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (ldest < size && size > 0)
	{
		i = ldest;
		while (j < lsrc && src[j] && ldest + j < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	if (ldest >= size)
		ldest = size;
	return (ldest + lsrc);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char first[] = "This is a";
    char last[] = " potentially long string";
    int r;
    char buffer[10];

    strcpy(buffer,first);
    r = ft_strlcat(buffer,last, 10);
	printf("%s\n", buffer);
	printf("%d\n", r);
    r = strlcat(buffer,last, 10);
	printf("%s\n", buffer);
	printf("%d\n", r);
	return 0;
}
*/
