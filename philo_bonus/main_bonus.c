/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:59 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/26 17:33:26 by irychkov         ###   ########.fr       */
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

static void	print_died(t_program_data *data, int id, size_t start_time)
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

void	print_eating(t_program_data *data, int id, size_t start_time)
{
	size_t	timestamp_in_ms;

	sem_wait(data->print);
	timestamp_in_ms = get_current_time() - start_time;
	printf("%zu %d is eating\n", timestamp_in_ms, id);
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

void	monitor_eating_completion(t_program_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		sem_wait(data->eat_count);
		i++;
	}
	sem_wait(data->print);
	sem_post(data->start);
	//printf("[DEBUG] sem_post: /start semaphore in monitor_eating_completion posted by thread %ld\n", pthread_self());
	//exit(0);
	//sleep(10);
}


int	run_philos(t_program_data *data)
{
	int		i;
	pid_t	monitor_pid;

	i = 0;
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		monitor_pid = fork();
		if (monitor_pid == -1)
		{
			perror("Error: fork failed for monitor");
			free_resources(data);
			exit(1);
		}
		if (monitor_pid == 0)
		{
			monitor_eating_completion(data);
			//exit(0);
		}
	}
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
			philosopher_routine(&data->philos[i]);
			free_resources(data);
			exit(0);
		}
		i++;
	}
	//sleep(2);
	//printf("[DEBUG] sem_wait: /start semaphore waited in run_philos by thread %ld\n", pthread_self());
	sem_wait(data->start);
	//printf("[DEBUG] sem_wait: /start semaphore passed in run_philos by thread %ld\n", pthread_self());
	i = 0;
	while (i < data->number_of_philosophers)
	{
		kill(data->philos[i].pid, 9);
		i++;
	}
	if (data->number_of_times_each_philosopher_must_eat != -1)
		kill(monitor_pid, 9);
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
