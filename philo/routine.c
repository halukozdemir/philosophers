/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:16 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/18 13:43:52 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_helper(t_data *data, int i)
{
	if (data->number_of_philo == 1)
	{
		if (pthread_detach(data->philo[i].thread))
		{
			printf("Error: Detach Err.\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			printf("Error: Join Err.\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	life_cycle(t_philo *philo)
{
	if (philo->chair_no % 2 == 0
		|| philo->chair_no == philo->t_data->number_of_philo)
	{
		thinking(philo);
		odd_eating(philo);
		sleeping(philo);
	}
	else
	{
		even_eating(philo);
		sleeping(philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->t_data->end_mutex);
		if (philo->t_data->end
			|| philo->eat_count == philo->t_data->nbr_of_times_eat)
		{
			pthread_mutex_unlock(&philo->t_data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->t_data->end_mutex);
		life_cycle(philo);
		pthread_mutex_lock(&philo->t_data->end_mutex);
		philo->chair_no = (philo->chair_no % philo->t_data->number_of_philo)
			+ 1;
		if (philo->eat_count == philo->t_data->nbr_of_times_eat)
			philo->t_data->end = true;
		pthread_mutex_unlock(&philo->t_data->end_mutex);
	}
	return (NULL);
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]))
			return (EXIT_FAILURE);
		usleep(100);
		i+=2;
	}
	i = 1;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]))
			return (EXIT_FAILURE);
		usleep(100);
		i+=2;
	}
	dead_check(data);
	i = -1;
	while (++i < data->number_of_philo)
		if (routine_helper(data, i))
			break ;
	return (EXIT_SUCCESS);
}
