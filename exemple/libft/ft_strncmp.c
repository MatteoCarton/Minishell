/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:06:17 by alama             #+#    #+#             */
/*   Updated: 2024/08/12 12:43:49 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char*s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n--;
	while ((s1[i] && s2[i]) && 0 < n && s1[i] == s2[i])
	{
		i++;
		n--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1 = "-2147483648";
	char	*s2 = "-2147483648";
	int	i = ft_strncmp(s1, s2, 11);
	printf("%d\n", i);
	i = strncmp(s1, s2, 11);
	printf("%d\n", i);
}
*/
