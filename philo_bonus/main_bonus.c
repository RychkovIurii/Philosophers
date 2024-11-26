/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:59 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/26 23:06:30 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	check_starving(t_program_data *data, pid_t *monitor_pid)
{
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		*monitor_pid = fork();
		if (*monitor_pid == -1)
		{
			perror("Error: fork failed for monitor");
			free_resources(data);
			exit(1);
		}
		if (*monitor_pid == 0)
		{
			monitor_eating_completion(data);
			//usleep(424242);
			//exit(0); //Check if this is needed
		}
	}
}

void	kill_processes(t_program_data *data, pid_t monitor_pid)
{
	int	i;

	i = 0;
	if (data->number_of_times_each_philosopher_must_eat != -1)
		kill(monitor_pid, 9);
	while (i < data->number_of_philosophers)
	{
		kill(data->philos[i].pid, 9);
		i++;
	}
}

int	run_philos(t_program_data *data)
{
	int		i;
	pid_t	monitor_pid;

	i = 0;
	check_starving(data, &monitor_pid);
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
			//usleep(424242);
			exit(0);
		}
		i++;
	}
	sem_wait(data->start);
	kill_processes(data, monitor_pid);
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
