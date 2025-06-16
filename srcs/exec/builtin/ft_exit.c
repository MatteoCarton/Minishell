#include "../../../inc/minishell.h"
#include <limits.h>

static bool	handle_sign(const char *str, int *i)
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

static bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	overflow_or_not(long long result, int digit, bool plus_sign,
		const char *str)
{
	if (plus_sign)
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& digit > LLONG_MAX % 10))
		{
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (1);
		}
	}
	else
	{
		if ((unsigned long long)result > (unsigned long long)LLONG_MAX / 10
			|| ((unsigned long long)result == (unsigned long long)LLONG_MAX / 10
				&& (unsigned long long)digit > ((unsigned long long)LLONG_MAX
					% 10 + 1)))
		{
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (1);
		}
	}
	return (0);
}

static int	ft_atoi_with_overflow(const char *str)
{
	int			i;
	bool		plus_sign;
	long long	result;

	i = 0;
	result = 0;
	plus_sign = handle_sign(str, &i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (overflow_or_not(result, str[i] - '0', plus_sign, str))
			exit(2);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (plus_sign)
		return (result);
	return (-result);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	code;

	printf("exit\n");
	if (!args || number_of_args(args) == 1)
	{
		g_exitcode = shell->exit;
		return (1);
	}
	if (!is_numeric(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		g_exitcode = 2;
		return (1);
	}
	if (number_of_args(args) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit = 1;
		g_exitcode = 1;
		return (0);
	}
	code = ft_atoi_with_overflow(args[1]);
	g_exitcode = (unsigned char)code;
	return (1);
}
