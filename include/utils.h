/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:32:00 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 12:32:43 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philosophers.h"

t_error free_list(t_philosopher **head, long long nb_philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c);

#endif
