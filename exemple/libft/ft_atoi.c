/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:14:26 by alama             #+#    #+#             */
/*   Updated: 2025/01/02 20:15:51 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_max_long_long(int is_negatif, const char *str)
{
	int	i;
	int	zero;

	zero = 0;
	i = 0;
	while (str[i] == '0')
	{
		zero++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i - zero < 19)
		return (1);
	else if (is_negatif == -1)
		return (0);
	else
		return (-1);
}

static long long	ft_add(int i, const char *str)
{
	long long	value;

	value = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value *= 10;
		value += str[i] - '0';
		i++;
	}
	return (value);
}

int	ft_atoi(const char *str)
{
	long long	i;
	long long	is_negatif;
	long long	value;

	i = 0;
	is_negatif = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negatif = -1;
		i++;
	}
	if (ft_max_long_long(is_negatif, str + i) <= 0)
		return (ft_max_long_long(is_negatif, str + i));
	value = ft_add(i, str);
	return (value * is_negatif);
}

//  #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	(void) argc;
// 	char *str = argv[1];
// 	printf("%d\n",ft_atoi(str));
//  	printf("%d\n", atoi(str));
// 	return (0);
// }
