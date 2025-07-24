/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/24 18:22:09 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(t_philo *philo)
{
	if(philo->ph_id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		if(check_for_death(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		if(check_for_death(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if(check_for_death(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
		if(check_for_death(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
	}
	print_log(philo, "has taken a fork");
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->t_last_meal = find_time();
	pthread_mutex_unlock(&philo->meal_lock);
	print_log(philo, "is eating");
	usleep(philo->input->time_to_eat * 1000);
	philo->meals_finished++;

	// while(philo->input->time_to_die - )
	// 	if(philo->input->time_to_die > philo->input->time_to_eat)
}

void	philo_put_fork(t_philo *philo)
{
	if(philo->ph_id % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

// long last_meal_taken(t_philo *philo)
// {
// 	philo->time_last_meal;
	
// }

// timestamp_in_ms X died
void	philo_sleep(t_philo *philo)
{

	long time_left;
	long sleep;

	long time_to_sleep = philo->input->time_to_sleep;
	pthread_mutex_lock(&philo->meal_lock);
	time_left = philo->input->time_to_die - (find_time() - philo->t_last_meal);
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_left < 0)
		time_left = 0;
	if(time_left > time_to_sleep)
		sleep = time_to_sleep;
	else
		sleep = time_left;
	print_log(philo, "is sleeping");
	usleep(sleep * 1000);
	if(philo->input->time_to_die > (philo->input->time_to_eat + philo->input->time_to_sleep))
		print_log(philo, "is thinking");
	else
		print_log(philo, "died");
}

void	philo_think(t_philo *philo, int a)
{
	print_log(philo, "is thinking");
	usleep(a);
}

