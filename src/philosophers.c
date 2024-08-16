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



/// \brief
/// \param ruleset A pointer to the ruleset structure.
/// \return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	init_simu(t_ruleset *ruleset)
{
	(void)ruleset;
	return (NO_ERROR);
}

/// \brief Initialises the array of philos.
/// \param ruleset A pointer to the ruleset structure.
/// \return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	init_philos(t_ruleset *ruleset)
{
	int i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		ruleset->philos_array[i].ruleset = ruleset;
		ruleset->philos_array[i].id = i + 1;
		pthread_create(&ruleset->philos_array[i].tid, NULL, (void *)&routine,
					   (void *)&ruleset->philos_array[i]);
		if (!ruleset->philos_array[i].tid)
			return (ft_exit(ruleset), ERROR);
		ruleset->philos_array[i].last_meal = 0;
		ruleset->philos_array[i].status = 0;
		ruleset->philos_array[i].nb_of_meals = 0;
		pthread_mutex_init(&ruleset->philos_array[i].l_fork, NULL);
		if (i == 0)
			ruleset->philos_array[i].neighbor[0] =
					&ruleset->philos_array[ruleset->number_of_philosophers -
											1];
		else
			ruleset->philos_array[i].neighbor[0] = &ruleset->philos_array[i -
																		  1];
		if (i == ruleset->number_of_philosophers - 1)
			ruleset->philos_array[i].neighbor[1] = &ruleset->philos_array[0];
		else
			ruleset->philos_array[i].neighbor[1] = &ruleset->philos_array[i +
																		  1];
		i++;
	}
	return (NO_ERROR);
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
	if (ruleset->number_of_philosophers < MIN_PHILO ||
	ruleset->number_of_philosophers > MAX_PHILO)
		return (ERROR);
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
	t_ruleset	*ruleset;

	ruleset = malloc(sizeof(t_ruleset));
	if (!ruleset)
		return (ERROR);
	if (check_input(argv))
		return (ERROR);
	if (parsing(argc, ruleset, argv))
		return (ERROR);
	ruleset->philos_array = malloc(ruleset->number_of_philosophers * sizeof
			(t_philo));
//	if (!ruleset->philos_array)
//		return (ft_exit(ruleset), ERROR);
	if (init_philos(ruleset))
		return (ERROR);
	if (init_simu(ruleset))
		return (ERROR);
	join_all_threads(ruleset);
	ft_exit(ruleset);
	return (NO_ERROR);
}