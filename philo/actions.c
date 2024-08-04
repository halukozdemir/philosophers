/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:32:35 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/04 18:31:58 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
