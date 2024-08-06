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

struct s_test
{
	int deposit;
	pthread_mutex_t	*lock;
};

int balance = 0;

void write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

int read_balance()
{
	usleep(250000);
	return (balance);
}

void	*deposit(struct s_test arg)
{
	pthread_mutex_lock(arg.lock);

	int account_balance = read_balance();

	account_balance += arg.deposit;

	write_balance(account_balance);

	pthread_mutex_unlock(arg.lock);

	return (NULL);
}

int	main()
{
	int before = read_balance();
	printf("Before: %d\n", before);

	pthread_t tid1;
	pthread_t tid2;
	pthread_mutex_t	lock;

	struct s_test deposit1 = {300, &lock};
	struct s_test deposit2 = {200, &lock};

	pthread_mutex_init(&lock, NULL);
	pthread_create(&tid1, NULL, (void*) deposit, &deposit1);
	pthread_create(&tid2, NULL, (void*) deposit, &deposit2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&lock);

	int after = read_balance();
	printf("After: %d\n", after);

	return (0);
}