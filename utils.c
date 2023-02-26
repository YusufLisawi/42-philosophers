#include "philo.h"

long long get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_atoi(const char *str)
{
	int result;
	int sign;
	int i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

void verify_args(int ac, char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			exit(0);
		i++;
	}
}

void init_table(t_table *table, char **av)
{
	int i;
	table->philosophers = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	table->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	table->num_philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ft_atoi(av[5]))
		table->num_meals_to_eat = ft_atoi(av[5]);
	else
		table->num_meals_to_eat = -1;
	table->num_finished = 0;
	table->stop = 0;
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			exit(1);
		table->philosophers[i].id = i;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % ft_atoi(av[1]);
		table->philosophers[i].meals = 0;
		table->philosophers[i].last_meal_time = get_time();
		table->philosophers[i].table = table;
	}
}
