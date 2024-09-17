/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:27:55 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/17 14:17:56 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		pthread_mutex_lock(&ruleset->philos_array[i].m_last_meal);
		pthread_mutex_lock(&ruleset->m_eating);
		if (get_time() > ruleset->philos_array[i].last_meal + \
			ruleset->time_to_die && !ruleset->philos_array[i].is_eating)
		{
			pthread_mutex_unlock(&ruleset->m_eating);
			pthread_mutex_unlock(&ruleset->philos_array[i].m_last_meal);
			ft_mprintf("died\n", &ruleset->philos_array[i]);
			pthread_mutex_lock(&ruleset->philos_array[i].m_status);
			ruleset->philos_array[i].status = dead;
			pthread_mutex_unlock(&ruleset->philos_array[i].m_status);
			pthread_mutex_lock(&ruleset->m_stop);
			ruleset->stop = true;
			pthread_mutex_unlock(&ruleset->m_stop);
			break ;
		}
		pthread_mutex_unlock(&ruleset->m_eating);
		pthread_mutex_unlock(&ruleset->philos_array[i].m_last_meal);
		i++;
	}
}

void	supervisor(t_ruleset *ruleset)
{
	while (1)
	{
		pthread_mutex_lock(&ruleset->m_stop);
		if (ruleset->stop == true)
		{
			pthread_mutex_unlock(&ruleset->m_stop);
			break ;
		}
		pthread_mutex_unlock(&ruleset->m_stop);
		check_death(ruleset);
		pthread_mutex_lock(&ruleset->m_replete);
		if (ruleset->nb_replete >= ruleset->number_of_philosophers)
		{
			pthread_mutex_unlock(&ruleset->m_replete);
			pthread_mutex_lock(&ruleset->m_stop);
			ruleset->stop = true;
			pthread_mutex_unlock(&ruleset->m_stop);
		}
		else
			pthread_mutex_unlock(&ruleset->m_replete);
		usleep(1);
	}
}

bool	should_i_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->ruleset->m_stop);
	pthread_mutex_lock(&philo->m_status);
	if (philo->ruleset->stop || philo->status == dead)
	{
		pthread_mutex_unlock(&philo->ruleset->m_stop);
		pthread_mutex_unlock(&philo->m_status);
		return (true);
	}
	pthread_mutex_unlock(&philo->ruleset->m_stop);
	pthread_mutex_unlock(&philo->m_status);
	return (false);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = v_philo;
	wait_for_start(philo->ruleset);
	if (philo->ruleset->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->m_status);
		while (philo->status != dead)
		{
			pthread_mutex_unlock(&philo->m_status);
			usleep(philo->ruleset->time_to_die);
			pthread_mutex_lock(&philo->m_status);
		}
		pthread_mutex_unlock(&philo->m_status);
	}
	if (philo->id % 2)
		usleep(100);
	while (!should_i_stop(philo))
		philo_eat(philo);
	return (NULL);
}

int	main(const int argc, char *argv[])
{
	t_ruleset	*ruleset;

	ruleset = malloc(sizeof(t_ruleset));
	if (!ruleset)
		return (ERROR);
	if (check_input(argv))
		return (free(ruleset), ERROR);
	if (parsing(argc, ruleset, argv))
		return (free(ruleset), ERROR);
	ruleset->philos_array = malloc(ruleset->number_of_philosophers * \
		sizeof(t_philo));
	if (!ruleset->philos_array)
		return (free(ruleset), ERROR);
	ft_init_philos(ruleset);
	if (ft_mutex_initialise(ruleset))
		return (ft_exit(ruleset), ERROR);
	if (ft_thread_initialise(ruleset))
		return (ft_exit(ruleset), ERROR);
	return (ft_exit(ruleset), NO_ERROR);
}
