/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/23 17:16:18 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	if(philo->ph_id % 2)
	{
		pthread_mutex_lock(&philo->left_fork);
		//if time to die < time for meal => sleep(time ot die - find_time() and die
			pthread_mutex_lock(&philo->right_fork);
		//if time to die < time for meal => sleep(time ot die - find_time() and die
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);

		pthread_mutex_lock(&philo->left_fork);
	}
	print_log(philo, "has taken a fork");
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
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

// long last_meal_taken(t_philo *philo)
// {
// 	philo->time_last_meal;
	
// }

// timestamp_in_ms X died
// void	philo_sleep(t_philo *philo)
// {

// 	long time_to_die;


// 	time_to_sleep = philo->input->time_to_sleep;
// 	time_to_die = philo->input->time_to_die - (find_time() - /* philo->time_last_meal */);
// if (time_to_die < 0)
// 		time_to_die = 0;
// 	long sleep = min(time_to_die, time_to_sleep);
// 	usleep(sleep);
// 	if(philo->input->time_to_die > (philo->input->time_to_eat + philo->input->time_to_sleep))
// 		printf("Sleep for %d\n", philo->input->time_to_sleep);
// 	else
// 		printf("Philo died at %ld\n", find_time());
// 	print_log(philo, "is sleeping");
// }

// void	philo_think(t_philo *philo)
// {
// 	if(philo->input->time_to_die > (philo->input->time_to_eat + philo->input->time_to_sleep))
// 		printf("Think for %d\n", philo->input->time_to_die - (philo->input->time_to_eat + philo->input->time_to_sleep));
//		print_lo(philo, "is thinking");
// }

