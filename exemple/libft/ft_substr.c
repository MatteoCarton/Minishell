/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:01 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:56:30 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (ft_strdup(""));
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && i < ft_strlen(s))
	{
		str[i] = ((char *)s)[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char const *s = "tripouille";
// 	char *str = ft_substr(s, 100, 1);
// 	char *str2 = ft_substr(s, 100, 1);
// 	printf("%s\n", str);
// }