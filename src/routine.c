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
	if (pthread_create(&philo->supervis, NULL, (void *) \
    &supervisor, (void*)&philo))
		return ;
	while (!philo->dead && !philo->ruleset->stop)
	{
		philo_eat(philo);
	}
	if (pthread_join(philo->supervis, NULL))
		return ;
}

static void	internal_philo_eat(t_philo *philo)
{
	if (!philo)
		return ;
	ft_mprintf("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->philo_lock);
	pthread_mutex_lock(&philo->neighbor->philo_lock);
	ft_mprintf("has taken his neighbor's fork\n", philo);
	philo->status = eating;
	ft_mprintf("is eating\n", philo);
	ft_usleep(philo->ruleset->time_to_eat);
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_unlock(&philo->neighbor->philo_lock);
}

int	philo_eat(t_philo *philo)
{
	if (check_stop(philo) == true)
		return (1);
	internal_philo_eat(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->remaining_time = get_time();
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(&philo->philo_lock);
	philo_sleep(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo)
		return ;
	if (check_stop(philo) == true)
		return ;
	if (philo->status == replete)
		return ;
	pthread_mutex_lock(&philo->philo_lock);
	philo->status = sleeping;
	pthread_mutex_unlock(&philo->philo_lock);
	ft_mprintf("is sleeping\n", philo);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->status = thinking;
	pthread_mutex_unlock(&philo->philo_lock);
	ft_mprintf("is thinking\n", philo);
}
