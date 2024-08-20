/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:32:10 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/20 13:17:44 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//void	routine(t_philo *philo)
//{
//	while (!philo->ruleset->start_time)
//		ft_usleep(1);
//	philo->last_meal = philo->ruleset->start_time;
//	while (!philo->ruleset->stop && philo->status != replete)
//	{
//
//	}
//	printf("%ld: Philo [%d] is dead\n", get_time(), philo->id);
//}

void routine(t_philo *philo)
{
	int first_round;

	first_round = 0;
	while (!philo->ruleset->start_time)
		ft_usleep(1);
	philo->last_meal = philo->ruleset->start_time;
	while (!philo->ruleset->stop && philo->status != replete)
	{
		if (philo->nb_of_meals >= philo->ruleset->max_meals)
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->status = replete;
			philo->ruleset->nb_replete_philos++;
			pthread_mutex_unlock(&philo->philo_lock);
			return ;
		}
		if (philo->status != eating && (get_time() - philo->last_meal > philo
				->ruleset->time_to_die))
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->status = dead;
			printf("%ld %d died.\n", get_time(), philo->id);
			philo->ruleset->stop = 1;
			pthread_mutex_unlock(&philo->philo_lock);
		}
		if (first_round == 0)
		{
			if (philo->id % 3 == 0)
				philo_eat(philo);
			else
				philo_think(philo);
			first_round = 1;
		}
		else if (philo->neighbor[0]->status != eating ||
		philo->neighbor[1]->status != eating)
			philo_eat(philo);
	}
	printf("Philo [%d] is quitting\n", philo->id);
}

void	philo_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->neighbor[0]->philo_lock) == 0)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->status = eating;
		printf("%ld %d is eating\n", get_time(), philo->id);
		ft_usleep(philo->ruleset->time_to_eat);

		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_unlock(&philo->neighbor[0]->philo_lock);
	}
	else if (pthread_mutex_lock(&philo->neighbor[1]->philo_lock) == 0)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->status = eating;
		printf("%ld %d is eating\n", get_time(), philo->id);
		ft_usleep(philo->ruleset->time_to_eat);
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_unlock(&philo->neighbor[1]->philo_lock);
	}
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	printf("%ld : philo %d meals: %d/%d\n", get_time(),
		   philo->id, philo->nb_of_meals, philo->ruleset->max_meals);
	philo_sleep(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo)
		return;
	philo->status = sleeping;
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	philo->status =thinking;
	printf("%ld %d is thinking\n", get_time(), philo->id);
}