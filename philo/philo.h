/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:07:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/16 19:15:41 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals;
	long long		last_meal_time;
	long long		start_time;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals_to_eat;
	int				stop;
	pthread_mutex_t	access;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

long long	get_time(void);
int			verify_args(int ac, char **av);
int			init_table(t_table *table, char **av);
void		nap(t_table *table, int time);
int			ft_atoi(const char *str);
void		log_status(char *message, t_philo ph);
int			check_eating(t_table *table);
int			check_death(t_table *table);

#endif