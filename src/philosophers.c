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
t_error	thread_handling(t_ruleset *ruleset)
{
	int	i;

	ruleset->start_time = get_time();
	if (!ruleset->start_time)
		return (ERROR);
	if (ruleset->max_meals != -1)
	{
		if (pthread_create(&ruleset->monitor, NULL, (void *) &monitoring, (void
		*)&ruleset))
			return (ERROR);
	}
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_create(&ruleset->philos[i].tid, NULL, \
		(void *)&routine, (void *) &ruleset->philos[i]))
			return (ERROR);
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_join(ruleset->philos_array[i].tid, NULL))
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

static void	internal_init_philo(t_ruleset *ruleset, int i)
{
	pthread_mutex_init(&ruleset->philos[i].philo_lock, NULL);
	pthread_mutex_lock(&ruleset->philos[i].philo_lock);
	ruleset->philos[i].ruleset = ruleset;
	ruleset->philos[i].supervis = 0;
	ruleset->philos[i].id = i + 1;
	ruleset->philos[i].nb_of_meals = 0;
	ruleset->philos[i].is_replete = 0;
	ruleset->philos[i].is_eating = 0;
	ruleset->philos[i].remaining_time = ruleset->time_to_die;
	ruleset->philos[i].dead = 0;
	if (i == ruleset->number_of_philosophers - 1)
		ruleset->philos[i].neighbor = \
		&ruleset->philos[0];
	else
		ruleset->philos[i].neighbor = \
		&ruleset->philos[i + 1];
	pthread_mutex_unlock(&ruleset->philos[i].philo_lock);
}

/// @brief Initialises the array of philos.
/// @param ruleset A pointer to the ruleset structure.
/// @return ERROR(1) if something went wrong, otherwise returns NO_ERROR(0).
t_error	init_philos(t_ruleset *ruleset)
{
	int	i;

	ruleset->philos = malloc(ruleset->number_of_philosophers * sizeof
			(t_philo));
	if (!ruleset->philos)
		return (ERROR);
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
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
	//TODO PREVOIR CAS PHILO TOUT SEUL
	if (init_philos(ruleset))
		return (ERROR);
	if (thread_handling(ruleset))
		return (ERROR);

	ft_exit(ruleset);
	return (NO_ERROR);
}
