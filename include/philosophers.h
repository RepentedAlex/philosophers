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

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define MIN_PHILO 1
#define MAX_PHILO 200

typedef bool t_error;

#define ERROR 1
#define NO_ERROR 0

struct	s_philo;

typedef struct	s_ruleset
{
	struct s_philo	*philos;
	int				number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				max_meals;
	time_t			start_time;
	int				nb_replete_philos;
	int				stop;
	pthread_mutex_t	*write;
}				t_ruleset;

typedef struct	s_philo
{
	t_ruleset		*ruleset;
	int				id;
	pthread_t		tid;
	time_t			last_meal;
	int				status;
	int				nb_of_meals;
	int				state;
	pthread_mutex_t	lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

//----- INITIALISATION -----//
t_error	check_input(char *argv[]);
t_error parsing(int argc, t_ruleset *ruleset, char *argv[]);

#endif
