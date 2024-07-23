#include "philo.h"
#include <errno.h>

void    dead_check(t_philo *philo)
{
    if (get_current_time() - philo->time_of_last_meal > philo->t_data->timo_to_die)
    {
        pthread_mutex_lock(philo->end_mutex);
        *philo->end = true;
        pthread_mutex_unlock(philo->end_mutex);
    }
}

void    thinking(t_philo *philo)
{
    dead_check(philo);
    ft_print(philo, "thinking");
}

void    sleeping(t_philo *philo)
{
    dead_check(philo);
    ft_print(philo, "sleeping");
    ft_usleep(philo->t_data->time_to_sleep);
}

void    eating(t_philo *philo)
{
    dead_check(philo);
    pthread_mutex_lock(philo->l_fork);
    ft_print(philo, "fork");
    pthread_mutex_lock(philo->r_fork);
    ft_print(philo, "fork");
    ft_print(philo, "eating");
    philo->time_of_last_meal = get_current_time() - philo->t_data->start_time;
    ft_usleep(philo->t_data->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}


void *routine(void *arg) {

    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        if (philo->id % 2 != 0)
        {
            thinking(philo);
            eating(philo);
            sleeping(philo);
        }
        else
        {
            eating(philo);
            sleeping(philo);
        }
    }
    ft_print(philo, "died");
    return NULL;
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
    data->start_time = get_current_time();
	while(i < data->number_of_philo)
	{
        data->philo[i].time_of_last_meal = get_current_time();
        printf("%zu*** \n", data->philo[i].time_of_last_meal);
		pthread_create(&data->philo[i].thread, NULL, routine, (void *)&data->philo[i]);
		i++;
	}
	i = 0;
	while(i < data->number_of_philo)
	{
		pthread_join(data->philo[i].thread, NULL);//eşit değilse sıfıra kontrolü koy
		i++;
	}
	return (EXIT_SUCCESS);
}
