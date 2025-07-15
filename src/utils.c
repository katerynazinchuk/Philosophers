/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:19:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/15 15:16:12 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
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
		if (number * sign > INT_MAX || number *sign < INT_MIN)// to check the owerflows
			return (-1);
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
	if(number_of_arg(argc))
		return (0);
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(ft_isalpha(str[i][j]))
			{
				printf("Numeric input required\n");
				return (0);
			}
			j++;
		}
		a = ft_atoi(str[i]);
		if(a <= 0)
		{
			printf("Positive numbers input required\n");//f1r1s9% ./philo 200 200 100 8 9- - clarify behaviour of this case
			return (0);
		}
		if(i == 1 && a > 200)
		{
			printf("Number of philosophers should be less then 200\n");
			return (0);
		}
		i++;
	}
	return (1);
}


// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

// memset, printf, malloc, free, write,
// usleep, 
// gettimeofday, 
// pthread_create(),
// pthread_detach(),
// pthread_join(), 
// pthread_mutex_init();
// pthread_mutex_destroy(); == 0 success
// pthread_mutex_lock(); == 0 success
// pthread_mutex_unlock(); == 0 success