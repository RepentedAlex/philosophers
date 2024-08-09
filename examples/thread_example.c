/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:24:45 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/09 12:24:45 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void	*computation(void *add)
{
	long	sum = 0;
	long	*add_sum = (long*)add;

	for (long i = 0; i < 1000000000; ++i)
	{
		sum += *add_sum;
	}
	printf("Add: %ld\n", *add_sum);
	return (NULL);
}

int	main()
{
	pthread_t	thread1;
	pthread_t	thread2;
	long		value1 = 1;
	long		value2 = 2;

	pthread_create(&thread1, NULL, computation, (void *)&value1);
	pthread_create(&thread2, NULL, computation, (void *)&value2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return (0);
}