#include "philo.h"

#include "philo.h"

void destroy(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
    int i;

    if (data)
    {
        pthread_mutex_destroy(&data->display);
        pthread_mutex_destroy(&data->philo_dead_mutex);
    }
    if (forks)
    {
        i = 0;
        while (i < data->philo_count)
        {
            pthread_mutex_destroy(&forks[i]);
            pthread_mutex_destroy(&philos[i].philo_last_eat_mutex);
            philos[i].left_fork = NULL;
            philos[i].right_fork = NULL;
            i++;
        }
        free(forks); // forks için tahsis edilmiş belleği serbest bırakıyoruz
    }
    if (philos)
    {
        free(philos); // philos için tahsis edilmiş belleği serbest bırakıyoruz
    }
}


int main (int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	if (!(argc >= 4 && argc <= 5) || (argv_check(argv) != 1))
		return (ERR_ARG);
	if (init_data(&data, argv) != 0)
		return (1);
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philo = init_philo(&data, forks);
	if (!philo)
		return (1);
	if (start(&data, philo))
		destroy(&data, forks, philo);
	free(forks);
	free(philo);
}
