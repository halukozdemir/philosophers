#include "philo.h"

void	ft_usleep(size_t waiting_time)
{
	size_t time;

	time = get_current_time();
	while (get_current_time() - time < waiting_time)
		usleep(100);
}

void display(t_philo *philo, char *msg)
{
    long long time;
    pthread_mutex_lock(&philo->data->display);
    pthread_mutex_lock(&philo->data->philo_dead_mutex);
    if (philo->data->philo_dead == 1)
    {
        pthread_mutex_unlock(&philo->data->philo_dead_mutex);
        pthread_mutex_unlock(&philo->data->display);
        return;
    }
    time = get_current_time() - philo->philo_start;
    printf("%lld %d %s\n", time, philo->philos_id, msg);
    pthread_mutex_unlock(&philo->data->philo_dead_mutex);
    pthread_mutex_unlock(&philo->data->display);
}

size_t	get_current_time()
{
	long long	current_time;

	struct timeval	tv;
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

int		ft_isspace(int c)
{
	const char	*str;
	int			i;

	i = 0;
	str = " \n\t\v\f\r";
	while (c != str[i])
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *s)
{
	int		i;
	long	res;
	long	coeff;

	i = 0;
	res = 0;
	coeff = 1;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		coeff = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * coeff);
}
