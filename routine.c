#include "philo.h"
#include <errno.h>

void    thinking(t_philo *philo)
{
    ft_print(philo, "thinking");
}

void    sleeping(t_philo *philo)
{
    ft_print(philo, "sleeping");
    ft_usleep(philo->t_data->time_to_sleep);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    ft_print(philo, "fork");
    pthread_mutex_lock(philo->r_fork);
    ft_print(philo, "fork");
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->time_of_last_meal = get_current_time();
    pthread_mutex_unlock(&philo->last_meal_mutex);
    ft_print(philo, "eating");
    ft_usleep(philo->t_data->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void *routine(void *arg) {

    t_philo *philo = (t_philo *)arg;

    while (!*philo->end)
    {
        if (philo->chair_no % 2 != 0 && philo->chair_no != philo->t_data->number_of_philo - 1)
        {
            eating(philo);
            sleeping(philo);
            thinking(philo);
        }
        else
        {
            thinking(philo);
            eating(philo);
            sleeping(philo);
        }

        if (philo->chair_no + 1 != (philo->t_data->number_of_philo + 1))
            philo->chair_no = (philo->chair_no + 1) % (philo->t_data->number_of_philo + 1);
        else
            philo->chair_no = 1;
    }
    return NULL;
}

int philo_start(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_current_time();
    while(i < data->number_of_philo)
    {
        data->philo[i].time_of_last_meal = get_current_time();
        pthread_create(&data->philo[i].thread, NULL, routine, (void *)&data->philo[i]);
        i++;
    }
    while (1)
    {
        int j = 0;
        while (j < data->number_of_philo)
        {
            pthread_mutex_lock(&data->philo[j].last_meal_mutex);
            if ((get_current_time() - data->philo[j].time_of_last_meal) >= data->timo_to_die + 10)
            {
                ft_print(&data->philo[j], "died");
                pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
                return (EXIT_FAILURE);
            }
            pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
            j++;
        }
    }
    i = 0;
    while(i < data->number_of_philo)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
    return (EXIT_SUCCESS);
}
