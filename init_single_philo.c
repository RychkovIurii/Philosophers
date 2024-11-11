/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_single_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:45:28 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 23:04:50 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_single_philo *init_single_philos(t_program_data *data)
{
	int				i;
	t_single_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_single_philo) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(t_single_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].times_eaten = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		philos[i].data = data;
		i++;
	}
	return (philos);
}
