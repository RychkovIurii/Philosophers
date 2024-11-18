/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:14 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/18 20:13:27 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	size_t				current_time;
	struct timeval		time;

	if (gettimeofday(&time, NULL) != 0)
		write(2, "Error: gettimeofday failed\n", 27);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

int	is_stop_in_threads(t_program_data *data)
{
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop_flag)
	{
		pthread_mutex_unlock(&data->mutex_stop);
		return (1);
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
		if (check_starving(philo))
			break ;
		if (is_stop_in_threads(philo->data))
			break ;
		usleep(500);
	}
}

int	check_starving(t_philo *philo)
{
	size_t	current_time;

	current_time = get_current_time();
	if ((current_time - philo->last_meal_time) > philo->time_to_die)
	{
		print_msg(philo->data, philo->id, 5);
		return (1);
	}
	return (0);
}

void	check_stop_in_main(t_program_data *data)
{
	while (1)
	{
		usleep(500);
		if (is_stop_in_threads(data))
			break ;
	}
}
