/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:32:27 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:55:21 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src > dst)
		ft_memcpy(dst, src, len);
	else if (src < dst)
		while (len-- > 0)
			*(char *)(dst + len) = *(char *)(src + len);
	return (dst);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char dst[] = "caca";
// 	char src[] = "pipi";
// 	//memmove(dst, src, 2);
// 	//printf("%s\n", memmove(src + 2, src + 1, 2));
// 	//printf("%s\n", ft_memmove(src + 2, src + 1, 2));
// 	//printf("%s\n", ft_memmove(dst, src, 15));
// 	printf("%s\n", memmove(dst, src, 15));
// 	return (0);
// }