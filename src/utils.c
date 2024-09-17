/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:24 by apetitco          #+#    #+#             */
/*   Updated: 2024/09/13 18:46:27 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(u_int64_t	time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] == 9 || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret);
}

t_error	check_input(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ERROR);
			j++;
		}
		i++;
	}
	return (NO_ERROR);
}

int	ft_mprintf(char *str, t_philo *philo)
{
	static pthread_mutex_t	printf_lock = PTHREAD_MUTEX_INITIALIZER;
	int						ret;

	pthread_mutex_lock(&printf_lock);
	pthread_mutex_lock(&philo->ruleset->m_stop);
	if (philo->ruleset->stop)
	{
		pthread_mutex_unlock(&printf_lock);
		pthread_mutex_unlock(&philo->ruleset->m_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->ruleset->m_stop);
	ret = printf("%ld %d %s", get_time() - philo->ruleset->start_time, \
	philo->id, str);
	pthread_mutex_unlock(&printf_lock);
	return (ret);
}

u_int64_t	get_time(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}
