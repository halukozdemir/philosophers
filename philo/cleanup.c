/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:29:18 by beyarsla          #+#    #+#             */
/*   Updated: 2024/08/09 15:27:19 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_calc(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[j].last_meal_mutex);
		pthread_mutex_lock(&data->end_mutex);
		if ((get_current_time()
				- data->philo[j].time_of_last_meal) >= data->timo_to_die
			&& !data->end)
		{
			pthread_mutex_unlock(&data->end_mutex);
			ft_print(&data->philo[j], "died");
			pthread_mutex_lock(&data->end_mutex);
			data->end = true;
			pthread_mutex_unlock(&data->end_mutex);
			pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
		pthread_mutex_unlock(&data->end_mutex);
		j++;
	}
}

void	dead_check(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	while (data->end == false)
	{
		pthread_mutex_unlock(&data->end_mutex);
		dead_calc(data);
		pthread_mutex_lock(&data->end_mutex);
	}
	pthread_mutex_unlock(&data->end_mutex);
}

void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_lock(&data->message) != EINVAL)
		pthread_mutex_destroy(&data->message);
	if (pthread_mutex_lock(&data->end_mutex) != EINVAL)
		pthread_mutex_destroy(&data->end_mutex);
	while (++i < data->number_of_philo)
	{
		if (pthread_mutex_lock(&data->philo[i].last_meal_mutex) != EINVAL)
			pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		if (data->number_of_philo != 1)
		{
			if (pthread_mutex_lock(&data->forks[i]) != EINVAL)
				pthread_mutex_destroy(&data->forks[i]);
		}
		else
		{
			pthread_mutex_unlock(&data->forks[i]);
			if (pthread_mutex_lock(&data->forks[i]) != EINVAL)
				pthread_mutex_destroy(&data->forks[i]);
		}
	}
}
