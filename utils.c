/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:14 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/14 22:18:12 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	size_t				current_time;
	struct timeval		time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

int	is_stop_in_threads(t_program_data *data)
{
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop_flag)
	{
		pthread_mutex_unlock(&data->mutex_stop);
		return (1) ;
	}
	pthread_mutex_unlock(&data->mutex_stop);
	return (0);
}

void	custom_wait(t_philo *philo, size_t time_to_wait)
{
	size_t	start_time;
	size_t	current_time;

	if (is_stop_in_threads(philo->data))
		return ;
	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if (current_time - start_time >= time_to_wait)
			break ;
		if (is_stop_in_threads(philo->data))
			break ;
		usleep(10);
	}
}

int	check_starving(t_program_data *data, t_philo *philos)
{
	int		i;
	size_t	current_time;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		current_time = get_current_time();
		pthread_mutex_lock(&data->mutex_last_meal);
		if ((current_time - philos[i].last_meal_time) > (size_t)data->time_to_die)
		{
			pthread_mutex_unlock(&data->mutex_last_meal);
			print_msg(philos[i].data, philos[i].id, 5);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex_last_meal);
		i++;
	}
	return (0);
}

void	check_stop_in_main(t_program_data *data, t_philo *philos)
{
	usleep(200000);
	while (1)
	{
		if (check_starving(data, philos))
			break ;
		if (is_stop_in_threads(data))
			break ;
		usleep(50);
	}
}
