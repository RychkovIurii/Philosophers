/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:10:57 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/13 15:58:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_single_philo *init_philos(t_program_data *data)
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
		philo[i].must_eat = (int)data->number_of_times_each_philosopher_must_eat;
		philo[i].last_meal_time = data->start_time;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		philo[i].data = data;
		i++;
	}
	return (philo);
}
