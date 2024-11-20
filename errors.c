/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:05 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/20 17:59:53 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error_and_return(char *msg, int error_code)
{
	write(2, msg, ft_strlen(msg));
	return (error_code);
}

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

void	destroy_free_all(t_program_data *data, t_philo *philos)
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
	free(data->forks);
	free(data);
	free(philos);
}

void	*init_fork_failure(t_program_data *data)
{
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_stop);
	pthread_mutex_destroy(&data->mutex_main);
	free(data);
	return (NULL);
}
