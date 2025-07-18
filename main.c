/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/18 14:03:12 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	int id;
	t_input input;
	t_philo philo[200];

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
		if (pthread_create(&philo[id].t_id, NULL, &pointer_func, &philo[id]))
			return (1);
		id++;
	}
	id = 0;
	while(id < input.philosophers)
	{
		if (pthread_join(philo[id].t_id, NULL))
			return (2);
		id++;
	}
	return (0);
}

void *pointer_func(void *data)//one pointer argument allowed by function signature
{
	int current_time;
	
	t_philo *philo = (t_philo *)data;
	current_time = find_time();
	if (current_time < philo->input->start_time)
		usleep((philo->input->start_time - current_time) * 1000);
	// while(1)
	// {
	printf("HELLO, from %d thread: c_t %ld\n", philo->ph_id, find_time());
		
	philo_take_fork(*philo);// pthread_mutex_lock(&philo[id]->input->forks[id]);
	philo_eat(philo);
	philo_put_fork(*philo);// c;
		
	philo_sleep(philo);
	philo_think(philo);
		// philo_die(philo);
		
	
	// }
	return (philo);
}

// void print_log(int start_time, int id, char *str)//posibly add arg for time
// {
	

// }
// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.