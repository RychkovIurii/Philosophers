/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 22:02:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat] */

#include "philo.h"

int	is_valid_data(const t_program_data *data)
{
	if (data->number_of_philosophers < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (0);
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	return (1);
}

/* t_program_data	*init_philo(int ac, char *av[])
{
	t_program_data	*data;

	data = malloc(sizeof(t_program_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = converter(av[1]);
	data->time_to_die = converter(av[2]);
	data->time_to_eat = converter(av[3]);
	data->time_to_sleep = converter(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = converter(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (!is_valid_data(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
} */

unsigned long int get_current_time(void)
{
	unsigned long int	current_time;
	struct timeval		time;


	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

t_program_data	*init_philo(int ac, char *av[])
{
	t_program_data	*data;
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_must_eat;

	philosophers = converter(av[1]);
	time_to_die = converter(av[2]);
	time_to_eat = converter(av[3]);
	time_to_sleep = converter(av[4]);

	if (ac == 6)
		times_each_must_eat = converter(av[5]);
	else
		times_each_must_eat = -1;

	data = malloc(sizeof(t_program_data));
	if (!data)
		return NULL;
	memset(data, 0, sizeof(t_program_data));
	*(int *)&data->number_of_philosophers = philosophers;
	*(int *)&data->time_to_die = time_to_die;
	*(int *)&data->time_to_eat = time_to_eat;
	*(int *)&data->time_to_sleep = time_to_sleep;
	*(int *)&data->number_of_times_each_philosopher_must_eat = times_each_must_eat;
	if (!is_valid_data(data))
	{
		free(data);
		return NULL;
	}
	return data;
}

int	manual(void)
{
	write(1, "Usage ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 119);
	return (0);
}

void	*routine(void *arg)
{
	(void)arg;
	printf("Hello from thread\n");
	return (NULL);
}

void	run_threads(t_program_data *data)
{
	int			i;
	pthread_t	th[data->number_of_philosophers];

	i = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("pthread_create failed");
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
		}
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
}

int	main(int ac, char *av[])
{
	t_program_data	*data;
	(void)av;
	if (ac < 5 || ac > 6)
		return (manual());
	data = init_philo(ac, av);
	if (!data)
		return (manual());
	run_threads(data);
	free(data);
	return (0);
}
