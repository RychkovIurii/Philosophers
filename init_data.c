/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:45:36 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/14 19:22:40 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_data(const t_program_data *data)
{
	if (data->number_of_philosophers < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (0);
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	return (1);
}

t_program_data	*init_data(int ac, char *av[])
{
	int				i;
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_must_eat;
	t_program_data	*data;

	i = 0;
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks) {
		free(data);
		return NULL;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	pthread_mutex_init(&data->mutex_main, NULL);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return data;
}
