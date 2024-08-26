/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:57:34 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/13 16:57:34 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// \brief Converts a string-written number into an int.
/// \param str The number written in an array of character.
/// \return The number in an integer.
int	ft_atoi(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] == 9 || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret);
}

void	ft_exit(t_ruleset *ruleset)
{
	int	i;

	if (!ruleset)
		return ;
	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		pthread_mutex_destroy(&ruleset->philos_array[i].philo_lock);
		pthread_mutex_destroy(&ruleset->philos_array[i].fork);
		i++;
	}
	free(ruleset->philos_array);
	pthread_mutex_destroy(&ruleset->ruleset_lock);
	free(ruleset);
}

void	join_all_threads(t_ruleset *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		pthread_join(ruleset->philos_array[i].tid, NULL);
		i++;
	}
}

void	ft_error(char *str, t_ruleset *ruleset)
{
	printf("%s\n", str);
	ft_exit(ruleset);
}

int	ft_mprintf(char *str, t_philo *philo)
{
	static pthread_mutex_t	printf_lock = PTHREAD_MUTEX_INITIALIZER;
	int						ret;

	pthread_mutex_lock(&printf_lock);
	if (!philo)
		ret = printf("%s", str);
	else
		ret = printf("%ld %d %s", get_time() - philo->ruleset->start_time, philo->id,
					 str);
	pthread_mutex_unlock(&printf_lock);
	return (ret);
}
