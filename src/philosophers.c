/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:43:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:51 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// \brief Converts a string-exprimed number into an int.
/// \param str The number exprimed in an array of character.
/// \return The number in an integer.
int	ft_atoi(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] == 9 || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret);
}

/// \brief Fills the corresponding structures with the CLI-provided arguments.
/// \param argv CLI arguments.
/// \return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error parsing(int argc, t_ruleset *ruleset, char *argv[])
{
	memset(ruleset, 0, sizeof(t_ruleset));
	if (argc != 5 && argc != 6)
		return (ERROR);
	ruleset->number_of_philosophers = ft_atoi(argv[1]);
	ruleset->time_to_die = ft_atoi(argv[2]);
	ruleset->time_to_eat = ft_atoi(argv[3]);
	ruleset->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ruleset->max_meals = ft_atoi(argv[5]);
	else
		ruleset->max_meals = -1;
	pthread_mutex_init(ruleset->write, NULL);
	return (NO_ERROR);
}

/// \brief Checks for invalid characters in the passed arguments.
/// \param argc Number of CLI arguments.
/// \param argv CLI arguments.
/// \return ERROR(1) if a non-digit character is encountered, else NO_ERROR(O).
t_error	check_input(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ERROR);
			j++;
		}
		i++;
	}
	return (NO_ERROR);
}

int	main(int argc, char *argv[])
{
	t_ruleset	ruleset;

	if (check_input(argv))
		return (ERROR);
	if (parsing(argc, &ruleset, argv))
		return (ERROR);
	ruleset.philos = malloc(ruleset.number_of_philosophers * sizeof(t_philo));
	if (!ruleset.philos)
		//TODO EXIT
	pthread_mutex_init(ruleset.write, NULL);

	return (NO_ERROR);
}