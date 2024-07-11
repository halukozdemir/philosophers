#include "philo.h"

void init_mutexes(t_program *prog)
{
	int	i;

	i = 0;
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	while (i < prog->num_of_philos)
	{
		pthread_mutex_init(&prog->forks[i], NULL);
		i++;
	}
}

void init_philo(t_philo *philo, t_program *prog, int id, size_t start_time)
{
	philo->id = id;
	philo->num_of_philos = prog->num_of_philos;
	philo->dead = &prog->dead_flag;
	
}

int	init_program(t_program *prog, int argc, char **argv)
{
	prog->num_of_philos = ft_atol(argv[1]);
	prog->time_to_die = ft_atol(argv[2]);
	prog->time_to_eat = ft_atol(argv[3]);
	prog->time_to_sleep = ft_atol(argv[4]);
	prog->num_times_to_eat = (argc == 6) ? ft_atol(argv[5]) : -1;
	prog->dead_flag = 0;
	init_mutexes(prog);
	init_philos(prog);
}
