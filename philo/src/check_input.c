/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:41:36 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/28 16:17:25 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	number_of_arg(int argc)
{
	if (argc < 5)
	{
		printf("Pleae provide a full list of required arguments\n");
		return (1);
	}
	if (argc > 6)
	{
		printf("Too many arguments\n");
		return (1);
	}
	return (0);
}

static int	is_numeric_inpt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **str)
{
	int	i;
	int	a;

	i = 1;
	if (number_of_arg(argc))
		return (0);
	while (str[i])
	{
		if (!is_numeric_inpt(str[i]))
		{
			printf("Numeric input required\n");
			return (0);
		}
		a = ft_atoi(str[i]);
		if (i == 1 && (a > 200 || a <= 0))
		{
			printf("Number of philosophers should be between 1 and 200\n");
			return (0);
		}
		i++;
	}
	return (1);
}
