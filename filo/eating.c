#include "philo.h"

int	everyone_ate(t_data *data) //bakılacak
{
	int	i;

	if (data->nbr_of_times_eat == -1)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].nbr_of_meals_mutex);
		if (data->philo[i].nbr_of_meals < data->nbr_of_times_eat)
		{
			pthread_mutex_unlock(&data->philo[i].nbr_of_meals_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].nbr_of_meals_mutex);
		i++;
	}
	return (1);
}

int	sleeping(t_philosopher *philo)
{
	size_t	time;

	time = get_current_time();
	message(philo, "is sleeping");
	custom_sleep_sleeping(philo, time);
	return (EXIT_SUCCESS);
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		message(philo, "has taken a fork");
	}
}

int	eating(void	*philo_ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_ptr;
	if (end_is_true_philo(philo) == 1)
		return(EXIT_SUCCESS);
	take_forks(philo);
	pthread_mutex_lock(&philo->time_of_last_meal_mutex);
	philo->time_of_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->time_of_last_meal_mutex);
	mutex_is_not_eating(philo, 0);
	message(philo, "is eating");
	custom_sleep_eating(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	mutex_nbr_of_meals(philo);
	mutex_is_not_eating(philo, 1);
	return (EXIT_SUCCESS);
}
