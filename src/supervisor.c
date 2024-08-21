/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
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
void	supervisor(t_ruleset *ruleset)
{
	while (!ruleset->start_time)
		ft_usleep(1);
	ft_mprintf("Supervisor launched!\n", NULL);
	pthread_mutex_lock(&ruleset->ruleset_lock);
	while (!ruleset->stop)
	{
		pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
		if (ruleset->nb_replete_philos == ruleset->number_of_philosophers)
		{
			ft_mprintf("All philos are replete!\n", NULL);
			ruleset->stop = 1;
			pthread_mutex_unlock(&ruleset->ruleset_lock);
		}
		else
			pthread_mutex_unlock(&ruleset->ruleset_lock);
		pthread_mutex_lock(&ruleset->ruleset_lock);
	}
	ft_mprintf("Supervisor exiting!\n", NULL);
	pthread_mutex_unlock(&ruleset->ruleset_lock);
}
