/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:53:32 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/08/04 15:11:27 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_input_struct(t_input *input)
{
	destroy_forks(input, input->philosophers);
	pthread_mutex_destroy(&input->death_lock);
	pthread_mutex_destroy(&input->print_lock);
	pthread_mutex_destroy(&input->monitor_thread);
}

void	destroy_forks(t_input *input, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&input->forks[i]);
		i++;
	}
}

void	destroy_philos_struct(t_philo *philo, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philo->meal_lock);
		i++;
	}
}
