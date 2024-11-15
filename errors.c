/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:05 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/15 15:12:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manual(void)
{
	write(2, "\nError: invalid arguments\n\n", 27);
	printf("Usage ./philo\tnum_of_philos ms_to_die ms_to_eat \
ms_to_sleep num_of_times_each_must_eat\nWhere:\n");
	printf("\tnum_of_philos: > 0\n");
	printf("\ttime_to_die: > 0\n");
	printf("\ttime_to_eat: > 0\n");
	printf("\ttime_to_sleep: > 0\n");
	printf("\tnum_must_eat(optional): > 0\n");
	return (1);
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
}
