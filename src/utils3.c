/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:15:20 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/21 18:15:48 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_philo_dead(t_philo *philo)
{
	philo->status = dead;
	ft_mprintf("died.\n", philo);
	pthread_mutex_lock(&philo->ruleset->ruleset_lock);
	philo->ruleset->stop = 1;
	pthread_mutex_unlock(&philo->ruleset->ruleset_lock);
	pthread_mutex_unlock(&philo->philo_lock);
}

void	do_first_round(t_philo *philo, int *flag)
{
	if (philo->id % 3 == 0)
		philo_eat(philo);
	else
		philo_think(philo);
	*flag = 1;
}

/// @brief Checks for invalid characters in the passed arguments.
/// @param argc Number of CLI arguments.
/// @param argv CLI arguments.
/// @return ERROR(1) if a non-digit character is encountered, else NO_ERROR(O).
t_error	check_input(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ERROR);
			j++;
		}
		i++;
	}
	return (NO_ERROR);
}

void	lonely_philo(t_philo *philo)
{
	ft_usleep(philo->ruleset->time_to_die);
	set_philo_dead(philo);
}
