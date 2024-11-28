/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:14:53 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/28 13:56:13 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_died(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d died\n", timestamp_in_ms, id);
	sem_post(data->start);
}

void	print_thinking(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is thinking\n", timestamp_in_ms, id);
	sem_post(data->print);
}

void	print_sleeping(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is sleeping\n", timestamp_in_ms, id);
	sem_post(data->print);
}

void	print_eating(t_program_data *data, t_philo *philo, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	sem_wait(data->meal_time);
	philo->last_meal_time = get_current_time();
	timestamp_in_ms = philo->last_meal_time - start_time;
	sem_post(data->meal_time);
	printf("%zu %d is eating\n", timestamp_in_ms, philo->id);
	sem_post(data->print);
}

void	print_fork(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d has taken a fork\n", timestamp_in_ms, id);
	sem_post(data->print);
}
