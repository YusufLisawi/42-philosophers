/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/16 21:40:59 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_stop(t_table *table)
{
	while (1)
	{
		if (check_death(table))
			return ;
		if (check_eating(table))
			return ;
	}
}

int	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	log_status("has taken a fork", *ph);
	if (ph->table->num_philos == 1)
	{
		// nap(ph->table, ph->table->time_to_die);
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		return (1);
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
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo *ph;
	int		stop;

	ph = (t_philo *) arg;
	log_status("is thinking", *ph);
	if (ph->id % 2 == 0)
	{
		usleep(500);
		// nap(ph->table, ph->table->time_to_sleep);
	}
	stop = 1;
	while (stop)
	{
		pthread_mutex_lock(&ph->table->access);
		stop = !ph->table->stop;
		pthread_mutex_unlock(&ph->table->access);
		if (eating(ph))
			return (NULL);
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
		if (pthread_create(&threads[i], NULL, philo_routine, &table->philos[i]))
			return (0);
		usleep(10);
	}
	check_stop(table);
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
 