/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/16 12:53:21 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	printf("%lld %d has taken a fork\n", get_time() - ph->table->start_time, ph->id);
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	printf("%lld %d has taken a fork\n", get_time() - ph->table->start_time, ph->id);
	printf("%lld %d is eating\n", get_time() - ph->table->start_time, ph->id);
	hold(ph->table, ph->table->time_to_eat);
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
}

void	*philosopher(void *arg)
{
	t_philo *ph;

	ph = (t_philo *) arg;
	if (ph->id % 2 == 0)
	{
		printf("%lld %d is thinking\n", get_time() - ph->table->start_time, ph->id);
		hold(ph->table, 1500);
	}
	while (ph->table->stop != 1)
	{
		eating(ph);
		printf("%lld %d is sleeping\n", get_time() - ph->table->start_time, ph->id);
		hold(ph->table, ph->table->time_to_sleep);
		printf("%lld %d is thinking\n", get_time() - ph->table->start_time, ph->id);
	}
	return (NULL);
}

int	start_dining(t_table *table)
{
	pthread_t	threads[table->num_philosophers];
	int			i;

	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &table->philosophers[i]))
			return (0);
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (!verify_args(argc, argv))
		return (0);
	if (!init_table(&table, argv))
		return (0);
	start_dining(&table);
	i = 0;
	while (i < table.num_philosophers)
	{
		pthread_mutex_destroy(&table.forks[i]);
		i++;
	}
	free(table.forks);
	free(table.philosophers);
	return (0);
}
 