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
