#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int argv_check(char **argv)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]))
				return 0;
			i++;
		}
		j++;
		i = 0;
	}
	return 1;
}
