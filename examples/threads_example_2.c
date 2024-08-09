/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_example_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:44:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/09 12:44:22 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine()
{
	printf("Test from threads.\n");
	sleep(3);
	printf("Ending thread.\n");
}

int main(int argc, char *argv[])
{
	pthread_t	thread_1;
	pthread_t	thread_2;

	if (pthread_create(&thread_1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&thread_2, NULL, &routine, NULL))
		return (2);

	if (pthread_join(thread_1, NULL))
		return (3);
	if (pthread_join(thread_2, NULL))
		return (4);

	return (0);
}