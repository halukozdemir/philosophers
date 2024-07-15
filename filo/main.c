#include "philo.h"

int main (int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (ft_init(&data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data.number_of_philo == 1)
		solo_philo(&data);
	else if(philosophers(&data) == EXIT_FAILURE)
	{
		printf("Error: simulation failed.\n");
		return (EXIT_FAILURE);
	}
	ft_close(&data);
	return (EXIT_SUCCESS);
}
