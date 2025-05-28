/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:10:00 by alama             #+#    #+#             */
/*   Updated: 2024/09/25 19:50:20 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_l)
{
	if (!lst || !new_l)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new_l;
	else
		*lst = new_l;
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list *elem = NULL;
// 	t_list *elem2 = ft_lstnew_l("l1");
// 	t_list *elem3 = ft_lstnew_l("l2");
// 	t_list *elem4 = ft_lstnew_l("l3");
// 	ft_lstadd_back(&elem , elem2);
// 	ft_lstadd_back(&elem , elem3);
// 	ft_lstadd_back(&elem , elem4);
// 	while (elem->next != NULL)
// 	{
// 		printf("%s ", elem->content);
// 		elem = elem->next;
// 	}
// 	printf("%s", elem->content);
// }
