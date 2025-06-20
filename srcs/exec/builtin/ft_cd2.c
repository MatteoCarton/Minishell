/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 18:36:38 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	free_components(char **components)
{
	int	i;

	i = 0;
	if (!components)
		return ;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

static void	ft_lstclear_one_rev(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	current = *lst;
	if (!current->next)
	{
		ft_lstdelone(current, del);
		*lst = NULL;
		return ;
	}
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	ft_lstdelone(current, del);
}

void	fill_path_list(t_list **path_list, char **components)
{
	int		i;
	size_t	len;

	i = 0;
	while (components[i])
	{
		len = ft_strlen(components[i]);
		if (len == 2 && ft_strncmp(components[i], "..", 2) == 0)
			ft_lstclear_one_rev(path_list, free);
		else if (len == 1 && ft_strncmp(components[i], ".", 1) == 0)
			;
		else if (*components[i])
			ft_lstadd_back(path_list, ft_lstnew(ft_strdup(components[i])));
		i++;
	}
}

static size_t	calculate_path_len(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len += ft_strlen(lst->content);
		if (lst->next)
			len++;
		lst = lst->next;
	}
	return (len);
}

char	*ft_lst_to_path(t_list *lst)
{
	char	*path;
	size_t	len;
	t_list	*tmp;

	if (!lst)
		return (ft_strdup("/"));
	len = calculate_path_len(lst);
	path = malloc(sizeof(char) * (len + 2));
	if (!path)
		return (NULL);
	tmp = lst;
	path[0] = '/';
	path[1] = '\0';
	while (tmp)
	{
		ft_strlcat(path, tmp->content, len + 2);
		if (tmp->next)
			ft_strlcat(path, "/", len + 2);
		tmp = tmp->next;
	}
	return (path);
}
