#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h> //usleep için
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> //malloc için
#include <stdbool.h>

# define ERR_ARG "Error: Invalid args."
# define ERR_INIT "Error: Init failed."

# define PHILO_MAX 200

typedef struct s_forks
{
	pthread_mutex_t	fork_mutex;
	bool			is_use;
}			t_forks;


typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	size_t			time_of_last_meal;
	int				nbr_of_meals; //for optional
	bool			is_eating;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*message;
	pthread_mutex_t	*end_mutex;
	bool			end;
}					t_philo;


typedef struct s_data
{
	long			number_of_philo;
	size_t			timo_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_of_times_eat;
	size_t			start_time;
	t_philo			philo[PHILO_MAX];
	t_forks			forks[PHILO_MAX];
	pthread_mutex_t	message;
	pthread_mutex_t	end_mutex;
	bool			end;
}					t_data;


int	ft_isdigit(int c);
int	init_all(t_data *data, int argc, char **argv);
int	philo_start(t_data *data);
long	ft_atol(const char *str);
size_t	get_current_time();



#endif
