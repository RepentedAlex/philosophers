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

void	routine(t_philo *philo) {
	int first_round;

	first_round = 0;
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	while (!philo->ruleset->start_time)
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		ft_usleep(1);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	philo->last_meal = philo->ruleset->start_time;
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	while (!philo->ruleset->stop && philo->status != replete)
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		if (philo->nb_of_meals >= philo->ruleset->max_meals)
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->status = replete;
			philo->ruleset->nb_replete_philos++;
			pthread_mutex_unlock(&philo->philo_lock);
			return ;
		}
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->status != eating && (get_time() - philo->last_meal > philo
				->ruleset->time_to_die))
		{
			philo->status = dead;
			ft_mprintf("died.\n", philo);
			pthread_mutex_lock(&philo->ruleset->ruleset_lock);
			philo->ruleset->stop = 1;
			pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
			pthread_mutex_unlock(&philo->philo_lock);
		}
		else
			pthread_mutex_unlock(&philo->philo_lock);
		if (first_round == 0)
		{
			if (philo->id % 3 == 0)
				philo_eat(philo);
			else
				philo_think(philo);
			first_round = 1;
		}
		else if (philo_eat(philo))
			philo_sleep(philo);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
}

int	philo_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->neighbor[0]->philo_lock) == 0)
	{
//		ft_mprintf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->philo_lock);
//		ft_mprintf("has taken a fork\n", philo);
		philo->status = eating;
//		ft_mprintf("is eating\n", philo);
		ft_usleep(philo->ruleset->time_to_eat);
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_unlock(&philo->neighbor[0]->philo_lock);
	}
	else if (pthread_mutex_lock(&philo->neighbor[1]->philo_lock) == 0)
	{
//		ft_mprintf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->philo_lock);
//		ft_mprintf("has taken a fork\n", philo);
		philo->status = eating;
//		ft_mprintf("is eating\n", philo);
		ft_usleep(philo->ruleset->time_to_eat);
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_unlock(&philo->neighbor[1]->philo_lock);
	}
	else
	{
		return (1);
	}
	philo->last_meal = get_time();
	philo->nb_of_meals++;
//	ft_mprintf("%ld : philo %d meals: %d/%d\n", get_time(),
//		   philo->id, philo->nb_of_meals, philo->ruleset->max_meals);
	philo_sleep(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo)
		return ;
	if (philo->status == replete)
		return ;
	philo->status = sleeping;
//	ft_mprintf("is sleeping\n", philo);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	philo->status = thinking;
//	ft_mprintf("is thinking\n", philo);
}
