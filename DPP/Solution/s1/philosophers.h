/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/19 13:44:45 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				nphilo;
	int				finished;
	unsigned long	pstart;
	int				max_meals;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	useconds_t		time_to_die;
	pthread_mutex_t	print_m;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	unsigned long	last_meal;
	int				meals_eaten;
	t_data			*pdata;
}				t_philo;

unsigned long	get_ms(void);
unsigned long	time_ms(unsigned long start);
int				ft_atoi(const char *str);
void			out(char *action, t_philo *philo);
void			my_usleep(unsigned long time);

#endif