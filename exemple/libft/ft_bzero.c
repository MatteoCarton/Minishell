/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:05:41 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 14:14:24 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>
// int	main (void)
// {
// 	int	i;
// 	i = 5;
// 	char str[] = "salut ca va ?";
// 	//bzero(str, 50);
// 	//printf("%s\n", str);
// 	i = 5;
// 	ft_bzero(str, 50);
// 	printf("%s\n", str);
// 	return (0);
// }