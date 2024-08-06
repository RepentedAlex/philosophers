/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:38:57 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 13:51:41 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialisation.h"
#include "utils.h"

int initialisation(int argc, char *argv[], t_frame *frame)
{
	memset(frame, 0, sizeof(*frame));
	printf("Setting program's parameters...\n");
	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"), ERROR);
	if (set_program_parameters(argc, argv, frame))
		return (printf("Error: Invalid arguments.\n"), ERROR);
	if (ft_init_table(frame))
		return (printf("Error: Couldn't initialise table.\n"), ERROR);
	return (printf("Program initialised.\n"), NO_ERROR);
}

int set_program_parameters(int argc, char *argv[], t_frame *frame)
{
	if (check_valid_args(argv))
		return (ERROR);
	frame->nb_of_philo = ft_atoi(argv[1]);
	frame->time_to_die = (time_t)ft_atoi(argv[2]);
	frame->time_to_eat = (time_t)ft_atoi(argv[3]);
	frame->time_to_sleep = (time_t)ft_atoi(argv[4]);
	if (argc == 6)
		frame->nb_time_eat = ft_atoi(argv[5]);
	if (check_args(argc, argv, frame))
		return (ERROR);
	return (NO_ERROR);
}

int	ft_init_table(t_frame *frame)
{
	int	i;

	i = 0;
	while (++i <= frame->nb_of_philo)
		if (add_to_list(&frame->head, i))
			return (free_list(&frame->head, frame->nb_of_philo), ERROR);
	return (NO_ERROR);
}

int check_valid_args(char *argv[])
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (ERROR);
		i++;
	}
	return (NO_ERROR);
}



int check_args(int argc, char *argv[], t_frame *frame)
{
	char	*tmp;

	tmp = ft_itoa(frame->nb_of_philo);
	if (ft_strncmp(argv[1], tmp, 512))
		return (free(tmp), ERROR);
	free(tmp);
	tmp = ft_itoa(frame->time_to_die);
	if (ft_strncmp(argv[2], tmp, 512))
		return (free(tmp), ERROR);
	free(tmp);
	tmp = ft_itoa(frame->time_to_eat);
	if (ft_strncmp(argv[3], tmp, 512))
		return (free(tmp), ERROR);
	free(tmp);
	tmp = ft_itoa(frame->time_to_sleep);
	if (ft_strncmp(argv[4], tmp, 512))
		return (free(tmp), ERROR);
	if (argc == 6)
	{
		free(tmp);
		tmp = ft_itoa(frame->nb_time_eat);
		if (ft_strncmp(argv[5], tmp, 512))
			return (free(tmp), ERROR);
	}
	return (free(tmp), NO_ERROR);
}