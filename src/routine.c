/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*   Created: 2024/08/16 15:32:06 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/16 15:32:10 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_philo *philo)
{
	while (!philo->ruleset->stop)
	{
		if (philo->id % 2 == 0)
		{
			philo_sleep(philo);
			philo_eat(philo);
		}
		if (philo->id % 2 != 0)
		{
			philo_eat(philo);
			philo_sleep(philo);
		}
	}
}

void	philo_eat(t_philo *philo)
{
	philo->status = eating;
	printf("%ld : philo [%d] is eating...\n", get_time(), philo->id);
	ft_usleep(philo->ruleset->time_to_eat);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	philo->status = thinking;
}

void	philo_sleep(t_philo *philo)
{
	if (!philo)
		return;
	philo->status = sleeping;
	printf("%ld : philo [%d] is sleeping...\n", get_time(), philo->id);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo->status = thinking;
}

void	philo_think(t_philo *philo)
{
	philo->status =thinking;
	printf("%ld : philo [%d] is thinking...\n", get_time(), philo->id);
}