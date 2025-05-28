/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:17:35 by alama             #+#    #+#             */
/*   Updated: 2025/01/05 21:44:24 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_trim(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_null(void)
{
	char	*trim_str;

	trim_str = malloc(sizeof(char) * 1);
	if (!trim_str)
		return (NULL);
	trim_str[0] = '\0';
	return (trim_str);
}

static void	ft_add(char **trim_str, int i, int j, const char *s1)
{
	int	k;

	k = 0;
	while (i <= j)
	{
		(*trim_str)[k] = s1[i];
		i++;
		k++;
	}
	(*trim_str)[k] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trim_str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!s1[0])
		return (ft_null());
	j = ft_strlen(s1) - 1;
	while (s1[j] == ' ')
		j--;
	while (s1[i] && ft_find_trim(set, s1[i]) == 1)
		i++;
	while (j > i && ft_find_trim(set, s1[j]) == 1)
		j--;
	trim_str = malloc(sizeof(char) * (j - i + 2));
	if (!trim_str)
		return (0);
	ft_add(&trim_str, i, j, s1);
	return (trim_str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*str = "";
// 	char	*set = "123";
// 	char	*s = ft_strtrim(str, set);
// 	printf("%s\n", s);
// }
