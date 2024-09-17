/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:13:34 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/17 14:04:42 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	increment_replete_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->ruleset->m_replete);
	philo->ruleset->nb_replete++;
	pthread_mutex_unlock(&philo->ruleset->m_replete);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*fir_fork;
	pthread_mutex_t	*sec_fork;

	edge_handler(philo, &fir_fork, &sec_fork);
	pthread_mutex_lock(fir_fork);
	ft_mprintf("has taken a fork\n", philo);
	pthread_mutex_lock(sec_fork);
	ft_mprintf("has taken a fork\n", philo);
	update_philo(philo);
	ft_mprintf("is eating\n", philo);
	usleep(philo->ruleset->time_to_eat * 1000 - 100);
	pthread_mutex_lock(&philo->ruleset->m_eating);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->ruleset->m_eating);
	pthread_mutex_unlock(fir_fork);
	pthread_mutex_unlock(sec_fork);
	if (should_i_stop(philo))
		return ;
	philo_sleep(philo);
}

void	edge_handler(t_philo *philo, pthread_mutex_t **fir_fork, \
pthread_mutex_t **sec_fork)
{
	if (philo->ruleset->number_of_philosophers == 3)
	{
		three_philos(philo, fir_fork, sec_fork);
	}
	else
	{
		if (philo->id % 2)
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
}

void	philo_sleep(t_philo *philo)
{
	ft_mprintf("is sleeping\n", philo);
	usleep(philo->ruleset->time_to_sleep * 1000);
	if (should_i_stop(philo))
		return ;
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	ft_mprintf("is thinking\n", philo);
	usleep((philo->ruleset->time_to_die - (philo->ruleset->time_to_eat + \
	philo->ruleset->time_to_sleep)) * 1000 / 2);
}
