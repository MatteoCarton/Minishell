/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:12:20 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 13:42:06 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*list;

// 	list = ft_lstnew("coucou ca va ?");

// 	printf("%s\n", list->content);
// 	if (list->next == NULL)
// 		printf("next is null\n");
// 	return (0);
// }