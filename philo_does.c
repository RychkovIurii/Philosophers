/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:21:52 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/19 11:19:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_have_eaten(t_philo *philo)
{
	if (philo->must_eat == philo->times_eaten)
	{
		pthread_mutex_lock(&philo->data->mutex_main);
		philo->data->have_eaten++;
		if (philo->data->have_eaten == philo->data->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo->data->mutex_main);
			pthread_mutex_lock(&philo->data->mutex_stop);
			philo->data->stop_flag = 1;
			pthread_mutex_unlock(&philo->data->mutex_stop);
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_main);
	}
}

static void	print_died_set_flag(t_program_data *data, int id, size_t ms)
{
	printf("%zu %d died\n", ms, id);
	pthread_mutex_lock(&data->mutex_stop);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	usleep(500);
}

void	print_msg(t_program_data *data, int id, int message_code, size_t start_time)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return ;
	}
	timestamp_in_ms = get_current_time() - start_time;
	if (message_code == 1)
		printf("%zu %d has taken a fork\n", timestamp_in_ms, id);
	else if (message_code == 2)
		printf("%zu %d is eating\n", timestamp_in_ms, id);
	else if (message_code == 3)
		printf("%zu %d is sleeping\n", timestamp_in_ms, id);
	else if (message_code == 4)
		printf("%zu %d is thinking\n", timestamp_in_ms, id);
	else if (message_code == 5)
		print_died_set_flag(data, id, timestamp_in_ms);
	pthread_mutex_unlock(&data->mutex_print);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	(void)check_starving(philo);
	print_msg(philo->data, philo->id, 1, philo->start_time);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo->data, philo->id, 1, philo->start_time);
	(void)check_starving(philo);
	print_msg(philo->data, philo->id, 2, philo->start_time);
	philo->last_meal_time = get_current_time();
	philo->times_eaten++;
	custom_wait(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_does(t_philo *philo)
{
	while (1)
	{
		if (is_stop_in_threads(philo->data))
			break ;
		eat(philo);
		if (philo->must_eat != -1)
			check_have_eaten(philo);
		print_msg(philo->data, philo->id, 3, philo->start_time);
		custom_wait(philo, philo->data->time_to_sleep);
		print_msg(philo->data, philo->id, 4, philo->start_time);
		usleep(100);
	}
}
