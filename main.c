/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 19:44:08 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat] */

#include "philo.h"
#include <stdio.h>

typedef struct s_philo
{
	const int		number_of_philosophers;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	const int		number_of_times_each_philosopher_must_eat;
}	t_philo;

int	is_valid_data(const t_philo *data)
{
	if (data->number_of_philosophers < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (0);
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	return (1);
}

/* t_philo	*init_philo(int ac, char *av[])
{
	t_philo	*data;

	data = malloc(sizeof(t_philo));
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


t_philo	*init_philo(int ac, char *av[])
{
	t_philo	*data;
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_must_eat;

	philosophers = converter(av[1]);
	time_to_die = converter(av[2]);
	time_to_eat = converter(av[3]);
	time_to_sleep = converter(av[4]);

	if (ac == 6)
		times_each_must_eat = converter(av[5]);
	else
		times_each_must_eat = -1;

	data = malloc(sizeof(t_philo));
	if (!data)
		return NULL;
	*(int *)&data->number_of_philosophers = philosophers;
	*(int *)&data->time_to_die = time_to_die;
	*(int *)&data->time_to_eat = time_to_eat;
	*(int *)&data->time_to_sleep = time_to_sleep;
	*(int *)&data->number_of_times_each_philosopher_must_eat = times_each_must_eat;
	if (!is_valid_data(data))
	{
		free(data);
		return NULL;
	}
	return data;
}

int	manual(void)
{
	write(1, "Usage ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 119);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*data;
	(void)av;
	if (ac < 5 || ac > 6)
		return (manual());
	data = init_philo(ac, av);
	if (!data)
		return (manual());
	free(data);
	return (0);
}
