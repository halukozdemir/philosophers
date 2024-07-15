#include "philo.h"

size_t	get_current_time()
{
	long long	current_time;

	struct timeval	tv;
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	init_time(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].start_time = &data->start_time;
		data->philo[i].time_of_last_meal = data->start_time;//bunlardan biri adres digeri neden farklı
		i++;
	}
}

void	custom_sleep_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_of_last_meal_mutex);
	while (get_current_time() - philo->time_of_last_meal < philo->time_to_eat)
		usleep(10);
	pthread_mutex_unlock(&philo->time_of_last_meal_mutex);

}

void	custom_sleep_sleeping(t_philosopher *philo, size_t time)
{
	while (get_current_time() - time < philo->time_to_sleep)
		usleep(10);
}
