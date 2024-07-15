#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

# define PHILO_MAX 200
# define ERR_ARG 0
# define ERR_MALLOC "Memory Allocate Error."
# define ERR_MUTEX_INIT "Mutex Init Error."
# define ERR_THREAD "Thread Create Error."
#define ERR_THREAD_JOIN "Thread Join Error."
# define ERR_INVALID_ARG "Invalid Arg. Error."

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef	struct s_data
{
	int				philo_count;
	size_t			philo_live_time;
	size_t			philo_eat_time;
	size_t			philo_sleep_time;
	size_t			philo_must_eat;
	size_t			philo_dead;
	pthread_mutex_t	display;
	pthread_mutex_t philo_dead_mutex;
}	t_data;

typedef	struct s_philo
{
	int				philos_id;
	int				philo_loop;
	size_t			philo_start;
	size_t			philo_last_eat;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	philo_last_eat_mutex;
	pthread_t		philo_thread;
	t_data			*data;
}	t_philo;

int		ft_isdigit(char c);
int 	argv_check(char **argv);
size_t	get_current_time();
long	ft_atol(const char *s);
pthread_mutex_t *init_forks(t_data *data);
t_philo	*init_philo(t_data *data, pthread_mutex_t *forks);
int		ft_isspace(int c);
int		start(t_data *data, t_philo *philo);
void 	ft_usleep(size_t waiting_time);
void	display(t_philo *philo, char *msg);
int	init_data(t_data *data, char **argv);


#endif
