/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 20:41:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_main);
	philo->last_meal_time = philo->data->start_time;
	philo->start_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->mutex_main);
	if (philo->number_of_philosophers == 1)
	{
		print_thinking(philo->data, philo->id, philo->start_time);
		pthread_mutex_lock(philo->left_fork);
		print_fork(philo->data, philo->id, philo->start_time);
		custom_wait(philo, philo->data->time_to_die + 1);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		print_thinking(philo->data, philo->id, philo->start_time);
		custom_wait(philo, philo->data->time_to_eat);
	}
	philo_does(philo);
	return (NULL);
}

static int	create_threads(t_program_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				&routine, (void *)&philos[i]) != 0)
		{
			while (i > 0)
				pthread_join(philos[--i].thread_id, NULL);
			destroy_free_all(data, philos);
			return (error_and_return("Error: pthread_create failed\n", 1));
		}
		i++;
	}
	return (0);
}

static int	join_threads(t_program_data *data, t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			status = error_and_return("Error: pthread_join failed\n", 1);
		i++;
	}
	destroy_free_all(data, philos);
	return (status);
}

static int	run_threads(t_program_data *data)
{
	ssize_t	start;
	t_philo	*philos;

	philos = init_philos(data);
	if (!philos)
	{
		destroy_free_all(data, philos);
		return (1);
	}
	pthread_mutex_lock(&data->mutex_main);
	if (create_threads(data, philos))
	{
		pthread_mutex_unlock(&data->mutex_main);
		return (1);
	}
	data->start_time = get_current_time();
	start = data->start_time;
	pthread_mutex_unlock(&data->mutex_main);
	check_stop_in_main(data, philos, start);
	return (join_threads(data, philos));
}

int	main(int ac, char *av[])
{
	t_program_data	*data;

	if (ac < 5 || ac > 6)
		return (manual());
	data = init_data(ac, av);
	if (!data)
		return (1);
	return (run_threads(data));
}
