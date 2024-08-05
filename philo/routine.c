/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:16 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/05 19:55:12 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_data *data)
{
	int	j;

	while (data->end == false)
	{
		j = 0;
		while (j < data->number_of_philo)
		{
			pthread_mutex_lock(&data->philo[j].last_meal_mutex);
			if ((get_current_time()
					- data->philo[j].time_of_last_meal) >= data->timo_to_die
				&& !data->end)
			{
				ft_print(&data->philo[j], "died");
				data->end = true;
				pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
			j++;
		}
	}
	return (data->end);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!*philo->end && philo->eat_count != philo->t_data->nbr_of_times_eat)
	{
		if (philo->chair_no % 2 != 0
			&& philo->chair_no != philo->t_data->number_of_philo)
		{
			odd_eat(philo);
			sleeping(philo);
		}
		else
		{
			thinking(philo);
			even_eat(philo);
			sleeping(philo);
		}
		philo->chair_no = (philo->chair_no % philo->t_data->number_of_philo)
			+ 1;
		if (philo->eat_count == philo->t_data->nbr_of_times_eat)
			philo->t_data->end = true;
	}
	// printf("%d numaralı filozof %d kez yemek yedi\n", philo->id +1, philo->eat_count);
	return (NULL);
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philo)
	{
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_create(&data->philo[i].thread, NULL, routine,
			(void *)&data->philo[i]);
		// usleep(100);
		pthread_detach(data->philo[i].thread);
		i = i + 2;
	}
	i = 1;
	while (i < data->number_of_philo)
	{
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_create(&data->philo[i].thread, NULL, routine,
			(void *)&data->philo[i]);
		// usleep(100);
		pthread_detach(data->philo[i].thread);
		i = i + 2;
	}
	dead_check(data);
	return (EXIT_SUCCESS);
}
