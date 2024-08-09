/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:23:01 by apetitco          #+#    #+#             */
/*   Updated: 2024/06/11 13:17:03 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
#include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MIN_PHILOS 1
# define MAX_PHILOS 200

typedef bool	t_error;

# define ERROR 1
# define NO_ERROR 0

struct	s_philo;

typedef struct	s_ruleset
{
	pthread_t		*tid;
	int 			nb_philos;
	int 			max_meals;
	int 			dead;
	struct s_philo	*philos;
	time_t			death_time;
	time_t 			eat_time;
	time_t			sleep_time;
	time_t 			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}				t_ruleset;

typedef struct	s_philo
{
	t_ruleset		*ruleset;
	pthread_t		tid;
	int 			id;
	int 			meals_eaten;
	int 			status;	// -1 dead ; 0 sleeping ; 1 thinking ; 2 sleeping
	time_t			time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

//----- INITIALISATION -----//
t_error ft_init(char **argv, t_ruleset *ruleset);
t_error	ft_init_data(char **argv, t_ruleset *ruleset);
t_error	ft_init_forks(t_ruleset *ruleset);

//----- CHECKERS -----//
t_error check_valid_args(char *argv[], t_ruleset *ruleset);

//----- ERROR HANDLING -----//
void	clear_ruleset(t_ruleset *ruleset);
int		ft_error(char *str, t_ruleset *ruleset);
void	ft_exit(t_ruleset *ruleset);

//----- UTILITIES -----//
int	ft_atoi(const char *num);

#endif
