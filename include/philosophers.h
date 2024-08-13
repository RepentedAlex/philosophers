/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:42:44 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:44 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdbool.h>
#include <sys/time.h>

#define MIN_PHILO 1
#define MAX_PHILO 200

typedef bool t_error;

#define ERROR 1
#define NO_ERROR 0

typedef struct	s_ruleset
{
	int		number_of_philosophers;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		max_meals;
}				t_ruleset;

//----- INITIALISATION -----//
t_error	check_input(char *argv[]);
t_error parsing(int argc, t_ruleset *ruleset, char *argv[]);

#endif
