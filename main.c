/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/17 17:32:31 by kzinchuk         ###   ########.fr       */
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
	t_philo *philo = (t_philo *)data;
	//usleep(start_time - current_time)//log calculetion start from poit start_time
	while(1)
	{
		philo_take_fork();
		philo_eat();
		philo_sleep();
		philo_think();
		philo_die();
		// pthread_mutex_lock(&philo[id]->input->forks[id]);
		// pthread_mutex_unlock(&mutex);
		printf("HELLO from threads - %d\n", philo->ph_id);
	}
	return (philo);
}

//identify currect time when the thread starts

void print_log(int start_time, int id, char *str)//posibly add arg for time
{
	

}
// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.