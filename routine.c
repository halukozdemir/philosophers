#include "philo.h"

void	routine(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= data->number_of_philo)
			i = 0;
		if (data->forks[i].is_use == false && data->forks[(i + 1) % data->number_of_philo].is_use == false)
		{
			pthread_mutex_lock(&data->forks[i].fork_mutex);
			pthread_mutex_lock(&data->forks[(i + 1) % data->number_of_philo].fork_mutex);
			data->forks[i].is_use = true;
			data->forks[(i + 1) % data->number_of_philo].is_use = true;
			printf("%d. filozof yemek yiyor \n", i);
			usleep(data->time_to_eat * 1000);
			data->forks[i].is_use = false;
			data->forks[(i + 1) % data->number_of_philo].is_use = false;
			pthread_mutex_unlock(&data->forks[i].fork_mutex);
			pthread_mutex_unlock(&data->forks[(i + 1) % data->number_of_philo].fork_mutex);
		}
		else
		{
			printf("%d. filo düşünüyor\n", i);
		}
		i++;
	}
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine, &data);
		i++;
	}
	i = 0;
	while(i < data->number_of_philo)
	{
		pthread_join(&data->philo[i].thread, NULL);//eşit değilse sıfıra kontrolü koy
		i++;
	}
}
