/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:52:02 by alama             #+#    #+#             */
/*   Updated: 2024/05/22 15:06:08 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

void	ft_free_twice(char *one, char *sec)
{
	ft_free(&one);
	ft_free(&sec);
}

char	*ft_add_str_buffer_size(char *str, int fd)
{
	char	*buffer;
	int		rd;

	while (str != NULL && ft_find_line(str) == -1)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (ft_free(&str), NULL);
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (ft_free_twice(str, buffer), NULL);
		if (rd == 0)
			break ;
		buffer[rd] = '\0';
		str = str_join(str, buffer, rd);
	}
	if (rd == 0)
		ft_free(&buffer);
	return (str);
}

char	*str_trim(char *str)
{
	char	*buffer;
	int		i;
	int		tmp;

	tmp = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[tmp] != '\n' && str[tmp] != '\0')
		tmp++;
	if (str[tmp] == '\n')
		buffer = malloc(sizeof(char) * (tmp + 2));
	else
		buffer = malloc(sizeof(char) * (tmp + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < tmp)
	{
		buffer[i] = str[i];
		i++;
	}
	if (str[tmp] == '\n')
		buffer[i++] = '\n';
	buffer[i] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*str[LIMIT_FD];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647
		|| read(fd, 0, 0) < 0 || LIMIT_FD > OPEN_MAX)
		return (ft_free(&(str[fd])), NULL);
	if (str[fd] == NULL)
	{
		str[fd] = malloc(sizeof(char) * 1);
		if (!str[fd])
			return (NULL);
		str[fd][0] = '\0';
	}
	str[fd] = ft_add_str_buffer_size(str[fd], fd);
	if (!str[fd])
		return (NULL);
	buffer = str_trim(str[fd]);
	str[fd] = next_line(str[fd]);
	if (ft_find_line(buffer) == -1)
		ft_free(&str[fd]);
	return (buffer);
}
