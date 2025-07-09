/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/09 16:47:32 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *pointer_func()
{	
	printf("HELLO from threads\n");
	return (NULL);
}

 int main (int argc, char ** argv)
 {
	(void) argc;
	(void) argv;
	pthread_t t1;
	if(pthread_create(&t1, NULL, &pointer_func, NULL))
		return (1);
	if(pthread_join(t1, NULL))
		return (2);
	return (0);
}