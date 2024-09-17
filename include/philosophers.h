/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:28:18 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/17 13:52:29 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define MIN_PHILO 1
# define MAX_PHILO 200

typedef bool	t_error;

# define ERROR 1
# define NO_ERROR 0

typedef enum e_states
{
	dead = -1,
	sleeping = 0,
	thinking = 1,
	eating = 2,
	replete = 3
}				t_states;

struct			s_philo;

typedef struct s_ruleset
{
	int				number_of_philosophers;
	struct s_philo	*philos_array;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				max_meals;
	u_int64_t		start_time;
	pthread_mutex_t	m_start;
	int				nb_replete;
	pthread_mutex_t	m_replete;
	bool			stop;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eating;
}				t_ruleset;

typedef struct s_philo
{
	t_ruleset		*ruleset;
	int				id;
	pthread_t		tid;
	t_states		status;
	pthread_mutex_t	m_status;
	u_int64_t		last_meal;
	pthread_mutex_t	m_last_meal;
	int				nb_of_meals;
	int				is_eating;
	pthread_mutex_t	m_nb_of_meals;
	pthread_mutex_t	m_fork;
	struct s_philo	*neighbor;
}				t_philo;

//===== INITIALISATION PHASE =====//
t_error		check_input(char *argv[]);
t_error		parsing(int argc, t_ruleset *ruleset, char *argv[]);
t_error		ft_init_philos(t_ruleset *ruleset);
t_error		ft_mutex_initialise(t_ruleset *ruleset);
t_error		ft_thread_initialise(t_ruleset *ruleset);

//===== ROUTINE =====//
void		*routine(void *v_philo);
bool		should_i_stop(t_philo *philo);
void		philo_eat(t_philo *philo);
void		edge_handler(t_philo *philo, pthread_mutex_t **fir_fork, \
pthread_mutex_t **sec_fork);
void		three_philos(t_philo *philo, pthread_mutex_t **fir_fork, \
pthread_mutex_t **sec_fork);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		supervisor(t_ruleset *ruleset);
void		increment_replete_philos(t_philo *philo);
void		update_philo(t_philo *philo);

//===== EXIT =====//
t_error		join_all_threads(t_ruleset *ruleset);
void		ft_exit(t_ruleset *ruleset);

//===== UTILITARIES =====//
int			ft_atoi(const char *str);
int			ft_mprintf(char *str, t_philo *philo);
//void		ft_usleep(u_int64_t	time);
u_int64_t	get_time(void);
void		wait_for_start(t_ruleset *ruleset);

#endif
