/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:29:48 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/18 19:40:26 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isallnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (1);
}

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

int	verify_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error: Incorrect arguments\n", 27);
		return (0);
	}
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0 || ft_isallnum(av[i]) == -1 || av[0] == 0)
			return (write(2, "Error: Incorrect arguments\n", 27), 0);
		i++;
	}
	return (1);
}

void	log_status(char *message, t_philo ph)
{
	pthread_mutex_lock(&ph.table->access);
	if (!ph.table->stop)
	{
		printf("%lld %d %s\n", (get_time() - ph.start_time), \
		ph.id, message);
	}
	pthread_mutex_unlock(&ph.table->access);
}
