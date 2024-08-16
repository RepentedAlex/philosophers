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

/// \brief Converts a string-exprimed number into an int.
/// \param str The number exprimed in an array of character.
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
	int i;

	i = 0;
	if (ruleset->philos_array)
	{
		while (i < ruleset->number_of_philosophers)
		{
			if (ruleset->philos_array[i].neighbor)
				free(ruleset->philos_array[i].neighbor);
//			if (ruleset->philos_array[i].l_fork)
//				pthread_mutex_destroy(ruleset->philos_array[i].l_fork);
			i++;
		}
		free(ruleset->philos_array);
	}
}

void	join_all_threads(t_ruleset *ruleset)
{
	int i;

	i = 0;
	while (i < ruleset->number_of_philosophers)
	{
		pthread_join(ruleset->philos_array[i].tid, NULL);
		i++;
	}
}