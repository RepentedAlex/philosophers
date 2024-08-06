/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:29 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 14:57:32 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define BIG 1000000000UL

struct s_utils
{
	u_int32_t        *a;
	pthread_mutex_t *a_lock;
};

void *change_a(void *arg)
{
	struct s_utils *utils;

	utils = (struct s_utils *)arg;
	pthread_mutex_lock(utils->a_lock);
	for(u_int32_t i = 0; i < BIG; i++)
		(*(utils->a))++;
	pthread_mutex_unlock(utils->a_lock);
	return (NULL);
}

int main()
{
	pthread_t       thread_1;
	pthread_t       thread_2;
	struct s_utils  utils;
	u_int32_t        a;
	pthread_mutex_t a_lock;

	pthread_mutex_init(&a_lock, NULL);
	utils = (struct s_utils){&a, &a_lock};
	pthread_create(&thread_1, NULL, change_a, &utils);
	pthread_create(&thread_2, NULL, change_a, &utils);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("a is: %u\n", a);
}