/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:29:48 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/19 17:45:22 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Convert a string to an integer
 * @param str The string to be converted
 * @return The integer value of the string
 **/
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

/**
 * Verify if the arguments passed in the command line are valid
 * @param ac The number of arguments
 * @param av The list of arguments
 * @return 1 if arguments are valid, 0 otherwise
 **/
int	verify_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Incorrect arguments\nUsage:\n./philo <num_of_philos> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep> [num_of_meals]\n");
		return (0);
	}
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * logs the status of the philo to the console with the current time,
 * philosopher ID, and the given message.
 * @param message the message to log_status
 * @param ph the philosopher struct that contains 
 * the philosopher's ID and a pointer to the table struct
**/
void	log_status(char *message, t_philo ph)
{
	pthread_mutex_lock(&ph.table->access);
	if (!ph.table->stop && !ph.table->finished)
		printf("%lld %d %s\n", (get_time() - ph.table->start_time), \
			ph.id, message);
	pthread_mutex_unlock(&ph.table->access);
}
