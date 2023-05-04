/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:36 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/04 16:49:47 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Get the current time in milliseconds using gettimeofday function
 * @return the current time in milliseconds
 **/
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * Better version of usleep
 * This function allows a thread to sleep for a certain amount of time,
 * while checking if the table has been stopped to exit the loop early.
 * @param table The table struct containing information about the philos.
 * @param time The amount of time to sleep in milliseconds.
**/
void	nap(t_table *table, int time)
{
	long long	current;
	int			stop;

	stop = 1;
	current = get_time();
	while (stop)
	{
		pthread_mutex_lock(&table->access);
		stop = !table->stop;
		pthread_mutex_unlock(&table->access);
		if (get_time() - current >= time)
			break ;
		usleep(50);
	}
}

/**
 * Initialize the philos struct array with their respective 
 * IDs, forks, meal counts and last meal time
 * @param table The main table struct
 * @return 1 if initialization was successful, 0 otherwise
 **/
int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (0);
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->num_philos;
		table->philos[i].meals = 0;
		table->philos[i].last_meal_time = get_time();
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

/** 
 * This function initializes the table struct with the number of philos,
 * their time limits, and allocates memory for the forks and philos.
 * @param table The table struct to be initialized.
 * @param av The array of strings containing the program arguments.
 * @return 1 on success, 0 on failure to allocate memory.
**/
int	init_table(t_table *table, char **av)
{
	table->stop = 0;
	table->finished = 0;
	table->start_time = get_time();
	table->num_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->num_meals_to_eat = -1;
	if (av[5])
		table->num_meals_to_eat = ft_atoi(av[5]);
	table->philos = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	table->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!table->philos || !table->forks)
		return (0);
	if (pthread_mutex_init(&table->access, NULL))
		return (0);
	if (!init_philos(table))
		return (0);
	return (1);
}
