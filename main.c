/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 23:05:45 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* t_program_data	*init_philo(int ac, char *av[])
{
	t_program_data	*data;

	data = malloc(sizeof(t_program_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = converter(av[1]);
	data->time_to_die = converter(av[2]);
	data->time_to_eat = converter(av[3]);
	data->time_to_sleep = converter(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = converter(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (!is_valid_data(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
} */

void	*routine(void *arg)
{
	(void)arg;
	printf("Hello from thread\n");
	return (NULL);
}

void	run_threads(t_program_data *data)
{
	int				i;
	t_single_philo	*philos;
	pthread_t		th[data->number_of_philosophers];

	i = 0;
	philos = init_single_philos(data);
	if (!philos)
	{
		free_all(data, philos);
		destroy_mutexes(data);
		return ; // handle error and free
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&th[i], NULL, &routine, (void *)&philos[i]) != 0)
		{
			perror("pthread_create failed");
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
		}
		i++;
	}
	destroy_mutexes(data);
	free_all(data, philos);
}

int	main(int ac, char *av[])
{
	t_program_data	*data;
	(void)av;
	if (ac < 5 || ac > 6)
		return (manual());
	data = init_data(ac, av);
	if (!data)
		return (manual());
	run_threads(data);
	return (0);
}
