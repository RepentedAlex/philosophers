/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:11:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/16 18:11:52 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	join_all_threads(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		if (pthread_join(ruleset->philos_array[i].tid, NULL))
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

void	ft_exit(t_ruleset *ruleset)
{
	if (ruleset && ruleset->philos_array)
		free(ruleset->philos_array);
	if (ruleset)
		free(ruleset);
}

void	update_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	pthread_mutex_lock(&philo->m_nb_of_meals);
	philo->nb_of_meals++;
	pthread_mutex_lock(&philo->ruleset->m_eating);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->ruleset->m_eating);
	if (philo->nb_of_meals == philo->ruleset->max_meals)
		increment_replete_philos(philo);
	pthread_mutex_unlock(&philo->m_nb_of_meals);
}

void	three_philos(t_philo *philo, pthread_mutex_t **fir_fork, \
pthread_mutex_t **sec_fork)
{
	if (philo->id < philo->neighbor->id)
	{
		(*fir_fork) = &philo->m_fork;
		(*sec_fork) = &philo->neighbor->m_fork;
	}
	else
	{
		(*fir_fork) = &philo->neighbor->m_fork;
		(*sec_fork) = &philo->m_fork;
	}
}
