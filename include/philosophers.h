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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define MIN_PHILO 1
#define MAX_PHILO 200

typedef bool t_error;

#define ERROR 1
#define NO_ERROR 0

typedef enum	e_states
{
	dead = -1,
	sleeping = 0,
	thinking = 1,
	eating = 2,
	replete = 3
}				t_states;

struct	s_philo;

/*!
 * @brief
 * @var	number_of_philosophers The total number of philosophers.
 * @var	*philos_array Pointer to the table of philosophers.
 * @var	time_to_die Max time before a philo dies of starvation.
 * @var	time_to_eat Duration of a meal.
 * @var	time_to_sleep Duration of a nap.
 * @var	max_meals Number of meals a philo must eat to be replete.
 * @var	start_time Simulation start timestamp.
 * @var	nb_replete_philos Counter for the number of philos that are replete.
 * @var	stop Flag that signals the end of the simulation.
 */
typedef struct	s_ruleset
{
	int				number_of_philosophers;
	struct s_philo	*philos_array;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				max_meals;
	time_t			start_time;
	int				nb_replete_philos;
	bool			stop;
	pthread_mutex_t	ruleset_lock;
}				t_ruleset;

/// @brief	Structure bearing
/// @var	*ruleset Pointer to the structure holding the ruleset for the simu.
/// @var	id The philosopher unique ID.
/// @var	tid The thread ID for the corresponding philosopher.
/// @var	last_meal Last meal's timestamp.
/// @var	status The philosopher's status
/// @var	is_replete Flag that signals if the philo ate `max_meals` meals.
/// @var	nb_of_meals Number of meals the philosopher ate.
/// @var	fork Mutex for the philosopher's fork.
/// @var	philo_lock
/// @var	*neighbor[2] Pointers to the philosopher's neighbor.
typedef struct	s_philo
{
	t_ruleset		*ruleset;
	int				id;
	pthread_t		tid;
	pthread_t		observator;
	time_t			last_meal;
	t_states 		status;
	int				nb_of_meals;
	pthread_mutex_t	philo_lock;
	struct	s_philo	*neighbor[2];
}				t_philo;

//----- INITIALISATION -----//
t_error	check_input(char *argv[]);
t_error	init_philos(t_ruleset *ruleset);
t_error	init_simu(t_ruleset *ruleset);
t_error parsing(int argc, t_ruleset *ruleset, char *argv[]);

//----- ROUTINE -----//
void 	routine(t_philo *philo);
int philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//----- UTILS -----//
int		check_simu_stop(t_ruleset *ruleset);
int		ft_atoi(const char *str);
void	ft_error(char *str, t_ruleset *ruleset);
void	ft_exit(t_ruleset *ruleset);
int		ft_mprintf(char *str, t_philo *philo);
time_t	get_time(void);
int 	ft_usleep(u_int64_t time);
void	join_all_threads(t_ruleset *ruleset);

#endif
