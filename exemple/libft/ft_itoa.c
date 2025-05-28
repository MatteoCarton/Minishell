/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:53:48 by alama             #+#    #+#             */
/*   Updated: 2024/04/17 22:23:06 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_str(long nb, long sign)
{
	char	*str;
	long	i;

	i = 0;
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1 + sign));
	if (!str)
		return (0);
	if (sign == 1)
	{
		str[i] = '-';
		i++;
	}
	if (nb == 0)
		str[0] = '0';
	str[i] = '\0';
	return (str);
}

static void	ft_reverse(char *str)
{
	long	i;
	long	j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	long	sign;
	long	nb;

	i = 0;
	nb = n;
	sign = 0;
	if (nb < 0)
	{
		nb *= -1;
		sign = 1;
	}
	str = ft_malloc_str(nb, sign);
	if (!str)
		return (NULL);
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	ft_reverse(str);
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n",ft_itoa(-2147483648));
	return (0);
}
*/