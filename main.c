/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/15 15:13:42 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// printf("invalid input");

void *pointer_func()
{	
	printf("HELLO from threads\n");
	return (NULL);
}

int main (int argc, char **argv)
{
	if(!check_input(argc, argv))
		return (0);
	pthread_t id1;
	if (pthread_create(&id1, NULL, &pointer_func, NULL))// last NULL can be replaced with any data pointer that thread should know
		return (1);
	if (pthread_join(id1, NULL))// wait until the specific thread finishes its work
		return (2);
	return (0);
}



// pthread_mutex_t mutex; //each fork is a mutex(lock)
// pthread_mutex_init(&mutex, NULL);
// //can add as many variables as needed between this two functions to protect them from the data racing
// pthread_mutex_lock(&mutex);
// printf("Mutex locked!\n");
// pthread_mutex_unlock(&mutex);
// pthread_mutex_destroy(&mutex);//destroy mutex everytime after using it

// unsleep(time);//in mls

// printf("200 3 has taken a fork");//example