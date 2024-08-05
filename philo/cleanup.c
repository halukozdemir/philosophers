/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:19:07 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/05 18:19:08 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_all(t_data *data)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (!pthread_mutex_destroy(&data->message))
		err = 1;
	if (!pthread_mutex_destroy(&data->end_mutex))
		err = 1;
	while (i < data->number_of_philo)
	{
		if (!pthread_mutex_destroy(&data->philo[i].philo_id))
			err = 1;
		if (!pthread_mutex_destroy(&data->philo[i].last_meal_mutex))
			err = 1;
		if (!pthread_mutex_destroy(&data->forks[i]))
			err = 1;
		i++;
	}
	return (err);
}
