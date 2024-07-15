#include "philo.h"

void	ft_usleep(size_t waiting_time)
{
	size_t time;

	time = get_current_time();
	while (get_current_time() - time < waiting_time)
		usleep(100);
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
int	message(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(philo->message);
	pthread_mutex_lock(philo->end_mutex);
	if (*philo->end == 1 && ft_strncmp(str, "died", 4) == 0)
	{
		pthread_mutex_unlock(philo->message);
		pthread_mutex_unlock(philo->end_mutex);
		return (EXIT_FAILURE);
	}
	printf("%zu %d %s\n", (get_current_time() - *philo->start_time), philo->id, str);
	pthread_mutex_unlock(philo->message);
	pthread_mutex_unlock(philo->end_mutex);
	return (EXIT_SUCCESS);
}

int	ft_strncmp(char *str, char *cmp, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	return (1);
}
