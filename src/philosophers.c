/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:23:01 by apetitco          #+#    #+#             */
/*   Updated: 2024/06/11 13:20:26 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "initialisation.h"
#include "termination.h"
#include "debug.h"

int	main(int argc, char *argv[])
{
	t_frame	frame;

	if (initialisation(argc, argv, &frame))
		return (printf("An error has occurred at startup.\n"), 1);
	if (termination(&frame))
		return (printf("philo encountered an error while closing.\n"), 2);
}
