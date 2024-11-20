/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:45:36 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/20 17:58:25 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_mutexes(t_program_data *data)
{
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (error_and_return("Error: mutex init failed\n", 1));
	if (pthread_mutex_init(&data->mutex_stop, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_print);
		return (error_and_return("Error: mutex init failed\n", 1));
	}
	if (pthread_mutex_init(&data->mutex_main, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_print);
		pthread_mutex_destroy(&data->mutex_stop);
		return (error_and_return("Error: mutex init failed\n", 1));
	}
	return (0);
}

static int	initialize_forks(t_program_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (error_and_return("Error: malloc failed\n", 1));
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[--i]);
			free(data->forks);
			return (error_and_return("Error: mutex init failed\n", 1));
		}
		i++;
	}
	return (0);
}

static void	set_data_fields(t_program_data *data, t_params *params)
{
	*(int *)&data->number_of_philosophers = params->philosophers;
	*(int *)&data->time_to_die = params->time_to_die;
	*(int *)&data->time_to_eat = params->time_to_eat;
	*(int *)&data->time_to_sleep = params->time_to_sleep;
	*(int *)&data->number_of_times_each_philosopher_must_eat = params->must_eat;
}

t_program_data	*init_data(int ac, char *av[])
{
	t_params		params;
	t_program_data	*data;

	params = parse_arguments(ac, av);
	if (params.philosophers == -1)
		return (NULL);
	data = malloc(sizeof(t_program_data));
	if (!data)
	{
		(void)error_and_return("Error: malloc failed\n", 0);
		return (NULL);
	}
	memset(data, 0, sizeof(t_program_data));
	set_data_fields(data, &params);
	if (initialize_mutexes(data))
	{
		free(data);
		return (NULL);
	}
	if (initialize_forks(data))
		return (init_fork_failure(data));
	return (data);
}

t_philo	*init_philos(t_program_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
	{
		(void)error_and_return("Error: malloc failed\n", 0);
		return (NULL);
	}
	memset(philos, 0, sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].time_to_die = (size_t)data->time_to_die;
		philos[i].must_eat
			= (int)data->number_of_times_each_philosopher_must_eat;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork
			= &data->forks[(i + 1) % data->number_of_philosophers];
		philos[i].data = data;
		i++;
	}
	return (philos);
}
