#include "reminder_exe.h"

int	count_elements(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i]);
	return (i);
}

static int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '+' || c == ' ')
		return (1);
	else
		return (0);
}

int	check_char_strs(char **s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if ((j != 0 && s[i][j] == '-') || \
			(s[i][j] == '-' && (s[i][j + 1] < '0' || s[i][j + 1] > '9')) \
			|| (s[i][j] == '+' && (s[i][j + 1] < '0' || s[i][j + 1] > '9')) \
			|| (j != 0 && s[i][j] == '+') || !ft_isdigit(s[i][j]))
				return (0);
		}
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	sign = 1;
	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

