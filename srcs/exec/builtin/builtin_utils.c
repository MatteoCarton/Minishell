#include "../../../inc/minishell.h"

bool	handle_sign(const char *str, int *i)
{
	bool	plus_sign;

	plus_sign = true;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			plus_sign = false;
		(*i)++;
	}
	return (plus_sign);
}

