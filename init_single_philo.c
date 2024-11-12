/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_single_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:45:28 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/12 16:48:46 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_single_philo *init_single_philos(t_program_data *data)
{
	int				i;
	t_single_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_single_philo) * data->number_of_philosophers);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_single_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].last_meal_time = data->start_time;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		philo[i].data = data;
		i++;
	}
	return (philo);
}
