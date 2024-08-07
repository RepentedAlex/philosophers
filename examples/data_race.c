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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void	*routine()
{
	for (int i = 0; i < 1000000; ++i)
	{
		mails++;
	}
}

int main(int argc, char *argv[])
{
	pthread_t	thread1, thread2;

	if (pthread_create(&thread1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&thread2, NULL, &routine, NULL))
		return (2);

	if (pthread_join(thread1, NULL))
		return (3);
	if (pthread_join(thread2, NULL))
		return (4);
	printf("Number of mail: %d\n", mails);
	return (0);
}