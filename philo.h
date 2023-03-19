/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/16 13:03:18 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIHLO_H
# define PIHLO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_philo
{
	int id;
	int left_fork;
	int right_fork;
	int meals;
	long long last_meal_time;
	struct s_table *table;
} t_philo;

typedef struct s_table
{
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_meals_to_eat;
	long long start_time;
	int stop;
	pthread_mutex_t *forks;
	t_philo *philosophers;
} t_table;

long long	get_time(void);
int			verify_args(int ac, char **av);
int			init_table(t_table *table, char **av);
void		hold(t_table *table, int time);
#endif