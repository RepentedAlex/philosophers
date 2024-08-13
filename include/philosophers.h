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

#include <stdbool.h>

typedef bool t_error;

#define ERROR 1
#define NO_ERROR 0

//----- INITIALISATION -----//
t_error	check_input(int argc, char *argv[]);

#endif
