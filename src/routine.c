/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:32:10 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/20 16:03:00 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_philo *philo)
{
	int	first_round;

	wait_for_start(philo, &first_round);
	if (philo->ruleset->number_of_philosophers == 1)
		return (lonely_philo(philo));
	if (pthread_create(&philo->observator, NULL, (void *)&monitor, \
	(void *)philo))
		return ;
	first_round = 0;
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	while (!philo->ruleset->stop && philo->status != replete)
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		if (philo->ruleset->max_meals != -1 && \
		philo->nb_of_meals >= philo->ruleset->max_meals)
			return (set_philo_replete(philo));
		philo_eat(philo);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
}

static void	internal_philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		ft_mprintf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->neighbor->fork);
		ft_mprintf("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->neighbor->fork);
		ft_mprintf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->fork);
		ft_mprintf("has taken a fork\n", philo);
	}
	philo_status_updater(philo, eating);
	ft_mprintf("is eating\n", philo);
	ft_usleep(philo->ruleset->time_to_eat);
	pthread_mutex_unlock(&philo->neighbor->fork);
	pthread_mutex_unlock(&philo->fork);
}

int	philo_eat(t_philo *philo)
{
	if (check_stop(philo) == true)
		return (1);
	internal_philo_eat(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->nb_of_meals++;
	philo->time_remaining = get_time() + philo->ruleset->time_to_die + \
	philo->ruleset->time_to_sleep;
	pthread_mutex_unlock(&philo->philo_lock);
	philo_sleep(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo)
		return ;
	if (check_stop(philo) == true)
		return ;
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->status == replete)
		return ((void) pthread_mutex_unlock(&philo->philo_lock));
	else
		pthread_mutex_unlock(&philo->philo_lock);
	philo_status_updater(philo, sleeping);
	ft_mprintf("is sleeping\n", philo);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	if (check_stop(philo) == true)
		return ;
	philo_status_updater(philo, thinking);
	ft_usleep(philo->time_to_think);
	ft_mprintf("is thinking\n", philo);
}
