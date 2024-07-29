#include "philo.h"
#include <errno.h>

void    thinking(t_philo *philo)
{
    ft_print(philo, "is thinking");
}

void    sleeping(t_philo *philo)
{
    ft_print(philo, "is sleeping");
    ft_usleep(philo->t_data->time_to_sleep);
}


void    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    ft_print(philo, "has taking a fork");
    pthread_mutex_lock(philo->r_fork);
    ft_print(philo, "has taking a fork");
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->time_of_last_meal = get_current_time();
    pthread_mutex_unlock(&philo->last_meal_mutex);
    ft_print(philo, "is eating");
    ft_usleep(philo->t_data->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void *routine(void *arg) {

    t_philo *philo = (t_philo *)arg;

    while (!*philo->end)
    {
        if (philo->chair_no % 2 != 0 && philo->chair_no != philo->t_data->number_of_philo)
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
        if (philo->chair_no != (philo->t_data->number_of_philo))
            philo->chair_no = (philo->chair_no + 1) % (philo->t_data->number_of_philo + 1);
        else
            philo->chair_no = 1;
        //printf("%d numaralı filozofun yeni sandalye numarası: %d\n", philo->id, philo->chair_no);
    }
    return NULL;
}

int philo_start(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_current_time();
    while (i < data->number_of_philo)
    {
        data->philo[i].time_of_last_meal = get_current_time();
        pthread_create(&data->philo[i].thread, NULL, routine, (void *)&data->philo[i]);
        pthread_detach(data->philo[i].thread);
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
    return (EXIT_SUCCESS);
}
