/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:05 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/04 18:20:20 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->message, NULL);
	while (i < data->number_of_philo)
	{
		data->philo[i].message = &data->message;
		data->philo[i].end_mutex = &data->end_mutex;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].philo_id, NULL);
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo - 1)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[i + 1];
		i++;
	}
	data->philo[i].l_fork = &data->forks[i];
	data->philo[i].r_fork = &data->forks[0];
	return (EXIT_SUCCESS);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].chair_no = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].end = &data->end;
		data->philo[i].number_of_philo = &data->number_of_philo;
		data->philo[i].is_thinking = false;
		data->philo[i].t_data = data;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philo = ft_atol(argv[1]);
	data->timo_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->nbr_of_times_eat = ft_atol(argv[5]);
	else
		data->nbr_of_times_eat = -1;
	data->end = false;
	return (EXIT_SUCCESS);
}

int	init_all(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (EXIT_FAILURE);
	if (init_philos(data))
		return (EXIT_FAILURE);
	if (init_forks(data))
		return (EXIT_FAILURE);
	if (init_mutex(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
