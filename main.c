/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/04 13:43:27 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher(void *arg)
{
	t_philo *ph = (t_philo *) arg;
	
	if (ph->id % 2 == 0)
	{
		printf("%lld %d is thinking\n", get_time() - ph->table->start_time, ph->id);
		usleep(1000);
	}
	while (ph->table->stop != 1)
	{
		pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
		printf("%lld %d has taken a fork\n", get_time() - ph->table->start_time, ph->id);
		pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
		printf("%lld %d has taken a fork\n", get_time() - ph->table->start_time, ph->id);
		printf("%lld %d is eating\n", get_time() - ph->table->start_time, ph->id);
		usleep(ph->table->time_to_eat * 1000);
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
		printf("%lld %d is sleeping\n", get_time() - ph->table->start_time, ph->id);
		usleep(ph->table->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time() - ph->table->start_time, ph->id);
	}
	return (NULL);
}

void start_dining(t_table *table)
{
	pthread_t threads[table->num_philosophers];
	int i;

	// Start philosopher threads
	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &table->philosophers[i]))
			exit(1);
	}
	// Wait for threads to finish
	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_join(threads[i], NULL))
			exit(1);
	}
}

int main(int argc, char **argv)
{
	t_table table;
	int i;

	verify_args(argc, argv);
	init_table(&table, argv);
	start_dining(&table);
	i = 0;
	while (i < table.num_philosophers)
	{
		pthread_mutex_destroy(&table.forks[i]);
		i++;
	}
	free(table.forks);
	free(table.philosophers);
	return 0;
}