#include "philo.h"

void	mutex_is_not_eating(t_philosopher *philo, int is_not_eating)
{
	pthread_mutex_lock(&philo->is_not_eating_mutex);
	philo->is_not_eating = is_not_eating;
	pthread_mutex_unlock(&philo->is_not_eating_mutex);
}

void	mutex_nbr_of_meals(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->nbr_of_meals_mutex);
	if (philo->nbr_of_meals != -1)
		philo->nbr_of_meals++;
	pthread_mutex_unlock(&philo->nbr_of_meals_mutex);
}

void	mutex_end(t_philosopher *philo, int value)
{
	pthread_mutex_lock(philo->end_mutex);
	*philo->end = value;
	pthread_mutex_unlock(philo->end_mutex);
}

int	end_is_true_data(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (0);
}

int	end_is_true_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->end_mutex);
	if (*philo->end == 1)
	{
		pthread_mutex_unlock(philo->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->end_mutex);
	return (0);
}
