/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:25:40 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/29 17:30:41 by kzinchuk         ###   ########.fr       */
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
	// pthread_t monitor_thread;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
}	t_input;

typedef struct s_philo
{
	pthread_t		t_id;
	int				ph_id;
	t_input			*input;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	long			t_last_meal;
	int				meals_finished;
}	t_philo;

int		ft_isdigit(int c);
int		check_input(int argc, char **str);
int		init_input_struct(t_input *input, int argc, char **argv);
void	destroy_input_struct(t_input *input);
int		init_philo_struct(t_philo *philo, t_input *input, int id);
void	destroy_forks(t_input *input, int count);
void	destroy_philo_struct(t_philo *philo);
int		ft_atoi(const char *str);
long	find_time(void);
void	*philo_life(void *data);
void	*monitoring(void *data);
void	print_log(t_philo *philo, char *str);
int		philo_take_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_put_fork(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
int		check_for_death(t_philo *philo);
void	wait_for_start(t_input *input);

#endif
