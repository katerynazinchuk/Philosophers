/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/25 18:42:48 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(t_philo *philo)
{
	if(philo->ph_id % 2 == 1)
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
	}
	else
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
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->t_last_meal = find_time();
	pthread_mutex_unlock(&philo->meal_lock);
	print_log(philo, "is eating");
	usleep((philo->input->time_to_eat * 1000));
	philo->meals_finished++;
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

void	philo_sleep(t_philo *philo)
{
	long	sleep;

	sleep = philo->input->time_to_sleep;
	print_log(philo, "is sleeping");
	usleep(sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	long	current_time;
	long	time_left;

	print_log(philo, "is thinking");
	current_time = find_time();
	time_left = philo->input->time_to_die - (current_time - philo->t_last_meal);
	if (time_left > 0)
		usleep(time_left / 2 * 1000);
}

