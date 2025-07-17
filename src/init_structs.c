/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:39:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/17 17:27:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		input->number_of_meals = -1; //????
	while(i < input->philosophers)
	{
		if(pthread_mutex_init(&input->forks[i], NULL))
		{
			while(--i >= 0)
			{
				pthread_mutex_destroy(&input->forks[i]);
			}
			return (-1);// add error
		}
		i++;
	}
	input->start_time = find_start_time() + 200;
	return (0);
}

long find_start_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000) + (ct.tv_usec / 1000));
}

void	destroy_input_struct(t_input *input)
{
	int	i;
	
	i = 0;
	while(i < input->philosophers)
	{
		pthread_mutex_destroy(&input->forks[i]);
		i++;
	}
}

void	init_philo_struct(t_philo *philo, t_input *input, int id)
{
	philo->t_id = 0;
	philo->ph_id = id;
	philo->input = input;
	philo->left_fork = &input->forks[id];
	philo->right_fork = &input->forks[(id + 1) % input->philosophers];
	philo->meals_finished = 0;
}

// void destroy_philo_struct(t_philo *philo)
// {
	
// }