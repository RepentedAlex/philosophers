/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:49:17 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/21 17:49:30 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL))
		return ((time_t)NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

int	ft_usleep(u_int64_t	time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	wait_for_start(t_philo *philo, int *first_round)
{
	if (first_round)
		*first_round = 0;
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	while (!philo->ruleset->start_time)
	{
		pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
		ft_usleep(100);
		pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	}
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	pthread_mutex_lock(&philo->philo_lock);
	philo->remaining_time = philo->ruleset->start_time;
	pthread_mutex_unlock(&philo->philo_lock);
}

bool	check_stop(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	if (philo->ruleset->stop)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	return (ret);
}

void	set_philo_replete(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->status = replete;
	ft_mprintf("is replete\n", philo);
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	philo->ruleset->nb_replete_philos++;
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	pthread_mutex_unlock(&philo->philo_lock);
}
