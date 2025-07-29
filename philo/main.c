/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/29 17:39:02 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	single_philo(t_input *input)
{
	printf("0     1   has taken a fork\n");
	usleep(input->time_to_die * 1000);
	printf("%-5d 1   died\n", input->time_to_die);
	destroy_input_struct(input);
	return (0);
}

static int	start_philo_threads(t_philo *philo)
{
	int	id;

	id = 0;
	while (id < philo->input->philosophers)
	{
		if (pthread_create(&philo[id].t_id, NULL, &philo_life, &philo[id]))
			return (1);
		id++;
	}
	return (0);
}

static int	init_all_philo(t_philo *philo, t_input *input)
{
	int	id;

	id = 0;
	while (id < input->philosophers)
	{
		if (init_philo_struct(&philo[id], input, id))
			return (1);
		id++;
	}
	return (0);
}

static int	join_philo_threads(t_philo *philo)
{
	int	id;

	id = 0;
	while (id < philo->input->philosophers)
	{
		if (pthread_join(philo[id].t_id, NULL))
			return (2);
		destroy_philo_struct(&philo[id]);
		id++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_input		input;
	t_philo		philo[200];
	pthread_t	monitor_thread;

	if (!check_input(argc, argv))
		return (1);
	if (init_input_struct(&input, argc, argv))
		return (1);
	if (input.philosophers == 1)
		return (single_philo(&input));
	if (init_all_philo(philo, &input))
		return (1);
	if (start_philo_threads(philo))
		return (1);
	if (pthread_create(&monitor_thread, NULL, &monitoring, philo))
		return (1);
	if (pthread_detach(monitor_thread))
		return (2);
	if (join_philo_threads(philo))
		return (2);
	destroy_input_struct(&input);
	destroy_philo_struct(philo);
	return (0);
}
