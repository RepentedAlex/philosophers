/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_race.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:54:26 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:30 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define BIG 1000000000UL

void *change_a(void *arg)
{
	u_int32_t *a = (u_int32_t *)arg;
	for(u_int32_t i = 0; i < BIG; i++)
		(*a)++;
	return (NULL);
}

int main()
{
	pthread_t thread_1;
	pthread_t thread_2;
	u_int32_t a;

	a = 0;
	pthread_create(&thread_1, NULL, change_a, &a);
	pthread_create(&thread_2, NULL, change_a, &a);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("a is: %u\n", a);
}