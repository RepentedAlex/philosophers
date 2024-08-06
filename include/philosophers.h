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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define ERROR 1
# define NO_ERROR 0

typedef enum e_states
{
	eating,
	thinking,
	sleeping
}				t_states;

typedef struct s_philosopher
{
	int						id;
	int						state;
	time_t					last_meal;
	int						fork_state;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
}				t_philosopher;

typedef struct s_frame
{
	int				nb_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_time_eat;
	t_philosopher	*head;
}				t_frame;

int				add_to_list(t_philosopher **head, int id);
int				ft_atoi(const char *num);
t_philosopher	*new_node(int id);

#endif
