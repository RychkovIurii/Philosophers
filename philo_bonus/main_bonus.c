/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:59 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/21 18:36:36 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher_routine(t_philo *philo)
{
	(void) philo;
	printf("Hello from philo\n");
}

int	run_philos(t_program_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			//think
		}
		if (data->philos[i].pid == 0)
		{
			printf("We are in child\n");
			philosopher_routine(&data->philos[i]);
			free_resources(data);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
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
