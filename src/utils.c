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

int	ft_atoi(const char *num)
{
	int	i;
	int	ret;
	int	sign;

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

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size > __SIZE_MAX__ / nmemb)
		return (NULL);
	pointer = NULL;
	pointer = malloc(nmemb * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, nmemb * size);
	return (pointer);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == '-' || c == '+')
		return (c);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	if (n == 0 || !s1 || !s2)
		return (0);
	i = 0;
	if (s1[i + 1] && s1[i] == '+')
		s1++;
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			return (result);
		}
		i++;
	}
	return (0);
}

t_error check_valid_args(char *argv[], t_ruleset *ruleset)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (ft_error("Error invalid arguments.\n", ruleset), ERROR);
		i++;
	}
	return (NO_ERROR);
}
