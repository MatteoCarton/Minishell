/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_itr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:28:24 by alama             #+#    #+#             */
/*   Updated: 2024/10/08 21:05:22 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_ITR_H
# define CHAR_ITR_H

# include "mini_shell.h"

typedef struct s_char_itr
{
	const char	*cursor;
	const char	*sentinel;
}				t_char_itr;

t_char_itr		charitr_value(const char *start, size_t length);
const char		*charitr_cursor(const t_char_itr *self);
int				charitr_has_next(const t_char_itr *self);
char			charitr_peek(const t_char_itr *self);
char			charitr_next(t_char_itr *self);

#endif
