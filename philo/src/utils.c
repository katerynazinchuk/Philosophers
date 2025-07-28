/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:19:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/28 16:11:43 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	number;
	int			sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		if (number * sign > INT_MAX)
			return (INT_MAX);
		if (number * sign < INT_MIN)
			return (INT_MIN);
		i++;
	}
	return (number * sign);
}

long	find_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000) + (ct.tv_usec / 1000));
}

void	print_log(t_philo *philo, char *str)
{
	long	timestamp;

	pthread_mutex_lock(&philo->input->print_lock);
	if (!philo->input->is_dead)
	{
		timestamp = find_time() - philo->input->start_time;
		printf("%-5ld %-3d %s\n", timestamp, philo->ph_id, str);
	}
	pthread_mutex_unlock(&philo->input->print_lock);
}

//left fork is the fork with the same index and 
//right fork is the fork with index n + 1
// left fork = N
// right fork = (N + 1) % number of philosophers;

// even number take first left
// unever take first right
//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.