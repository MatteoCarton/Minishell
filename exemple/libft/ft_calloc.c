/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:20:12 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 20:46:39 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((size != 0 && ((count * size) / size != count)) || (size >= 2147483647
			&& count >= 2147483647))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// int main(void)
// {
// 	size_t count = 100000000;
// 	size_t size = 400000;
// 	ft_calloc(count, size);
// 	// char *str = calloc(count, size);
// 	return (0);
// }