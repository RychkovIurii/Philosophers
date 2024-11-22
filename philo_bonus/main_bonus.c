/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:59 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/22 17:22:11 by irychkov         ###   ########.fr       */
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

static void	print_died_exit(t_program_data *data, int id, size_t ms)
{
	int i;

	printf("%zu %d died\n", ms, id);
	i = 0;
	while(i < data->number_of_philosophers)
	{
		if (id != data->philos[i].id)
			kill(data->philos[i].pid, 9);
		i++;
	}
	kill(data->philos[i].id, 9);
	exit(100);
}

void	print_msg(t_program_data *data, int id, int message_code,
		size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
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
		print_died_exit(data, id, timestamp_in_ms);
	sem_post(data->print);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	size_t	current_time;

	while (1)
	{
		current_time = get_current_time();
		if ((current_time - philo->last_meal_time) >= (size_t)philo->data->time_to_die)
		{
			print_msg(philo->data, philo->id, 5, philo->data->start_time);
		}
	}
	return (NULL);

}

void	philosopher_routine_even(t_philo *philo)
{
	pthread_t	th;
	
	pthread_create(&th, NULL, &monitor_death, (void *)&philo);
	pthread_detach(th);
	while(1)
	{
		sem_wait(philo->data->forks);
		print_msg(philo->data, philo->id, 1, philo->data->start_time);
		sem_wait(philo->data->forks);
		print_msg(philo->data, philo->id, 1, philo->data->start_time);
		print_msg(philo->data, philo->id, 2, philo->data->start_time);
		philo->last_meal_time = get_current_time();
		usleep(philo->data->time_to_eat * 1000);
		philo->times_eaten++;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_msg(philo->data, philo->id, 3, philo->data->start_time);
		usleep(philo->data->time_to_sleep * 1000);
		print_msg(philo->data, philo->id, 4, philo->data->start_time);
	}
}

void	philosopher_routine_odd(t_philo *philo)
{
	pthread_t	th;

	pthread_create(&th, NULL, &monitor_death, (void *)&philo);
	pthread_detach(th);
	usleep(1000);
	while(1)
	{
		print_msg(philo->data, philo->id, 4, philo->data->start_time);
		sem_wait(philo->data->forks);
		print_msg(philo->data, philo->id, 1, philo->data->start_time);
		sem_wait(philo->data->forks);
		print_msg(philo->data, philo->id, 1, philo->data->start_time);
		print_msg(philo->data, philo->id, 2, philo->data->start_time);
		philo->last_meal_time = get_current_time();
		usleep(philo->data->time_to_eat * 1000);
		philo->times_eaten++;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_msg(philo->data, philo->id, 3, philo->data->start_time);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

int	run_philos(t_program_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philosophers)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			//think
		}
		if (data->philos[i].pid == 0)
		{
			data->philos[i].last_meal_time = data->start_time;
			if (i % 2 == 0)
				philosopher_routine_even(&data->philos[i]);
			else
				philosopher_routine_odd(&data->philos[i]);
			free_resources(data);
			exit(0);
		}
		i++;
	}
	//sleep(2);
	//sem_post(data->start);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		//kill(data->philos[i].pid, 9);
		waitpid(data->philos[i].pid, NULL, 0);
		i++;
	}
	free_resources(data);
	return (0);
}

int	main(int ac, char *av[])
{
	t_program_data	*data;

	if (ac < 5 || ac > 6)
		return (manual());
	data = init_data(ac, av);
	if (!data)
		return (1);
	return (run_philos(data));
}
