/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/18 14:18:52 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	if(philo->ph_id % 2)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
}

void	philo_eat(t_philo *philo)
{
	while()
		if(philo->input->time_to_die > philo->input->time_to_eat)
			printf("Eat for %d\n", philo->input->time_to_eat);
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

void	philo_sleep(t_philo *philo)
{

	long time_to_slee;
	long time_to_die;

	time_to_slee = philo->input->time_to_sleep;
	time_to_die = philo->input->time_to_die - (find_time() - /* philo->time_last_meal */);
if (time_to_die < 0)
		time_to_die = 0;
	long sleep = min(time_to_die, time_to_slee);
	
		usleep(sleep);
	if(philo->input->time_to_die > (philo->input->time_to_eat + philo->input->time_to_sleep))
		printf("Sleep for %d\n", philo->input->time_to_sleep);
	else
		printf("Philo died at %ld\n", find_time());
}

void	philo_think(t_philo *philo)
{
	if(philo->input->time_to_die > (philo->input->time_to_eat + philo->input->time_to_sleep))
		printf("Think for %d\n", philo->input->time_to_die - (philo->input->time_to_eat + philo->input->time_to_sleep));
}

