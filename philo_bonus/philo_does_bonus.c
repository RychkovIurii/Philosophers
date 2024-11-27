/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:15:48 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 18:55:49 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	size_t			current_time;
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		(void)error_and_return("Error: gettimeofday failed\n", 0);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

void	*monitor_death(void *arg)
{
	size_t	current_time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = philo->data->start_time;
	while (1)
	{
		usleep(2000);
		sem_wait(philo->data->meal_time);
		current_time = get_current_time();
		if ((current_time - philo->last_meal_time)
			>= (size_t)philo->data->time_to_die)
		{
			sem_post(philo->data->meal_time);
			print_died(philo->data, philo->id, philo->data->start_time);
			return (NULL);
		}
		sem_post(philo->data->meal_time);
	}
	return (NULL);
}

static void	create_monitor_and_detach(t_philo *philo)
{
	pthread_t	th;

	if (pthread_create(&th, NULL, &monitor_death, (void *)philo) != 0)
	{
		sem_post(philo->data->start);
		exit (1);
	}
	if (pthread_detach(th) != 0)
	{
		sem_post(philo->data->start);
		exit (1);
	}
}

static void	eat(t_philo *philo, size_t start_time)
{
	sem_wait(philo->data->forks);
	print_fork(philo->data, philo->id, start_time);
	sem_wait(philo->data->forks);
	print_fork(philo->data, philo->id, start_time);
	print_eating(philo->data, philo->id, start_time);
	sem_wait(philo->data->meal_time);
	philo->last_meal_time = get_current_time();
	sem_post(philo->data->meal_time);
	usleep(philo->data->time_to_eat * 1000);
	if (philo->must_eat != -1)
	{
		philo->times_eaten++;
		if (philo->times_eaten == philo->must_eat)
			sem_post(philo->data->eat_count);
	}
	usleep(200);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philosopher_routine(t_philo *philo)
{
	size_t		start_time;

	start_time = philo->data->start_time;
	create_monitor_and_detach(philo);
	if (philo->id % 2 != 0)
	{
		print_thinking(philo->data, philo->id, start_time);
		usleep(1000);
	}
	while (1)
	{
		eat(philo, start_time);
		print_sleeping(philo->data, philo->id, start_time);
		usleep(philo->data->time_to_sleep * 1000);
		print_thinking(philo->data, philo->id, start_time);
		usleep(500);
	}
}
