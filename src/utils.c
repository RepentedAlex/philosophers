/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:11:04 by apetitco          #+#    #+#             */
/*   Updated: 2024/06/11 13:17:03 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long ft_atoll(const char *num)
{
	long long i;
	long long ret;
	int sign;

	i = 0;
	sign = 1;
	ret = 0;
	while (num[i] == 32 || num[i] == 9)
		i++;
	if (num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			sign = -1;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
		ret = ret * 10 + (num[i++] - '0');
	return (ret * sign);
}

t_philosopher	*new_node(int id)
{
	t_philosopher	*node;

	node = malloc(sizeof(t_philosopher));
	if (!node)
		return (NULL);
	memset(node, 0, sizeof(t_philosopher));
	node->id = id;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int free_list(t_philosopher **head, long long nb_philo)
{
	int				i;
	t_philosopher	*nav;
	t_philosopher	*tmp;

	i = 0;
	if (!head)
		return (ERROR);
	nav = *head;
	while (i < nb_philo)
	{
		tmp = nav->next;
		memset(nav, 0, sizeof(t_philosopher));
		free(nav);
		nav = tmp;
		i++;
	}
	return (NO_ERROR);
}

int	add_to_list(t_philosopher **head, int id)
{
	t_philosopher	*node;

	node = new_node(id);
	if (!node)
		return (ERROR);
	if (*head == NULL)
	{
		*head = node;
		(*head)->prev = *head;
		(*head)->next = *head;
	}
	else
	{
		node->prev = (*head)->prev;
		node->next = *head;
		(*head)->prev->next = node;
		(*head)->prev = node;
	}
	return (NO_ERROR);
}

int	ft_init_table(int argc, char *argv[], t_frame *frame)
{
	int	i;

	i = 1;
	memset(frame, 0, sizeof(t_frame));
	frame->head = NULL;
	frame->nb_of_philo = ft_atoll(argv[1]);
	if (argc == 6)
		frame->nb_time_eat = ft_atoll(argv[5]);
	while (i <= frame->nb_of_philo)
	{
		if (add_to_list(&frame->head, i))
			return (free_list(&frame->head, frame->nb_of_philo), ERROR);
		i++;
	}
	return (NO_ERROR);
}
