/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:11:42 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 19:00:25 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_data_fields(t_program_data *data, t_params *params)
{
	*(int *)&data->number_of_philosophers = params->philosophers;
	*(int *)&data->time_to_die = params->time_to_die;
	*(int *)&data->time_to_eat = params->time_to_eat;
	*(int *)&data->time_to_sleep = params->time_to_sleep;
	*(int *)&data->number_of_times_each_philosopher_must_eat = params->must_eat;
}

static int	initialize_semaphores(t_program_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal_time");
	sem_unlink("/start");
	sem_unlink("/eat_count");
	data->forks
		= sem_open("/forks", O_CREAT, 0644, data->number_of_philosophers);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->meal_time = sem_open("/meal_time", O_CREAT, 0644, 1);
	data->start = sem_open("/start", O_CREAT, 0644, 0);
	data->eat_count = sem_open("/eat_count", O_CREAT, 0644, 0);
	if ((data->forks == SEM_FAILED) || (data->forks == SEM_FAILED)
		|| (data->forks == SEM_FAILED) || (data->forks == SEM_FAILED)
		|| (data->forks == SEM_FAILED) || (data->forks == SEM_FAILED))
		return (1);
	return (0);
}

static void	init_philosophers(t_program_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
	{
		free(data);
		error_and_exit("Error: malloc failed\n", 1);
	}
	memset(data->philos, 0, sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		data->philos[i].must_eat
			= data->number_of_times_each_philosopher_must_eat;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		i++;
	}
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
	init_philosophers(data);
	if (initialize_semaphores(data))
	{
		(void)error_and_return("Error: init semaphores failed\n", 0);
		free_resources(data);
		return (NULL);
	}
	return (data);
}
