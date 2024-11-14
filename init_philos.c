/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:10:57 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/14 19:29:46 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philos(t_program_data *data)
{
	int				i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].times_eaten = 0;
		philos[i].must_eat = (int)data->number_of_times_each_philosopher_must_eat;
		philos[i].last_meal_time = data->start_time;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		philos[i].data = data;
		i++;
	}
	return (philos);
}
