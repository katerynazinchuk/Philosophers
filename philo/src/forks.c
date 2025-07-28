/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:05:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/28 13:06:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	odd_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_for_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_for_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_log(philo, "has taken a fork");
	return (0);
}

static int	even_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_for_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (check_for_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_log(philo, "has taken a fork");
	return (0);
}

int	philo_take_fork(t_philo *philo)
{
	if (philo->ph_id % 2 == 1)
		return (odd_philo_take_fork(philo));
	else
		return (even_philo_take_fork(philo));
}

void	philo_put_fork(t_philo *philo)
{
	if (philo->ph_id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
