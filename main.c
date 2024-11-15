/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/15 13:45:27 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if(philo->id % 2 != 0)
	{
		print_msg(philo->data, philo->id, 4);
		custom_wait(philo, philo->data->time_to_eat);
	}
	philo_does(philo);
	return (NULL);
}

int	create_threads(t_program_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].last_meal_time = data->start_time;
		if (pthread_create(&philos[i].thread_id, NULL, &routine, (void *)&philos[i]) != 0)
		{
			perror("pthread_create failed"); //join all threads and free all
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_program_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			perror("pthread_join failed"); //check
		}
		i++;
	}
}

void	run_threads(t_program_data *data)
{
	t_philo	*philos;

	philos = init_philos(data);
	if (!philos)
	{
		free_all(data, philos);
		destroy_mutexes(data);
		return ; // handle error and free
	}
	pthread_mutex_lock(&data->mutex_main);
	data->start_time = get_current_time();
	create_threads(data, philos);
	pthread_mutex_unlock(&data->mutex_main);
	check_stop_in_main(data, philos);
	join_threads(data, philos);
	destroy_mutexes(data);
	free_all(data, philos);
}

int	main(int ac, char *av[])
{
	t_program_data	*data;
	(void)av;
	if (ac < 5 || ac > 6)
		return (manual());
	data = init_data(ac, av);
	if (!data)
		return (manual());
	run_threads(data);
	return (0);
}
