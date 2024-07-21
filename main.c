#include "philo.h"

int	argv_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while(argv[i])
	{
		while(argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}


int main(int argc, char **argv)
{
	t_data	*data;
	if(((argc < 5 || argc > 6) || !argv_check(argv)) && printf("%s", ERR_ARG))
		return (EXIT_FAILURE);
	if (init_all(data, argc, argv) && printf("%s", ERR_INIT))
		return (EXIT_FAILURE);
	philo_start(data);
}
