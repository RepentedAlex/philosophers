/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:38:57 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 13:51:41 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

/// \brief Initialises all the data for the ruleset.
/// \param argv CLI arguments.
/// \param ruleset Pointer to the structure holding all the simulation's params.
/// \return ERROR if it encountered an error, NO_ERROR otherwise.
t_error	ft_init_data(char **argv, t_ruleset *ruleset)
{
	ruleset->nb_philos = ft_atoi(argv[1]);
	ruleset->death_time = ft_atoi(argv[2]);
	ruleset->eat_time = ft_atoi(argv[3]);
	ruleset->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		ruleset->max_meals = ft_atoi(argv[5]);
	else
		ruleset->max_meals = -1;
	if (ruleset->nb_philos < MIN_PHILOS || ruleset->nb_philos > MAX_PHILOS ||
	ruleset->death_time < 0 || ruleset->eat_time < 0 || ruleset->sleep_time < 0)
		return (ft_error("Error: Invalid arguments.\n", ruleset), ERROR);
	ruleset->dead = 0;
	pthread_mutex_init(&ruleset->write, NULL);
	pthread_mutex_init(&ruleset->lock, NULL);
	return (NO_ERROR);
}

/// \brief Allocates memory for the three arrays (thread IDs, forks, philos).
/// \param ruleset Pointer to the structure holding all the simulation's params.
/// \return ERROR if it encountered an error, NO_ERROR otherwise.
t_error ft_alloc(t_ruleset *ruleset)
{
	ruleset->tid = malloc(ruleset->nb_philos * sizeof(pthread_t));
	if (!ruleset->tid)
		return (ft_error("Error: Couldn't allocate memory.", ruleset), ERROR);
	ruleset->forks = malloc(ruleset->nb_philos * sizeof(pthread_mutex_t));
	if (!ruleset->forks)
		return (ft_error("Error: Couldn't allocate memory.", ruleset), ERROR);
	ruleset->philos = malloc(ruleset->nb_philos * sizeof(t_philo));
	if (!ruleset->philos)
		return (ft_error("Error: Couldn't allocate memory.", ruleset), ERROR);
	return (NO_ERROR);
}

/// \brief Initialises every fork's mutex and assign each fork to a philosopher.
/// \param ruleset Pointer to the structure holding all the simulation's params.
/// \return ERROR if it encountered an error, NO_ERROR otherwise.
t_error	ft_init_forks(t_ruleset *ruleset)
{
	int i = -1;

	while (++i < ruleset->nb_philos)
		if (pthread_mutex_init(&ruleset->forks[i], NULL))
			return (ft_error("Error: Couldn't initialise mutex.\n", ruleset), ERROR);
	i = 0;
	ruleset->philos[i].l_fork = &ruleset->forks[0];
	ruleset->philos[i].r_fork = &ruleset->forks[ruleset->nb_philos - 1];
	while (++i < ruleset->nb_philos)
	{
		ruleset->philos[i].l_fork = &ruleset->forks[i];
		ruleset->philos[i].r_fork = &ruleset->forks[i - 1];
	}
	return (NO_ERROR);
}

/// \brief
/// \param ruleset Pointer to the structure holding all the simulation's params.
/// \return ERROR if it encountered an error, NO_ERROR otherwise.
t_error ft_init_philos(t_ruleset *ruleset)
{
	int i;

	i = -1;
	while (++i < ruleset->nb_philos)
	{
		ruleset->philos[i].ruleset = ruleset;
		ruleset->philos[i].id = i + 1;
		ruleset->philos[i].time_to_die = ruleset->death_time;
		ruleset->philos[i].meals_eaten = 0;
		ruleset->philos[i].status = 0;
		if (pthread_mutex_init(&ruleset->philos[i].lock, NULL))
			return (ft_error("Error: Couldn't initialise mutex.\n", ruleset), ERROR);
	}
	return (NO_ERROR);
}

/// \brief Handles all the initialisation.
/// \param argv CLI arguments.
/// \param ruleset Pointer to the structure holding all the simulation's params.
/// \return ERROR if it encountered an error, NO_ERROR otherwise.
t_error ft_init(char **argv, t_ruleset *ruleset)
{
	if (ft_init_data(argv, ruleset))
		return (ERROR);
	if (ft_alloc(ruleset))
		return (ERROR);
	if (ft_init_forks(ruleset))
		return (ERROR);
	if (ft_init_philos(ruleset))
		return (ERROR);
	return (NO_ERROR);
}
