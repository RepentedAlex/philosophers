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

#ifndef INITIALISATION_H
# define INITIALISATION_H

# include "philosophers.h"

//-----MAIN FUNCTION-----//
t_error initialisation(int argc, char *argv[], t_frame *frame);

//-----SUBSIDIARY FUNCTIONS-----//
t_error set_program_parameters(int argc, char *argv[], t_frame *frame);
t_error ft_init_table(t_frame *frame);

//-----UTILITIES-----//
t_error check_args(int argc, char *argv[], t_frame *frame);
t_error check_valid_args(char *argv[]);

#endif
