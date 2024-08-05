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

int	main(int argc, char *argv[])
{
	t_frame	cur_frame;
	t_philosopher	*nav;

	ft_init_table(argc, argv, &cur_frame);
	nav = cur_frame.head;
	for (int i = 0; i < cur_frame.nb_of_philo; ++i)
	{
		printf("Philo id = %d\n", nav->id);
		nav = nav->next;
	}
	free_list(&cur_frame.head, cur_frame.nb_of_philo);
	cur_frame.head = NULL;
	if (!cur_frame.head)
		printf("Liste effacee avec succes\n");
}
