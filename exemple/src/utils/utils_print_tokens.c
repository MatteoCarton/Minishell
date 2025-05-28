/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:15:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/21 16:43:23 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	print_token_list(t_token *token_list)
{
	t_token	*current;

	if (!token_list)
		return ;
	current = token_list;
	while (current != NULL)
	{
		if (current->type == 0)
			printf("Type : %u | Lexeme: end\n", current->type);
		else
			printf("Type : %u | Lexeme: %s\n", current->type, current->lexeme);
		current = current->next;
	}
}
