/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:12 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/04 18:21:25 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argv_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (((argc < 5 || argc > 6) || !argv_check(argv)) && printf("%s", ERR_ARG))
		return (EXIT_FAILURE);
	if (ft_atol(argv[1]) > 200)
	{
		printf("%s", ERR_ARG);
		return (EXIT_FAILURE);
	}
	if (init_all(&data, argc, argv) && printf("%s", ERR_INIT))
		return (EXIT_FAILURE);
	philo_start(&data);
	while (1)
		if (data.end == true)
			break ;
	clean_all(&data);
}
