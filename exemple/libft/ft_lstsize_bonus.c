/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:28 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:53:55 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	if (lst)
	{
		while (tmp->next != NULL)
		{
			i++;
			tmp = tmp->next;
		}
		i++;
	}
	return (i);
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list *elem = ft_lstnew("l1");
// 	t_list *elem2 = ft_lstnew("l2");
// 	t_list *elem3 = ft_lstnew("l3");

// 	elem->next = elem2;
// 	elem2->next = elem3;
// 	int	i = ft_lstsize(elem);
// 	printf("%d\n", i);
// }