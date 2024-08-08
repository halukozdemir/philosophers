/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:12 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/09 00:42:22 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

int	argv_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "0", ft_strlen(argv[i])) == 0)
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
