/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:40 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/17 17:17:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_input
{
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int start_time;
	pthread_mutex_t forks[200]; // array of mutexes for forks

}	t_input;

typedef struct s_philo
{
	pthread_t		t_id;
	int				ph_id;
	t_input			*input;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals_finished;
}	t_philo;
	
int		check_input(int argc, char **str);
int		init_input_struct(t_input *input, int argc, char **argv);
void	init_philo_struct(t_philo *philo, t_input *input, int id);
int		ft_atoi(const char *str);


#endif


