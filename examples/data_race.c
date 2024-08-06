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

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int balance = 0;

int write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

int read_balance()
{
	usleep(250000);
	return (balance);
}

void	*deposit(void *amount)
{
	int account_balance = read_balance();

	account_balance += *((int *)amount);

	write_balance(account_balance);

	return (NULL);
}

int	main()
{
	int before = read_balance();
	printf("Before: %d\n", balance);

	pthread_t tid1;
	pthread_t tid2;

	int deposit1 = 300;
	int deposit2 = 200;

	pthread_create(&tid1, NULL, deposit, (void*) &deposit1);
	pthread_create(&tid2, NULL, deposit, (void*) &deposit2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	int after = read_balance();
	printf("After: %d\n", after);

	return (0);
}