/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:16 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/02 17:31:42 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_data *data)
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
}

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->t_data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, "has taking a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, "has taking a fork");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_of_last_meal = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_print(philo, "is eating");
	ft_usleep(philo->t_data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		else
		{
			thinking(philo);
			eating(philo);
			sleeping(philo);
		}
		philo->chair_no = (philo->chair_no % philo->t_data->number_of_philo)
			+ 1;
		if (philo->eat_count == philo->t_data->nbr_of_times_eat)
			philo->t_data->end = true;
	}
	return (NULL);
}

int	philo_start(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philo)
	{
		data->philo[i].time_of_last_meal = get_current_time();
		pthread_create(&data->philo[i].thread, NULL, routine,
			(void *)&data->philo[i]);
		usleep(100);
		pthread_detach(data->philo[i].thread);
		i++;
	}
	dead_check(data);
	return (EXIT_SUCCESS);
}
