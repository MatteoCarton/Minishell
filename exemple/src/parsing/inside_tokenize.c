/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:24:19 by alama             #+#    #+#             */
/*   Updated: 2025/01/17 13:27:27 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*inside_tokenize(int *i, char *str, t_token *tok)
{
	t_token	*token_list;
	char	*set_malloc;

	token_list = tok;
	if ((which_token(i, str, &token_list)) == -1)
		return (ft_free_token(&token_list), NULL);
	if (str[*i] == '<' && str[*i + 1] != '<')
	{
		set_malloc = ft_strdup("<");
		ft_add_token(&token_list, I_DIR, set_malloc);
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		set_malloc = ft_strdup("<<");
		ft_add_token(&token_list, DI_DIR, set_malloc);
		(*i)++;
	}
	else if (ft_is_lexeme(str[*i]) == 0)
		*i = ft_str_to_lexeme(*i, str, &token_list, 1);
	if (str[*i] != '\0')
		(*i)++;
	return (token_list);
}

int	handle_invalid_token(int c)
{
	ft_not_close(c);
	return (-1);
}
