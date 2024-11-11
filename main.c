/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 18:05:07 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat] */

#include "philo.h"

typedef struct s_philo
{
	const int		number_of_philosophers;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	const int		number_of_times_each_philosopher_must_eat;
}	t_philo;

int	init_philo(int ac, char *av[], t_philo *data)
{
	data->number_of_philosophers = converter(av[1]);
	data->time_to_die = converter(av[2]);
	data->time_to_eat = converter(av[3]);
	data->time_to_sleep = converter(av[4]);
	data->number_of_times_each_philosopher_must_eat(av[5]);

}

int	manual(void)
{
	write(1, "Usage ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 119);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	data;
	(void)av;
	if (ac < 5 || ac > 6)
		return (manual());
	if (init_philo(ac , av, &data))
		return (manual());
	return (0);
}