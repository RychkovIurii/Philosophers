/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:59 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 17:19:33 by irychkov         ###   ########.fr       */
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
	usleep(424242);
	exit(0);
}

void	check_starving(t_program_data *data, pid_t *monitor_pid)
{
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		*monitor_pid = fork();
		if (*monitor_pid == -1)
		{
			free_resources(data);
			error_and_exit("Error: fork failed for monitor\n", 1);
		}
		if (*monitor_pid == 0)
			monitor_eating_completion(data);
	}
}

int	kill_processes(t_program_data *data, pid_t monitor_pid)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		if (kill(monitor_pid, 9) == -1)
			exit_code = error_and_return("Failed to kill monitor process\n", 1);
	}
	while (i < data->number_of_philosophers)
	{
		if (kill(data->philos[i].pid, 9) == -1)
			exit_code = error_and_return("Failed to kill philo process\n", 1);
		if (waitpid(data->philos[i].pid, &status, 0) == -1)
			exit_code = error_and_return("Failed to wait philo process\n", 1);
		if (!WIFSIGNALED(status))
			exit_code = error_and_return("Failed pthread in philo process\n", 1);
		i++;
	}
	return (exit_code);
}

int	run_philos(t_program_data *data)
{
	int		i;
	int		exit_code;
	pid_t	monitor_pid;

	i = 0;
	exit_code = 0;
	check_starving(data, &monitor_pid);
	data->start_time = get_current_time();
	while (i < data->number_of_philosophers)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			kill(monitor_pid, 9);
			while (i > 0)
				kill(data->philos[--i].pid, 9);
			free_resources(data);
			error_and_return("Error: fork failed for philos\n", 1);
		}
		if (data->philos[i].pid == 0)
			philosopher_routine(&data->philos[i]);
		i++;
	}
	sem_wait(data->start);
	exit_code = kill_processes(data, monitor_pid);
	free_resources(data);
	return (exit_code);
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
