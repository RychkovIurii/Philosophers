/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:00:23 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/24 16:26:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	manual(void)
{
	write(2, "\nError: invalid arguments\n\n", 27);
	printf("Usage ./philo_bonus\tnum_of_philos ms_to_die ms_to_eat \
ms_to_sleep num_of_times_each_must_eat\nWhere:\n");
	printf("\tnum_of_philos: > 0\n");
	printf("\ttime_to_die: > 0\n");
	printf("\ttime_to_eat: > 0\n");
	printf("\ttime_to_sleep: > 0\n");
	printf("\tnum_must_eat(optional): > 0\n");
	return (1);
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error_and_return(char *msg, int error_code)
{
	write(2, msg, ft_strlen(msg));
	return (error_code);
}

void	free_resources(t_program_data *data)
{
	free(data->philos);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->start);
	sem_close(data->eat_count);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/start");
	sem_unlink("/eat_count");
	free(data);
}
