/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:05:37 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 14:05:39 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_error	free_list(t_philosopher **head, long long nb_philo)
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
	memset(head, 0, sizeof(t_philosopher *));
	return (NO_ERROR);
}

t_error	add_to_list(t_philosopher **head, int id)
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
