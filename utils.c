/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:14 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/13 19:07:59 by irychkov         ###   ########.fr       */
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

void	custom_wait(t_single_philo *philo, size_t time_to_wait, int does_eat)
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
		if (!does_eat)
			check_starving(philo , current_time);
		if (is_stop_in_threads(philo->data))
			break ;
		usleep(10);
	}
}

void	check_starving(t_single_philo *philo, size_t current_time)
{
	if ((current_time - philo->last_meal_time) > (size_t)philo->data->time_to_die)
	{
		print_msg(philo->data, philo->id, 5);
	}
}

void	check_stop_in_main(t_program_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_main);
		if (data->have_eaten == data->number_of_philosophers)
		{
			pthread_mutex_unlock(&data->mutex_main);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_main);
		if (is_stop_in_threads(data))
			break ;
		usleep(100);
	}
}
