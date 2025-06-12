#include "../../../inc/minishell.h"

int	number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
