/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:15:48 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/26 23:11:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	size_t				current_time;
	struct timeval		time;

	if (gettimeofday(&time, NULL) != 0)
		write(2, "Error: gettimeofday failed\n", 27);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	size_t	current_time;

	philo->last_meal_time = philo->data->start_time;
	while (1)
	{
		usleep(2000);
		sem_wait(philo->data->meal_time);
		current_time = get_current_time();
		if ((current_time - philo->last_meal_time) >= (size_t)philo->data->time_to_die)
		{
			sem_post(philo->data->meal_time);
			print_died(philo->data, philo->id, philo->data->start_time);
			return (NULL);
		}
		sem_post(philo->data->meal_time);
	}
	return (NULL);

}

void	philosopher_routine(t_philo *philo)
{
	size_t start_time;
	pthread_t	th;

	start_time = philo->data->start_time;
	pthread_create(&th, NULL, &monitor_death, (void *)philo);
	pthread_detach(th);
	if (philo->id % 2 != 0)
	{
		print_thinking(philo->data, philo->id, start_time);
		usleep(1000/* philo->data->time_to_eat * 500 */);
	}
	while(1)
	{
		//print_thinking(philo->data, philo->id, start_time);
		/* if (philo->id % 2 == 0)
		{
			usleep(philo->data->time_to_eat * 500);
		} */
		sem_wait(philo->data->forks);
		print_fork(philo->data, philo->id, philo->data->start_time);
		sem_wait(philo->data->forks);
		print_fork(philo->data, philo->id, philo->data->start_time);
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
		/* usleep(200); */ //Think how can I slow down here
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_sleeping(philo->data, philo->id, start_time);
		usleep(philo->data->time_to_sleep * 1000);
		print_thinking(philo->data, philo->id, start_time);
		usleep(300);
	}
}
