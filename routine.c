#include "philo.h"
#include <errno.h>

int    dead_check(t_philo *philo)
{
    if (get_current_time() - philo->time_of_last_meal > philo->t_data->timo_to_die)
    {
        printf("---%lu----\n", get_current_time() - philo->time_of_last_meal);
        pthread_mutex_lock(philo->end_mutex);
        *philo->end = true;
        pthread_mutex_unlock(philo->end_mutex);
        ft_print(philo, "died");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void    thinking(t_philo *philo)
{
    //dead_check(philo);
    ft_print(philo, "thinking");
}

void    sleeping(t_philo *philo)
{
    //dead_check(philo);
    ft_print(philo, "sleeping");
    ft_usleep(philo->t_data->time_to_sleep);
}

void    eating(t_philo *philo)
{
    //dead_check(philo);
    pthread_mutex_lock(philo->l_fork);
    ft_print(philo, "fork");
    pthread_mutex_lock(philo->r_fork);
    ft_print(philo, "fork");
    ft_print(philo, "eating");
    philo->time_of_last_meal = get_current_time();// - philo->t_data->start_time;
    ft_usleep(philo->t_data->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}


void *routine(void *arg) {

    t_philo *philo = (t_philo *)arg;

    while (!*philo->end)
    {
        if (philo->fake_id % 2 != 0 && philo->fake_id != 5)
        {
            if (dead_check(philo))
                break;
            eating(philo);
            sleeping(philo);
            thinking(philo);
        }
        else
        {
            thinking(philo);
            if (dead_check(philo))
                break;
            eating(philo);
            sleeping(philo);
        }
        pthread_mutex_lock(&philo->philo_id);
        philo->fake_id = (philo->fake_id + 1) % philo->t_data->number_of_philo + 1;
        pthread_mutex_unlock(&philo->philo_id);
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
