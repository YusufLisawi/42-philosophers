/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:42:16 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/17 21:42:31 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_finished(t_table **table, int eaten)
{
	if (!eaten && (*table)->num_meals_to_eat != -1)
	{
		pthread_mutex_lock(&(*table)->access);
		(*table)->stop = 1;
		pthread_mutex_unlock(&(*table)->access);
		return (1);
	}
	return (0);
}

int	print_death(t_table **table, int i, long check_time)
{
	if (check_time >= (*table)->time_to_die)
	{
		pthread_mutex_lock(&(*table)->access);
		printf("%lld %d %s\n", get_time() - (*table)->philos[i].start_time, \
			(*table)->philos[i].id, "died");
		(*table)->stop = 1;
		pthread_mutex_unlock(&(*table)->access);
		return (1);
	}
	return (0);
}

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
		if (print_death(&table, i, check_time))
			return (1);
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
			meals < table->num_meals_to_eat + 1)
		{
			eaten = 1;
			break ;
		}
	}
	if (is_all_finished(&table, eaten))
		return (1);
	return (0);
}
