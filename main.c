/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/19 19:14:17 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check(t_table *table)
{
	int	i;

	while (1)
	{
		if (table->finished == table->num_philos)
		{
			pthread_mutex_lock(&table->access);
			table->stop = 1;
			pthread_mutex_unlock(&table->access);	
			return ;
		}
		i = -1;
		while (++i < table->num_philos)
		{
			if (table->num_meals_to_eat != -1 && \
			table->philos[i].meals >= table->num_meals_to_eat)
				continue ;
			if (get_time() - table->philos[i].last_meal_time > table->time_to_die)
			{
				log_status("has died", table->philos[i]);
				pthread_mutex_lock(&table->access);
				table->stop = 1;
				pthread_mutex_unlock(&table->access);
				return ;
			}
		}
	}
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	log_status("has taken a fork", *ph);
	if (ph->table->num_philos == 1)
	{
		nap(ph->table, ph->table->time_to_die);
		return ;
	}
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	log_status("has taken a fork", *ph);
	log_status("is eating", *ph);
	pthread_mutex_lock(&ph->table->access);
	ph->last_meal_time = get_time();
	pthread_mutex_unlock(&ph->table->access);
	nap(ph->table, ph->table->time_to_eat);
	pthread_mutex_lock(&ph->table->access);
	ph->meals++;
	pthread_mutex_unlock(&ph->table->access);
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
}

void	*philosopher(void *arg)
{
	t_philo *ph;

	ph = (t_philo *) arg;
	if (ph->id % 2 == 0)
	{
		log_status("is thinking", *ph);
		usleep(1500);
	}
	while (ph->table->stop != 1)
	{
		eating(ph);
		if (ph->table->num_meals_to_eat != -1 && \
			ph->meals >= ph->table->num_meals_to_eat)
			return (ph->table->finished++, ph);
		log_status("is sleeping", *ph);
		nap(ph->table, ph->table->time_to_sleep);
		log_status("is thinking", *ph);
	}
	return (ph);
}

int	start_dining(t_table *table)
{
	pthread_t	threads[table->num_philos];
	int			i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &table->philos[i]))
			return (0);
	}
	check(table);
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	if (!verify_args(ac, av))
		return (0);
	if (!init_table(&table, av))
		return (0);
	start_dining(&table);
	i = 0;
	while (i < table.num_philos)
	{
		pthread_mutex_destroy(&table.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table.access);	
	return (free(table.forks), free(table.philos), 0);
}
 