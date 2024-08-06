/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:38:57 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 11:39:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_INITIALISATION_H
#define PHILOSOPHERS_INITIALISATION_H

#include "philosophers.h"


//-----MAIN FUNCTION-----//
int initialisation(int argc, char *argv[], t_frame *frame);

//-----SUBSIDIARIES FUNCTIONS-----//
int set_program_parameters(int argc, char *argv[], t_frame *frame);
int	ft_init_table(t_frame *frame);

//-----UTILITIES-----//
int check_args(int argc, char *argv[], t_frame *frame);
int check_valid_args(char *argv[]);

#endif
