/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:24:21 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 14:47:34 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack && !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) haystack + i);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	//const char	*s = "lorem ipsum dolor sit amet";
// 	//const char	*a = "sit";
// 	//char haystack[30] = "fake";
// 	//char needle[10] = "";
// 	//char * empty = (char*)"";
// 	//char		*str = strnstr(haystack, ((void *)0), 3);
// 	char		*str2 = ft_strnstr("fake", 0, 3);
// 	//printf("%s\n", str);
// 	printf("%s\n", str2);
// }