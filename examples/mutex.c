/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_race.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:15:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 18:15:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	mutex_fuel;
pthread_cond_t	cond_fuel;
int 			fuel = 0;

void	*fuel_filling(void *arg)
{
	for (int i = 0; i < 5 ; i++)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 30;
		printf("Filled fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_broadcast(&cond_fuel);
		sleep(1);
	}
}

void	*car(void *arg)
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel < 40)
	{
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
}

int main()
{
	pthread_t	t_id[2];

	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);
	for (int i = 0; i < 6; i++)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&t_id[i], NULL, &fuel_filling, NULL))
				perror("Failed to create thread.\n");
		}
		else if (pthread_create(&t_id[i], NULL, &car, NULL))
		{
			perror("Failed to create thread.\n");
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (pthread_join(t_id[i], NULL))
			perror("Failed to joind thread.\n");
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return (0);
}