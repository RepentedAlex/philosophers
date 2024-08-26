/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:43:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/21 17:46:33 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief
/// @param ruleset A pointer to the ruleset structure.
/// @return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	init_simu(t_ruleset *ruleset)
{
	pthread_mutex_lock(&ruleset->ruleset_lock);
	ruleset->start_time = get_time();
	pthread_mutex_unlock(&ruleset->ruleset_lock);
	if (!ruleset->start_time)
		return (ft_exit(ruleset), ERROR);
	return (NO_ERROR);
}

static void	internal_init_philo(const t_ruleset *ruleset, int i)
{
	pthread_mutex_lock(&ruleset->philos_array[i].philo_lock);
	ruleset->philos_array[i].last_meal = 0;
	ruleset->philos_array[i].status = thinking;
	ruleset->philos_array[i].nb_of_meals = 0;
	if (i == 0)
		ruleset->philos_array[i].neighbor = \
		&ruleset->philos_array[ruleset->number_of_philosophers - 1];
	else if (i == ruleset->number_of_philosophers - 1)
		ruleset->philos_array[i].neighbor = \
		&ruleset->philos_array[0];
	else
		ruleset->philos_array[i].neighbor = \
		&ruleset->philos_array[i + 1];
	pthread_mutex_unlock(&ruleset->philos_array[i].philo_lock);
}

/// @brief Initialises the array of philos.
/// @param ruleset A pointer to the ruleset structure.
/// @return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	init_philos(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		ruleset->philos_array[i].ruleset = ruleset;
		ruleset->philos_array[i].id = i + 1;
		pthread_create(&ruleset->philos_array[i].tid, NULL, (void *)&routine, \
		(void *)&ruleset->philos_array[i]);
		if (!ruleset->philos_array[i].tid)
			return (ft_exit(ruleset), ERROR);
		pthread_mutex_init(&ruleset->philos_array[i].philo_lock, NULL);
		internal_init_philo(ruleset, i);
		i++;
	}
	return (NO_ERROR);
}

/// @brief Fills the corresponding structures with the CLI-provided arguments.
/// @param argv CLI arguments.
/// @return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	parsing(int argc, t_ruleset *ruleset, char *argv[])
{
	memset(ruleset, 0, sizeof(t_ruleset));
	pthread_mutex_init(&ruleset->ruleset_lock, NULL);
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
	if (ruleset->number_of_philosophers < MIN_PHILO || \
	ruleset->number_of_philosophers > MAX_PHILO)
		return (ERROR);
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
	if (init_philos(ruleset))
		return (ERROR);
	if (init_simu(ruleset))
		return (ERROR);
	supervisor(ruleset);
	join_all_threads(ruleset);
	ft_exit(ruleset);
	return (NO_ERROR);
}
