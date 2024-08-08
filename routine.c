/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:16 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/09 00:09:29 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void dead_check(t_data *data)
{
	int j;

	pthread_mutex_lock(&data->end_mutex);
	while (data->end == false)
	{
		pthread_mutex_unlock(&data->end_mutex);
		j = 0;
		while (j < data->number_of_philo)
		{
			pthread_mutex_lock(&data->philo[j].last_meal_mutex);
			pthread_mutex_lock(&data->end_mutex);
			if ((get_current_time() - data->philo[j].time_of_last_meal) >= data->timo_to_die && !data->end)
			{
				pthread_mutex_unlock(&data->end_mutex);
				ft_print(&data->philo[j], "died");
				pthread_mutex_lock(&data->end_mutex);
				data->end = true;
				pthread_mutex_unlock(&data->end_mutex);
				pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
				break;
			}
			pthread_mutex_unlock(&data->philo[j].last_meal_mutex);
			pthread_mutex_unlock(&data->end_mutex);
			j++;
		}
		pthread_mutex_lock(&data->end_mutex);
	}
	pthread_mutex_unlock(&data->end_mutex);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->t_data->end_mutex);
		if (*philo->end || philo->eat_count == philo->t_data->nbr_of_times_eat)
		{
			pthread_mutex_unlock(&philo->t_data->end_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->t_data->end_mutex);

		if (philo->chair_no % 2 != 0 && philo->chair_no != philo->t_data->number_of_philo)
		{
			eating(philo);
			sleeping(philo);
		}
		else
		{
			thinking(philo);
			eating(philo);
			sleeping(philo);
		}

		pthread_mutex_lock(&philo->t_data->end_mutex);
		philo->chair_no = (philo->chair_no % philo->t_data->number_of_philo) + 1;
		if (philo->eat_count == philo->t_data->nbr_of_times_eat)
			philo->t_data->end = true;
		pthread_mutex_unlock(&philo->t_data->end_mutex);
	}
	return (NULL);
}

int philo_start(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		pthread_create(&data->philo[i].thread, NULL, routine,
					   (void *)&data->philo[i]);
		usleep(100);
		// pthread_detach(data->philo[i].thread);
		i++;
	}
	dead_check(data);
	i = -1;
	while (++i < data->number_of_philo)
	{
		if (data->number_of_philo == 1)
			pthread_detach(data->philo[i].thread);
		else
			pthread_join(data->philo[i].thread, NULL);
	}
	return (EXIT_SUCCESS);
}
