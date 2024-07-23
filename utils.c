#include "philo.h"

long	ft_atol(char *str)
{
	int	i;
	long sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;

	if (!str[i])
		return (0);
	while(((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if(str[i] == '+')
		i++;
	while((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	get_current_time()
{
	size_t	current_time;

	struct timeval	tv;
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(size_t	ms)
{
	size_t	time;

	time = get_current_time() + ms;
	while (get_current_time() < time)
		if (usleep(100) != 0)
			return ;
}
int	ft_print(t_philo *philo, char *state)
{
	pthread_mutex_lock(philo->message);
	if (philo->t_data->end == false)
	{
		if (ft_strcmp(state, "fork") == 0)
		{
			printf("%zu %d has taken a fork\n", get_current_time() - philo->t_data->start_time, philo->id);
			pthread_mutex_unlock(philo->message);
		}
		else if (ft_strcmp(state, "eating") == 0)
		{
			printf("%zu %d eating\n", get_current_time() - philo->t_data->start_time, philo->id);
			pthread_mutex_unlock(philo->message);
		}
		else if (ft_strcmp(state, "sleeping") == 0)
		{
			printf("%zu %d sleeping\n", get_current_time() - philo->t_data->start_time, philo->id);
			pthread_mutex_unlock(philo->message);
		}
		else if (ft_strcmp(state, "thinking") == 0)
		{
			printf("%zu %d is thinking\n", get_current_time() - philo->t_data->start_time,  philo->id);
			pthread_mutex_unlock(philo->message);
		}
		else
		{
			printf("%zu %d died\n", get_current_time() - philo->t_data->start_time, philo->id);
   			pthread_mutex_unlock(philo->message);
		}
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(philo->message);
	return (EXIT_FAILURE);
}
