/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:42:16 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/16 18:22:34 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_table *table)
{
	long	check_time;
	int		i;
	int		meals;

	i = -1;
	meals = 0;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->access);
		meals = table->philos[i].meals;
		pthread_mutex_unlock(&table->access);
		if (table->num_meals_to_eat != -1 && \
			meals >= table->num_meals_to_eat)
			continue ;
		pthread_mutex_lock(&table->access);
		check_time = get_time() - table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->access);
		if (check_time > table->time_to_die)
		{
			log_status("died", table->philos[i]);
			pthread_mutex_lock(&table->access);
			table->stop = 1;
			pthread_mutex_unlock(&table->access);
			return (1);
		}
	}
	return (0);
}

int	check_eating(t_table *table)
{
	int	i;
	int	eaten;
	int	meals;

	eaten = 0;
	meals = 0;
	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->access);
		meals = table->philos[i].meals;
		pthread_mutex_unlock(&table->access);
		if (table->num_meals_to_eat != -1 && \
			meals < table->num_meals_to_eat)
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
		return (1);
	}
	return (0);
}
