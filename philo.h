/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:32:02 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/04 16:58:32 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h> //malloc için
# include <sys/time.h>
# include <unistd.h> //usleep için

# define ERR_ARG "Error: Invalid args."
# define ERR_INIT "Error: Init failed."

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				chair_no;
	size_t			time_of_last_meal;
	int				eat_count;
	int				*number_of_philo;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*message;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	philo_id;
	pthread_mutex_t	last_meal_mutex;
	bool			*end;
	bool			is_thinking;
	struct s_data	*t_data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	size_t			timo_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_of_times_eat;
	size_t			start_time;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	message;
	pthread_mutex_t	end_mutex;
	bool			end;
}					t_data;

int					init_mutex(t_data *data);
int					init_forks(t_data *data);
int					init_philos(t_data *data);
int					init_data(t_data *data, int argc, char **argv);
int					init_all(t_data *data, int argc, char **argv);
int					argv_check(char **argv);
void				*routine(void *arg);
int					philo_start(t_data *data);
long				ft_atol(char *str);
int					ft_isdigit(int c);
size_t				get_current_time(void);
void				ft_usleep(size_t ms);
int					ft_print(t_philo *philo, char *state);
void				dead_check(t_data *data);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
int					clean_all(t_data *data);

#endif
