/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:14 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/20 14:02:13 by irychkov         ###   ########.fr       */
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

	start_time = get_current_time();
	/* if (is_stop_in_threads(philo->data))
		return ; */
	while (1)
	{
		current_time = get_current_time();
		if (current_time - start_time >= time_to_wait)
			break ;
		if (is_stop_in_threads(philo->data))
			break ;
		usleep(1500);
	}
}

int	check_starving(t_program_data *data, t_philo *philos, size_t start_time)
{
	int		i;
	size_t	current_time;

	i = 0;
	//usleep(10000 * data->time_to_die - 10000);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_main);
		current_time = get_current_time();
		if (philos[i].last_meal_time == 0)
		{
			pthread_mutex_unlock(&data->mutex_main);
			usleep(1000);
			i++;
			continue ;
		}
		if ((current_time - philos[i].last_meal_time)
			> (size_t)data->time_to_die)
		{
			pthread_mutex_unlock(&data->mutex_main);
			print_msg(philos[i].data, philos[i].id, 5, start_time);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex_main);
		i++;
	}
	return (0);
}

/* int	check_starving(t_philo *philo)
{
	size_t	current_time;

	current_time = get_current_time();
	if ((current_time - philo->last_meal_time) > philo->time_to_die)
	{
		print_msg(philo->data, philo->id, 5, philo->start_time);
		return (1);
	}
	return (0);
} */

void	check_stop_in_main(t_program_data *data, t_philo *philos, size_t start_time)
{
	while (1)
	{
		usleep(1000);
		if (check_starving(data, philos, start_time))
			break ;
		if (is_stop_in_threads(data))
			break ;
	}
}
