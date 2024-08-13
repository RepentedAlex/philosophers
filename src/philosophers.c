/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:43:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:51 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// \brief Checks for invalid characters in the passed arguments.
/// \param argc Number of CLI arguments.
/// \param argv CLI arguments.
/// \return ERROR(1) if a non-digit character is encountered, else NO_ERROR(O).
t_error	check_input(int argc, char *argv[])
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
	}
	return (NO_ERROR);
}

int	main(int argc, char *argv[])
{
	if (check_input(argc, argv))
		return (ERROR);
	return (NO_ERROR);
}