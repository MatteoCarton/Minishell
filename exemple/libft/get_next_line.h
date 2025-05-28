/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:31:27 by alama             #+#    #+#             */
/*   Updated: 2024/05/18 16:14:57 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_add_str_buffer_size(char *str, int fd);
int		ft_find_line(char *str);
char	*str_join(char *str, char *buffer, int rd);
int		ft_strlen(char *str);
char	*str_trim(char *str);
char	*next_line(char *str);
void	ft_free(char **str);
void	ft_free_twice(char *one, char *sec);

#endif