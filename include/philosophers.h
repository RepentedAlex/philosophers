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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define MIN_PHILO 1
# define MAX_PHILO 200

# define ERROR 1
# define NO_ERROR 0

typedef bool	t_error;

typedef enum e_states
{
	eating,
	thinking,
	sleeping
}				t_states;

typedef struct s_philosopher
{
	int						id;
	int						thread_id;
	int						state;
	time_t					last_meal;
	int						nb_dinner;
	int						is_replete;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
	pthread_mutex_t			lock;
	pthread_mutex_t			*fork;
}				t_philosopher;

typedef struct s_frame
{
	int 			*thread_id;
	int				nb_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	int				nb_meals;
	int				nb_philo_replete;
	int				stop;
	t_philosopher	*head;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}				t_frame;

t_error add_to_list(t_philosopher **head, int id);
int				ft_atoi(const char *num);
t_philosopher	*new_node(int id);

#endif
