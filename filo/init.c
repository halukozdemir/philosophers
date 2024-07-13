#include "philo.h"
#include "stdlib.h"

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

void init_philo(t_philo *philo, t_program *prog, int id, size_t start_time) {
    philo->id = id;
    philo->num_of_philos = prog->num_of_philos;
    philo->dead = &prog->dead_flag;
    philo->l_fork = &prog->forks[(id - 1) % prog->num_of_philos]; // Sol çatal (id - 1)
    philo->r_fork = &prog->forks[id % prog->num_of_philos]; // Sağ çatal (id)
    philo->write_lock = &prog->write_lock;
    philo->dead_lock = &prog->dead_lock;
    philo->meal_lock = &prog->meal_lock;
    philo->eating = 0;
    philo->meals_eaten = 0;
    philo->last_meal = start_time;
    philo->start_time = start_time;
    philo->time_to_die = prog->time_to_die;
    philo->time_to_eat = prog->time_to_eat;
    philo->time_to_sleep = prog->time_to_sleep;
    philo->num_times_to_eat = prog->num_times_to_eat;
}

void init_philos(t_program *prog) {
    int i;
    size_t start_time;

    i = 0;
    start_time = get_current_time();
    prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
    while (i < prog->num_of_philos) {
        init_philo(&prog->philos[i], prog, i + 1, start_time);
        i++; // i'yi arttırmayı unutmayın
    }
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
	return (0);
}
