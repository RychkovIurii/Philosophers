/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:05 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/14 21:45:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manual(void)
{
	write(1, "Usage ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 119);
	return (0);
}

void	free_all(t_program_data *data, t_philo *philos)
{
	free(data->forks);
	free(data);
	free(philos);
}

void	destroy_mutexes(t_program_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_stop);
	pthread_mutex_destroy(&data->mutex_main);
	pthread_mutex_destroy(&data->mutex_last_meal);
}
