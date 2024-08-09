/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:23:01 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/09 15:54:01 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_ruleset(t_ruleset *ruleset)
{
	if (ruleset->tid)
		free(ruleset->tid);
	if (ruleset->forks)
		free(ruleset->forks);
	if (ruleset->philos)
		free(ruleset->philos);
}

void	ft_exit(t_ruleset *ruleset)
{
	int	i;

	i = -1;
	while (++i < ruleset->nb_philos)
	{
		pthread_mutex_destroy(&ruleset->forks[i]);
		pthread_mutex_destroy(&ruleset->philos[i].lock);
	}
	pthread_mutex_destroy(&ruleset->write);
	pthread_mutex_destroy(&ruleset->lock);
	clear_ruleset(ruleset);
}

int	ft_error(char *str, t_ruleset *ruleset)
{
	printf("%s", str);
	if (ruleset)
		ft_exit(ruleset);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_ruleset	ruleset;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"));
	if (check_valid_args(argv, &ruleset))
		return (1);
	if (ft_init(argv, &ruleset))
		return (ERROR);
}
