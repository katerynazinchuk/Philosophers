/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/24 18:57:13 by kzinchuk         ###   ########.fr       */
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
	// printf("Start time - %ld\n", input.start_time);
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
	if(pthread_join(monitor_thread, NULL))
		return (2);
	id = 0;
	while(id < input.philosophers)
	{
		if (pthread_join(philo[id].t_id, NULL))
			return (2);
		id++;
	}
	return (0);
}

void *monitor_function(void *data)
{
	t_philo *philos = (t_philo *)data;
	t_input *input = philos[0].input;						
	int	i;
	long	time_dif;

	while(1)
	{
		i = 0;
		while(i < input->philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			time_dif =  find_time() - philos[i].t_last_meal;
			pthread_mutex_unlock(&philos[i].meal_lock);

			pthread_mutex_lock(&input->death_lock);
			if(time_dif > input->time_to_die && philos->input->is_dead)
			{
				input->is_dead = 1;
				pthread_mutex_unlock(&input->death_lock);
				print_log(&philos[i], "died");
				return NULL;
			}
			pthread_mutex_unlock(&input->death_lock);
			i++;
		}
		if(input->number_of_meals > 0 && philos->meals_finished == input->number_of_meals)
			break ;// need to check for each philosopher
		usleep(500);
	}
	return NULL;
}

void *philo_life(void *data)//one pointer argument allowed by function signature
{
	int current_time;
	
	t_philo *philo = (t_philo *)data;
	current_time = find_time();
	if (current_time < philo->input->start_time)
		usleep((philo->input->start_time - current_time) * 1000);
	if(philo->ph_id % 2)
		philo_think(philo, philo->input->time_to_eat);
	while(1)
	{
		if(check_for_death(philo))
				return (NULL);
		if(philo->input->number_of_meals > 0 && philo->meals_finished == philo->input->number_of_meals)
			return (NULL);
		if(philo_take_fork(philo))
		{
			print_log(philo, "died");
			return NULL;
		}
		philo_eat(philo);
		philo_put_fork(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void print_log(t_philo *philo, char *str)//posibly add arg for time
{
	long	timestamp;

	timestamp = find_time() - philo->input->start_time;
	printf("%-5ld %-3d %s\n", timestamp, philo->ph_id + 1, str);
}


//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.

int check_for_death(t_philo *philo)
{
	int i;

	pthread_mutex_lock(&philo->input->death_lock);
	i = philo->input->is_dead;
	pthread_mutex_unlock(&philo->input->death_lock);
	return(i);
}