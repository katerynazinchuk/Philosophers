/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:39:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/29 17:39:28 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->philosophers)
	{
		if (pthread_mutex_init(&input->forks[i], NULL))
		{
			destroy_forks(input, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_input_struct(t_input *input, int argc, char **argv)
{
	int	i;

	i = 0;
	input->philosophers = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->number_of_meals = ft_atoi(argv[5]);
	else
		input->number_of_meals = -1;
	input->start_time = find_time() + 1000;
	input->is_dead = 0;
	if (init_forks(input))
		return (1);
	if (pthread_mutex_init(&input->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&input->death_lock, NULL))
		return (1);
	return (0);
}

int	init_philo_struct(t_philo *philo, t_input *input, int id)
{
	philo->t_id = 0;
	philo->ph_id = id + 1;
	philo->input = input;
	philo->left_fork = &input->forks[id];
	philo->right_fork = &input->forks[(id + 1) % input->philosophers];
	if (pthread_mutex_init(&philo->meal_lock, NULL))
		return (1);
	philo->t_last_meal = input->start_time;
	philo->meals_finished = 0;
	return (0);
}
