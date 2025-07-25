/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/25 18:46:33 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	int id;
	t_input input;
	t_philo philo[200];
	pthread_t monitor_thread;

	id = 0;
	if(!check_input(argc, argv))
		return (0);
	init_input_struct(&input, argc, argv);
	
	// Special case for 1 philosopher - cannot eat with only 1 fork
	if (input.philosophers == 1)
	{
		printf("0     1   has taken a fork\n");
		usleep(input.time_to_die * 1000);
		printf("%-5d 1   died\n", input.time_to_die);
		destroy_input_struct(&input);
		return (0);
	}
	// printf("Start time -   %ld\n", input.start_time);
	while(id < input.philosophers)
	{
		init_philo_struct(&philo[id], &input, id);
		id++;
	}
	id = 0;
	while (id < input.philosophers)
	{
		if (pthread_create(&philo[id].t_id, NULL, &philo_life, &philo[id]))
			return (1);
		id++;
	}
	if(pthread_create(&monitor_thread, NULL, &monitor_function, philo))
		return (1);
	if (pthread_detach(monitor_thread))
		return (2);
	id = 0;
	while(id < input.philosophers)
	{
		if (pthread_join(philo[id].t_id, NULL))
			return (2);
		destroy_philo_struct(&philo[id]);
		id++;
	}
	destroy_input_struct(&input);
	// printf("All philosophers have finished their meals.\n");
	return (0);
}

void *monitor_function(void *data)
{
	t_philo *philos = (t_philo *)data;
	t_input *input = philos[0].input;						
	int		i;
	long	time_dif;
	int 	meal_number;
	int 	current_time;
	
	current_time = find_time();
	if (current_time < input->start_time)
		usleep((input->start_time - current_time) * 1000);
	while (1)
	{
		i = 0;
		while (i < input->philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			time_dif =  find_time() - philos[i].t_last_meal;
			meal_number = philos[i].meals_finished; 
			pthread_mutex_unlock(&philos[i].meal_lock);
			if (meal_number != input->number_of_meals)
			{
				if(time_dif > input->time_to_die)
				{
					pthread_mutex_lock(&input->death_lock);
					input->is_dead = 1;
					pthread_mutex_unlock(&input->death_lock);
					{
						long timestamp = find_time() - input->start_time;
						printf("%-5ld %-3d %s\n", timestamp, philos[i].ph_id, "died");
					}
					return NULL;
				}
			}
			i++;
		}
		usleep(1000);
	}
	return NULL;
}

void *philo_life(void *data)	
{
	int current_time;
	
	t_philo *philo = (t_philo *)data;
	current_time = find_time();
	if (current_time < philo->input->start_time)
		usleep((philo->input->start_time - current_time) * 1000);
	if (philo->ph_id % 2 == 1)
		philo_think(philo);
	while (1)
	{
		if (check_for_death(philo))
			return (NULL);
		if (philo->input->number_of_meals > 0 && philo->meals_finished == philo->input->number_of_meals)
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

void print_log(t_philo *philo, char *str)
{
	long	timestamp;

	pthread_mutex_lock(&philo->input->print_lock);
	if (!philo->input->is_dead)
	{
		timestamp = find_time() - philo->input->start_time;
		printf("%-5ld %-3d %s\n", timestamp, philo->ph_id, str);
	}
	pthread_mutex_unlock(&philo->input->print_lock);
}

int check_for_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->input->death_lock);
	i = philo->input->is_dead;
	pthread_mutex_unlock(&philo->input->death_lock);
	return (i);
}