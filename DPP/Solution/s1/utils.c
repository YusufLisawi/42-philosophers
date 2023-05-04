/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:44:35 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/19 13:48:22 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

/**
 * GET TIME IN MILLISECONDS
 */
unsigned long	get_ms(void)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/**
 * GET TIME IN MILLISECONDS
 * RELATIVE TO THE START OF THE PROGRAM
 */
unsigned long	time_ms(unsigned long start)
{
	return (get_ms() - start);
}

/**
 * PRINT WHEN print_m IS UNLOCKED
 */
void	out(char *action, t_philo *philo)
{
	pthread_mutex_lock(&(philo->pdata->print_m));
	printf("%lu %d %s\n", time_ms(philo->pdata->pstart), philo->id + 1, action);
	pthread_mutex_unlock(&(philo->pdata->print_m));
}

/**
 * MY VERSION OF USLEEP FUNCTION
 */
void	my_usleep(unsigned long time)
{
	unsigned long	curr;

	curr = get_ms();
	while (get_ms() - curr < time)
		usleep(50);
}

/* 
 * ATOI
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
} 
   