/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:08:26 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/17 13:57:22 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	ft_thread_initialise(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_create(&ruleset->philos_array[i].tid, NULL, routine, \
			&ruleset->philos_array[i]) != 0)
			return (ERROR);
		usleep(1);
		i++;
	}
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		ruleset->philos_array[i].last_meal = get_time();
		ruleset->philos_array[i].is_eating = 0;
		i++;
	}
	pthread_mutex_lock(&ruleset->m_start);
	ruleset->start_time = get_time();
	pthread_mutex_unlock(&ruleset->m_start);
	supervisor(ruleset);
	join_all_threads(ruleset);
	return (NO_ERROR);
}

t_error	ft_mutex_initialise(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&ruleset->m_start, NULL))
		return (ERROR);
	if (pthread_mutex_init(&ruleset->m_replete, NULL))
		return (ERROR);
	if (pthread_mutex_init(&ruleset->m_stop, NULL))
		return (ERROR);
	if (pthread_mutex_init(&ruleset->m_eating, NULL))
		return (ERROR);
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_mutex_init(&ruleset->philos_array[i].m_status, NULL))
			return (ERROR);
		if (pthread_mutex_init(&ruleset->philos_array[i].m_last_meal, NULL))
			return (ERROR);
		if (pthread_mutex_init(&ruleset->philos_array[i].m_nb_of_meals, NULL))
			return (ERROR);
		if (pthread_mutex_init(&ruleset->philos_array[i].m_fork, NULL))
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

t_error	ft_init_philos(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		memset(&ruleset->philos_array[i], 0, sizeof(t_philo));
		ruleset->philos_array[i].ruleset = ruleset;
		ruleset->philos_array[i].id = i + 1;
		ruleset->philos_array[i].status = thinking;
		if (i == ruleset->number_of_philosophers - 1)
			ruleset->philos_array[i].neighbor = &ruleset->philos_array[0];
		else
			ruleset->philos_array[i].neighbor = &ruleset->philos_array[i + 1];
		i++;
	}
	return (NO_ERROR);
}

t_error	parsing(const int argc, t_ruleset *ruleset, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (ERROR);
	memset(ruleset, 0, sizeof(t_ruleset));
	ruleset->number_of_philosophers = ft_atoi(argv[1]);
	ruleset->time_to_die = ft_atoi(argv[2]);
	ruleset->time_to_eat = ft_atoi(argv[3]);
	ruleset->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ruleset->max_meals = ft_atoi(argv[5]);
	else
		ruleset->max_meals = -1;
	if (ruleset->number_of_philosophers < MIN_PHILO || \
		ruleset->number_of_philosophers > MAX_PHILO || ruleset->time_to_die > \
		INT_MAX || ruleset->time_to_eat > INT_MAX || ruleset->time_to_sleep > \
		INT_MAX || ruleset->max_meals > INT_MAX)
		return (ERROR);
	ruleset->start_time = 0;
	return (NO_ERROR);
}

void	wait_for_start(t_ruleset *ruleset)
{
	while (1)
	{
		pthread_mutex_lock(&ruleset->m_start);
		if (ruleset->start_time)
			break ;
		pthread_mutex_unlock(&ruleset->m_start);
		usleep(1);
	}
	pthread_mutex_unlock(&ruleset->m_start);
}
