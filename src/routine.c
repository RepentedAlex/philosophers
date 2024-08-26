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
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	while (!philo->ruleset->stop && philo->status != replete)
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		if (philo->ruleset->max_meals != -1 && \
		philo->nb_of_meals >= philo->ruleset->max_meals)
			return (set_philo_replete(philo));
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->status != eating && (get_time() - \
		philo->last_meal > philo->ruleset->time_to_die))
			set_philo_dead(philo);
		else
			pthread_mutex_unlock(&philo->philo_lock);
		if (first_round == 0)
			do_first_round(philo, &first_round);
		else if (philo_eat(philo))
			philo_sleep(philo);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
}

static void	internal_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->neighbor->philo_lock);
	ft_mprintf("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->philo_lock);
	ft_mprintf("has taken a fork\n", philo);
	philo->status = eating;
	ft_mprintf("is eating\n", philo);
	ft_usleep(philo->ruleset->time_to_eat);
	pthread_mutex_unlock(&philo->neighbor->philo_lock);
	pthread_mutex_unlock(&philo->philo_lock);
}

int	philo_eat(t_philo *philo)
{
	if (check_stop(philo) == true)
		return (1);
	internal_philo_eat(philo);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
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
	philo->status = sleeping;
	ft_mprintf("is sleeping\n", philo);
	ft_usleep(philo->ruleset->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	if (check_stop(philo) == true)
		return ;
	philo->status = thinking;
	ft_mprintf("is thinking\n", philo);
}
