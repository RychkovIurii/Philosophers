/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:15:30 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 20:46:31 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died_set_flag(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d died\n", timestamp_in_ms, id);
	pthread_mutex_lock(&data->mutex_stop);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	usleep(500);
	pthread_mutex_unlock(&data->mutex_print);
}

void	print_thinking(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is thinking\n", timestamp_in_ms, id);
	pthread_mutex_unlock(&data->mutex_print);
}

void	print_sleeping(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is sleeping\n", timestamp_in_ms, id);
	pthread_mutex_unlock(&data->mutex_print);
}

void	print_eating(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is eating\n", timestamp_in_ms, id);
	pthread_mutex_unlock(&data->mutex_print);
}

void	print_fork(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d has taken a fork\n", timestamp_in_ms, id);
	pthread_mutex_unlock(&data->mutex_print);
}
