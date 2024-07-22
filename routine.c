#include "philo.h"

void *routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    //printf("%d numaralı filozofun sol çatalı: %d, sağ çatalı: %d \n", philo->id, philo->l_fork_index, philo->r_fork_index);
    while (1)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->message);
        if(philo->t_data->forks[philo->id].is_use == false && philo->t_data->forks[(philo->id + 1) % *(philo->number_of_philo)].is_use == false)
        {
            philo->t_data->forks[philo->id].is_use = true;
            philo->t_data->forks[(philo->id + 1) % *(philo->number_of_philo)].is_use = true;
            printf("%d numaralı filo çatal aldı. \n", philo->id);
            printf("%d numaralı filo çatal aldı. \n", philo->id);
            printf("%d numaralı filo yemek yedi. \n", philo->id);
            usleep(1000000);
            philo->t_data->forks[philo->id].is_use = false;
            philo->t_data->forks[(philo->id + 1) % *(philo->number_of_philo)].is_use = false;
        }
        else if (philo->is_thinking == false)
        {
            printf("%d numaralı filo düşünüyor. \n", philo->id);
        }
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->message);
    }



    return NULL;
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philo)
	{
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
