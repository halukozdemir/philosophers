#include "philo.h"

static void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    display(philo, FORK);
    pthread_mutex_lock(philo->right_fork);
    display(philo, FORK);
    display(philo, EATING);
    if (philo->data->philo_must_eat)
        philo->philo_loop--;
    pthread_mutex_lock(&philo->philo_last_eat_mutex);
    philo->philo_last_eat = get_current_time();
    pthread_mutex_unlock(&philo->philo_last_eat_mutex);
    ft_usleep(philo->data->philo_eat_time);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    display(philo, SLEEPING);
    ft_usleep(philo->data->philo_sleep_time);
    display(philo, THINKING);
}

static void *stalker(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_data *data = philos[0].data;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->philo_count)
        {
            pthread_mutex_lock(&philos[i].philo_last_eat_mutex);
            pthread_mutex_lock(&data->philo_dead_mutex);
            if (data->philo_dead == 1)
            {
                pthread_mutex_unlock(&data->philo_dead_mutex);
                pthread_mutex_unlock(&philos[i].philo_last_eat_mutex);
                return NULL;
            }
            if (get_current_time() - philos[i].philo_last_eat >= data->philo_live_time)
            {
                display(&philos[i], DEAD);
                data->philo_dead = 1;
                pthread_mutex_unlock(&data->philo_dead_mutex);
                pthread_mutex_unlock(&philos[i].philo_last_eat_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->philo_dead_mutex);
            pthread_mutex_unlock(&philos[i].philo_last_eat_mutex);
            i++;
        }
        usleep(100); // Biraz bekleyerek CPU kullanımını azalt
    }
    return NULL;
}



static void solo_philo(t_philo *philo)
{
    display(philo, FORK);
    ft_usleep(philo->data->philo_live_time);
    display(philo, DEAD);
}

static void *philo_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    philo->philo_last_eat = get_current_time();

    if (philo->data->philo_count == 1)
    {
        solo_philo(philo);
        return (NULL);
    }

    if (philo->philos_id % 2 == 0)
    {
        ft_usleep(philo->data->philo_eat_time);
        philo->philo_last_eat = get_current_time();
    }

    while (1)
    {
        pthread_mutex_lock(&philo->data->philo_dead_mutex);
        if (philo->data->philo_dead == 1)
        {
            pthread_mutex_unlock(&philo->data->philo_dead_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->philo_dead_mutex);

        if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
            break;

        eat(philo);
    }

    return (NULL);
}



int start(t_data *data, t_philo *philo)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while (i < data->philo_count)
    {
        philo[i].philo_start = get_current_time();
        if (pthread_create(&philo[i].philo_thread, NULL, philo_routine, &philo[i]) && printf("%s\n", ERR_THREAD))
            return (1);
        i++;
    }

    if (pthread_create(&monitor_thread, NULL, stalker, (void *)philo) && printf("%s\n", ERR_THREAD))
        return (1);

    i = 0;
    while (i < data->philo_count)
    {
        if (pthread_join(philo[i].philo_thread, NULL) && printf("%s\n", ERR_THREAD_JOIN))
            return (1);
        i++;
    }

    if (pthread_join(monitor_thread, NULL) && printf("%s\n", ERR_THREAD_JOIN))
        return (1);

    return (0);
}
