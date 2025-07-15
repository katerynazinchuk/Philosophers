/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:40 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:38 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_config
{
	int	philosophers;

}	t_configs;

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	mutex;
	int end_cycle;

}	t_philo;
	
int	check_input(int argc, char **str);


#endif


//6 400 100 100 7 - full input
//limit is not more that 200 philosophers

//left fork is the fork with the same index and right fork is the fork with index n + 1
// left fork = N
// right fork = (N + 1) % number of philosophers;


// even number take first left
// unever take first right