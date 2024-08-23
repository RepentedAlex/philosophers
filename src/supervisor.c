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

/// @brief Monitors if all philos are replete to stop the simulation.
/// @param ruleset A pointer to the ruleset structure.
void	monitor(t_ruleset *ruleset)
{
	ft_mprintf("Supervisor launched!\n", NULL);
	pthread_mutex_lock(&ruleset->ruleset_lock);
	while (!ruleset->stop)
	{
		pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
		if (ruleset->max_meals != -1 && \
		ruleset->nb_replete_philos == ruleset->number_of_philosophers)
		{
			ft_mprintf("All philos are replete!\n", NULL);
			ruleset->stop = 1;
			pthread_mutex_unlock(&ruleset->ruleset_lock);
		}
		else
			pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&ruleset->ruleset_lock);
	ft_mprintf("Supervisor exiting!\n", NULL);
}

void supervisor(t_philo *philo)
{
	while (!philo->dead)
	{
		pthread_mutex_lock(&philo->philo_lock);
		if ((get_time() - philo->last_meal) >= philo->ruleset->time_to_die \
		&& philo->status != eating)
		{
			philo->status = dead;
			ft_mprintf("has died\n", philo);
			pthread_mutex_lock(&philo->ruleset->ruleset_lock);
			philo->ruleset->stop = 1;
			pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		}
		pthread_mutex_unlock(&philo->philo_lock);
	}
}