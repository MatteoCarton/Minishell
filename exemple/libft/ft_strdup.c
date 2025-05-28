/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:56:40 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 16:33:17 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		len;

	len = ft_strlen(src);
	dest = (char *)malloc((sizeof(char)) * len + 1);
	if (!dest)
		return (0);
	i = -1;
	while (src[++i])
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char * s = ft_strdup((char*)"coucou");
// 	printf("%s\n", s);
// }