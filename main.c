/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/23 17:35:10 by kzinchuk         ###   ########.fr       */
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
	//
	init_input_struct(&input, argc, argv);
	printf("Start time - %ld\n", input.start_time);
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
	pthread_create(&monitor_thread, NULL, &monitor_function, philo);
	pthread_join(monitor_thread, NULL);
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
	t_philo *philo = (t_philo *)data;
	int	i;
	long	time_left;

	i = 0;
	while(1)
	{
		while(i < philo->input->philosophers)
		{
			pthread_mutex_lock(&philo->meal_lock);
			time_left =  find_time() - philo[i].t_last_meal;
			pthread_mutex_unlock(&philo->meal_lock);

			pthread_mutex_lock(&philo->input->death_lock);
			if()//setup this flag in eat function. now its = 0;
			{
				//do something that interupt the whole program and print message about death
				pthread_mutex_unlock(&philo->meal_lock);
				return ;
			}
			pthread_mutex_unlock(&philo->input->death_lock);


			// check for number of meals eaten
			while(i < philo->input->philosophers)
			{
				if(philo->input->number_of_meals > 0 && i < philo->input->number_of_meals)
				//what exactly should i compare here?
					i++;
			}
		}
		//
		usleep(500);
	}
}
void *philo_life(void *data)//one pointer argument allowed by function signature
{
	int current_time;
	
	t_philo *philo = (t_philo *)data;
	current_time = find_time();
	if (current_time < philo->input->start_time)
		usleep((philo->input->start_time - current_time) * 1000);
	while(1)
	{
		printf("HELLO, from %d thread: c_t %ld\n", philo->ph_id, find_time());
			
		philo_take_fork(philo);
		philo_eat(philo);
		philo_put_fork(philo);
			
		// philo_sleep(philo);
		// philo_think(philo);
		// philo_die(philo);
	}
	return (philo);
}

void print_log(t_philo *philo, char *str)//posibly add arg for time
{
	long	timestamp;

	timestamp = find_time() - philo->input->start_time;
	printf("%ld %d %s\n", timestamp, philo->ph_id + 1, str);
}


//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.