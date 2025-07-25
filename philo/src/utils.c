/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:19:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/25 18:46:16 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
    int i;
    long long number;
    int sign;
    
	i = 0;
	number = 0;
	sign = 1;
    while (str[i] == '\t' || str[i] == '\r' || str[i] == ' ')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        number = number * 10 + (str[i] - '0');
		if (number * sign > INT_MAX)
			return (INT_MAX);
		if(number *sign < INT_MIN)
			return (INT_MIN);
        i++;
    }   
    return (number * sign);
}

static int number_of_arg(int argc)
{
	if (argc < 5)
	{
		printf("Provide full list of required arguments\n");
		return (1);
	}
	if (argc > 6)
	{
		printf("Too many arguments\n");
		return (1);
	}
	return (0);
}

int	check_input (int argc, char **str)
{
	int	i;
	int	j;
	int	a;

	i = 1;
	if (number_of_arg(argc))
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
			{
				printf("Numeric input required\n");
				return (0);
			}
			j++;
		}
		a = ft_atoi(str[i]);
		if (i == 1 && (a > 200 || a <= 0))
		{
			printf("Number of philosophers should be between 1 and 200\n");
			return (0);
		}
		i++;
	}
	return (1);
}

long find_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000) + (ct.tv_usec / 1000));
}

// memset, printf, malloc, free, write,
// usleep, 
// gettimeofday, 
// pthread_create(), // last NULL can be replaced with any data pointer that thread should know
// pthread_detach(),
// pthread_join(), // wait until the specific thread finishes its work
// pthread_mutex_init();
// pthread_mutex_destroy(); == 0 success
// pthread_mutex_lock(); == 0 success
// pthread_mutex_unlock(); == 0 success


// pthread_mutex_t mutex; //each fork is a mutex(lock)
// pthread_mutex_init(&mutex, NULL);
// //can add as many variables as needed between this two functions to protect them from the data racing
// pthread_mutex_lock(&mutex);
// printf("Mutex locked!\n");
// pthread_mutex_unlock(&mutex);
// pthread_mutex_destroy(&mutex);//destroy mutex everytime after using it
// unsleep(time);//in mls
// printf("200 3 has taken a fork");//example

//6 400 100 100 7 - full input
//limit is not more that 200 philosophers

//left fork is the fork with the same index and right fork is the fork with index n + 1
// left fork = N
// right fork = (N + 1) % number of philosophers;

// even number take first left
// unever take first right



//each state of the automat is a function.
//while loop is the engine for the states.
// each function return the state wich next function absorb.