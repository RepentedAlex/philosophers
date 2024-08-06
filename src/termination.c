/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:12:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 14:15:09 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "termination.h"
#include "utils.h"

int	termination(t_frame *frame)
{
	printf("\nStarting termination sequence.\n");
	free_list(&frame->head, frame->nb_of_philo);
	return (printf("Program terminated successfully!\n"), NO_ERROR);
}
