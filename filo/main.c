#include "philo.h"
#include <stdlib.h>

void create_threads(t_program *prog)
{
	int	i;

	i = 0;
	while(i < prog->num_of_philos)
	{
		pthread_create(&prog->philos[i].thread, NULL, philo_routine, &prog->philos[i]);
		i++;
	}
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor_routine, prog);
	pthread_join(monitor_thread, NULL);
}

void join_threads(t_program *prog)
{
	int	i;

	i = 0;
	while(i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
}

void destroy_mutexes(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);
}

int main(int argc, char **argv) {
    t_program prog;
    if (init_program(&prog, argc, argv))
        return (1);
    create_threads(&prog);
    join_threads(&prog);
    destroy_mutexes(&prog);
    free(prog.philos);
    free(prog.forks);
    return (0);
}
