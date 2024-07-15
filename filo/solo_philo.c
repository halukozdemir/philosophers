#include "philo.h"

void	solo_philo(t_data *data)
{
	message(&data->philo[0], "is thinking");
	message(&data->philo[0], "has taken a fork");
	usleep(data->time_to_die * 1000);
	message(&data->philo[0], "died");

}
