/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/28 15:54:54 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->t_last_meal = find_time();
	pthread_mutex_unlock(&philo->meal_lock);
	print_log(philo, "is eating");
	usleep((philo->input->time_to_eat * 1000));
	philo->meals_finished++;
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

void	*philo_life(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	wait_for_start(philo->input);
	if (philo->ph_id % 2 == 1)
		philo_think(philo);
	while (1)
	{
		if (check_for_death(philo))
			return (NULL);
		if (philo->input->number_of_meals > 0 && \
philo->meals_finished == philo->input->number_of_meals)
			return (NULL);
		if (philo_take_fork(philo))
			return (NULL);
		philo_eat(philo);
		philo_put_fork(philo);
		if (check_for_death(philo))
			return (NULL);
		philo_sleep(philo);
		if (check_for_death(philo))
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}
