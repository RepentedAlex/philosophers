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
	eating = 2
}				t_states;

struct	s_philo;

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
}				t_ruleset;

typedef struct	s_philo
{
	t_ruleset		*ruleset;
	int				id;
	pthread_t		tid;
	time_t			last_meal;
	t_states 		status;
	int				nb_of_meals;
	pthread_mutex_t	l_fork;
	struct	s_philo	*neighbor[2];
}				t_philo;

//----- INITIALISATION -----//
t_error	check_input(char *argv[]);
t_error	init_philos(t_ruleset *ruleset);
t_error	init_simu(t_ruleset *ruleset);
t_error parsing(int argc, t_ruleset *ruleset, char *argv[]);

//----- ROUTINE -----//
void	routine(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//----- UTILS -----//
int		ft_atoi(const char *str);
void	ft_error(char *str, t_ruleset *ruleset);
void	ft_exit(t_ruleset *ruleset);
time_t	get_time(void);
int 	ft_usleep(u_int64_t time);
void	join_all_threads(t_ruleset *ruleset);

#endif
