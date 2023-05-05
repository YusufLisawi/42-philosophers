/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:42:16 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/05 18:34:59 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_table *table)
{
	long	check_time;
	int		i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (table->num_meals_to_eat != -1 && \
		table->philos[i].meals >= table->num_meals_to_eat)
			continue ;
		pthread_mutex_lock(&table->access);
		check_time = get_time() - table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->access);
		if (check_time > table->time_to_die)
		{
			pthread_mutex_lock(&table->access);
			table->stop = 1;
			pthread_mutex_unlock(&table->access);
			log_status("died", table->philos[i]);
			return ;
		}
	}
}

void	check_eating(t_table *table)
{
	int	i;
	int	eaten;

	eaten = 0;
	i = -1;
	while (++i < table->num_philos)
	{
		if (table->num_meals_to_eat != -1 && \
		table->philos[i].meals < table->num_meals_to_eat)
		{
			eaten = 1;
			break ;
		}
	}
	if (!eaten && table->num_meals_to_eat != -1)
	{
		pthread_mutex_lock(&table->access);
		table->stop = 1;
		pthread_mutex_unlock(&table->access);
		return ;
	}
}
