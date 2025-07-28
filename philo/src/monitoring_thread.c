/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:14:47 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/28 16:03:11 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_input *input)
{
	int		current_time;

	current_time = find_time();
	if (current_time < input->start_time)
		usleep((input->start_time - current_time) * 1000);
}

static void	report_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo[0].input->death_lock);
	philo[0].input->is_dead = 1;
	pthread_mutex_unlock(&philo[0].input->death_lock);
	timestamp = find_time() - philo[0].input->start_time;
	pthread_mutex_lock(&philo->input->print_lock);
	printf("%-5ld %-3d %s\n", timestamp, philo->ph_id, "died");
	pthread_mutex_unlock(&philo->input->print_lock);
}

static int	collect_data(t_philo *philo)
{
	long	time_dif;
	int		meal_number;

	pthread_mutex_lock(&philo->meal_lock);
	time_dif = find_time() - philo->t_last_meal;
	meal_number = philo->meals_finished;
	pthread_mutex_unlock(&philo->meal_lock);
	if (meal_number != philo->input->number_of_meals && \
time_dif > philo->input->time_to_die)
		return (1);
	return (0);
}

void	*monitoring(void *data)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)data;
	wait_for_start(philos->input);
	while (1)
	{
		i = 0;
		while (i < philos[0].input->philosophers)
		{
			if (collect_data(&philos[i]))
			{
				report_death(&philos[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_for_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->input->death_lock);
	i = philo->input->is_dead;
	pthread_mutex_unlock(&philo->input->death_lock);
	return (i);
}
