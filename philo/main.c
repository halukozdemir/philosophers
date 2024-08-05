/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:12 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/05 18:27:19 by halozdem         ###   ########.fr       */
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
		if (argv[i][0] == '0')
			return (EXIT_FAILURE);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (EXIT_FAILURE);
			j++;
		}
		j = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (((argc < 5 || argc > 6) || argv_check(argv)) && printf("%s", ERR_ARG))
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
