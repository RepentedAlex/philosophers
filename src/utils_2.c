/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:06:52 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/06 14:09:00 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

static int	ft_get_nb_len(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static unsigned char	*ft_transcribe_nb(char *dst, long n, int len)
{
	dst[len] = 0;
	len--;
	while (len >= 0 && dst[len] != '-')
	{
		if (n == 10)
		{
			dst[len] = '0';
			dst[len - 1] = '1';
			return ((unsigned char *)dst);
		}
		if (n >= 0 && n <= 9)
		{
			dst[len] = (char)(n + '0');
			return ((unsigned char *)dst);
		}
		if (n > 10)
		{
			dst[len] = (char)((n % 10) + '0');
			n /= 10;
		}
		len--;
	}
	return ((unsigned char *)dst);
}

//Need to convert it to a long to ascii in order to handle time_t variables
char	*ft_itoa(int n)
{
	char	*ascii;
	int		n_len;

	n_len = ft_get_nb_len((long int)n);
	ascii = ft_calloc(n_len + 1, sizeof(char));
	if (!ascii)
		return (NULL);
	if ((long int)n < 0)
	{
		ascii[0] = '-';
		ft_transcribe_nb(ascii, (long int)n * -1, n_len);
	}
	else
		ft_transcribe_nb(ascii, (long int)n, n_len);
	return (ascii);
}