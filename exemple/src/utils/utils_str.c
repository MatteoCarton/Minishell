/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:10:42 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 12:45:45 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len] && len < n)
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

char	*ft_strdel(char *str, const char *del)
{
	char	*new_str;
	size_t	del_len;

	if (!str || !del)
		return (str);
	del_len = ft_strlen(del);
	if (ft_strncmp(str, del, del_len) == 0)
	{
		new_str = ft_strdup(str + del_len);
		return (new_str);
	}
	return (str);
}
