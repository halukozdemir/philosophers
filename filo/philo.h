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

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	size_t			*start_time;
	pthread_mutex_t	time_of_last_meal_mutex;
	size_t			time_of_last_meal;
	pthread_mutex_t	nbr_of_meals_mutex;
	int				nbr_of_meals;
	pthread_mutex_t	is_not_eating_mutex;
	int				is_not_eating;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*message;
	pthread_mutex_t	*end_mutex;
	int				*end;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_philosopher;

typedef struct s_data
{
	int				number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_of_times_eat;
	size_t			start_time;
	t_philosopher	philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	message;
	pthread_mutex_t	end_mutex;
	int				end;
}					t_data;

int	ft_isdigit(char c);
int argv_check(char **argv);
int	ft_close(t_data *data);
int	everyone_ate(t_data *data);
int	sleeping(t_philosopher *philo);
void	take_forks(t_philosopher *philo);
int	eating(void	*philo_ptr);
int	init_data(t_data *data, int argc, char **argv);
int	init_philosophers(t_data *data);
int	init_mutex(t_data *data);
int	init_forks(t_data *data);
int ft_init(t_data *data, int argc, char **argv);
void	mutex_is_not_eating(t_philosopher *philo, int is_not_eating);
void	mutex_nbr_of_meals(t_philosopher *philo);
void	mutex_end(t_philosopher *philo, int value);
int	end_is_true_data(t_data *data);
int	end_is_true_philo(t_philosopher *philo);
int	dead_philo(t_data *data);
void	*living_philo(void *philosopher);
void	check_end(t_data *data);
int	philosophers(t_data *data);
void	solo_philo(t_data *data);
size_t	get_current_time();
void	init_time(t_data *data);
void	custom_sleep_eating(t_philosopher *philo);
void	custom_sleep_sleeping(t_philosopher *philo, size_t time);
void	ft_usleep(size_t waiting_time);
int		ft_isspace(int c);
long	ft_atol(const char *s);
int	message(t_philosopher *philo, char *str);
int	ft_strncmp(char *str, char *cmp, size_t len);

#endif
