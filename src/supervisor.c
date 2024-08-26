/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:47:21 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/21 17:47:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Monitors if a philo should die.
/// @param philo A pointer to the ruleset structure.
void	supervisor(t_philo *philo)
{
	ft_mprintf("Supervisor launched!\n", NULL);
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	pthread_mutex_lock(&philo->philo_lock);
	while (!philo->ruleset->stop && (!philo->dead || philo->nb_of_meals <=
	philo->ruleset->max_meals))
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->nb_of_meals == philo->ruleset->max_meals)
		{
			pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
			pthread_mutex_unlock(&philo->philo_lock);
			pthread_mutex_lock(&philo->philo_lock);
			philo->status = replete;
			pthread_mutex_unlock(&philo->philo_lock);
			pthread_mutex_lock(&philo->ruleset->ruleset_lock);
			philo->ruleset->nb_replete_philos++;
			pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		}
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
		pthread_mutex_lock(&philo->philo_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	pthread_mutex_unlock(&philo->philo_lock);
	ft_mprintf("Supervisor exiting!\n", NULL);
}

/// @brief Monitors if there's a dead philo OR if all philos are replete.
/// @param ruleset
void monitoring(t_ruleset *ruleset)
{
	pthread_mutex_lock(&ruleset->ruleset_lock);
	while (!ruleset->stop)
	{
		pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
		if (ruleset->nb_replete_philos == ruleset->number_of_philosophers || ruleset->dead_philo)
			ruleset->stop = 1;
		pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&ruleset->ruleset_lock);
}