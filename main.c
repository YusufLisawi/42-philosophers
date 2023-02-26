#include "philo.h"

void *philosopher(void *arg)
{
	t_philo *p = (t_philo *)arg;
	while (p->table->num_meals_to_eat == 0 || p->meals < p->table->num_meals_to_eat)
	{
		// Try to pick up left fork
		if (pthread_mutex_trylock(&p->table->forks[p->left_fork]) == 0)
		{
			// Left fork picked up successfully, try to pick up right fork
			if (pthread_mutex_trylock(&p->table->forks[p->right_fork]) == 0)
			{
				// Right fork picked up successfully, start eating
				printf("%lld %d is eating\n", get_time(), p->id + 1);
				p->last_meal_time = get_time();
				usleep(p->table->time_to_eat * 1000);
				// Put down right fork
				pthread_mutex_unlock(&p->table->forks[p->right_fork]);
			}
			// Put down left fork
			pthread_mutex_unlock(&p->table->forks[p->left_fork]);
		}
		// Sleep or die
		if (get_time() - p->last_meal_time >= p->table->time_to_die)
		{
			printf("%lld %d died\n", get_time(), p->id + 1);
			pthread_mutex_unlock(&p->table->forks[p->left_fork]);
			pthread_exit(NULL);
		}
		else
		{
			printf("%lld %d is sleeping\n", get_time(), p->id + 1);
			usleep(p->table->time_to_sleep * 1000);
			printf("%lld %d is thinking\n", get_time(), p->id + 1);
		}
		// Check if all philosophers have finished eating
		if (p->table->num_meals_to_eat > 0)
		{
			pthread_mutex_lock(&p->table->forks[0]);
			if (p->table->num_finished == p->table->num_philosophers)
			{
				pthread_mutex_unlock(&p->table->forks[0]);
				p->table->stop = 1;
				break;
			}
			pthread_mutex_unlock(&p->table->forks[0]);
		}
	}
	p->table->num_finished++;
	pthread_exit(NULL);
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