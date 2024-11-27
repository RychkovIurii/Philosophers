/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:21:52 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 20:45:43 by irychkov         ###   ########.fr       */
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

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_fork(philo->data, philo->id, philo->start_time);
	pthread_mutex_lock(philo->right_fork);
	print_fork(philo->data, philo->id, philo->start_time);
	pthread_mutex_lock(&philo->data->mutex_main);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->mutex_main);
	print_eating(philo->data, philo->id, philo->start_time);
	custom_wait(philo, philo->data->time_to_eat);
	philo->times_eaten++;
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
		print_sleeping(philo->data, philo->id, philo->start_time);
		custom_wait(philo, philo->data->time_to_sleep);
		print_thinking(philo->data, philo->id, philo->start_time);
		usleep(100);
	}
}
