/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:05:06 by alama             #+#    #+#             */
/*   Updated: 2025/01/06 13:22:46 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_count_c(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_malloc_split(char **str, char const *s, char c)
{
	int	i;
	int	a;
	int	j;

	i = -1;
	a = 0;
	while (s[++i])
	{
		j = 0;
		while (s[i] != c && s[i])
		{
			i++;
			j++;
		}
		if (j != 0)
		{
			str[a] = malloc(sizeof(char) * (j + 1));
			if (!str[a])
				return (ft_free(str), 2);
			a++;
			i--;
		}
	}
	return (1);
}

static void	ft_add_split(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	a = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c && s[i])
		{
			str[a][j] = s[i];
			j++;
			i++;
		}
		if (j != 0)
		{
			str[a][j] = '\0';
			a++;
			i--;
		}
		i++;
	}
	str[a] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count_c;
	int		sp;

	if (!s)
		return (NULL);
	count_c = ft_count_c(s, c);
	str = malloc(sizeof(char *) * (count_c + 1));
	if (!str)
		return (NULL);
	sp = ft_malloc_split(str, s, c);
	if (sp > 1)
		return (0);
	ft_add_split(str, s, c);
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	int		i;
 	char	**str;
 	str = ft_split("\"coucou commetn ca va\"", ' ');
 	i = 0;
 	if (ft_split(NULL, '^') == NULL)
 		printf("NULL\n");
 	else
 	{
 		while (str[i])
 		{
 			printf("%s\n", str[i]);
 			i++;
 		}
 	}
 	// char** tabstr;
 	// int i = 0;
 	// if (!(tabstr = ft_split("lorem ipsum dolor ", 'z')))
 	// 	write(1, "flop\n", 5);
     //     // ft_print_result("NULL");
     // else
     // {
     //     while (tabstr[i] != NULL)
     //     {
 	// 		int j = 0;
     //         // ft_print_result(tabstr[i]);
     //         while (tabstr[i][j] != '\0') {	
 	// 			write(1, &tabstr[i][j], 1);
 	// 			j++;
 	// 		}
 	// 		printf("%d\n", j);
     //         i++;
     //     }
 	// 	write(1, "\n", 1);
     // }
}
*/
