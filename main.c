/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/15 13:17:19 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died_set_flag(t_program_data *data, int id, size_t ms)
{
	printf("%zu %d died\n", ms, id);
	pthread_mutex_lock(&data->mutex_stop);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	usleep(500);
}

void	print_msg(t_program_data *data, int id, int	message_code)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	if (is_stop_in_threads(data))
	{
		pthread_mutex_unlock(&data->mutex_print);
		return;
	}
	timestamp_in_ms = get_current_time() - data->start_time;
	if (message_code == 1)
		printf("%zu %d has taken a fork\n", timestamp_in_ms, id);
	else if (message_code == 2)
		printf("%zu %d is eating\n", timestamp_in_ms, id);
	else if (message_code == 3)
		printf("%zu %d is sleeping\n", timestamp_in_ms, id);
	else if (message_code == 4)
		printf("%zu %d is thinking\n", timestamp_in_ms, id);
	else if (message_code == 5)
		print_died_set_flag(data, id, timestamp_in_ms);
	pthread_mutex_unlock(&data->mutex_print);
}

void	philo_does(t_philo *philo)
{
	int	times;

	if (philo->must_eat == -1)
		times = 1;
	else
		times = philo->must_eat;
	while (times)
	{
		if (is_stop_in_threads(philo->data))
			break ;
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo->data, philo->id, 1);
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo->data, philo->id, 1);
		print_msg(philo->data, philo->id, 2);
		pthread_mutex_lock(&philo->data->mutex_main);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->data->mutex_main);
		philo->times_eaten++;
		custom_wait(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->must_eat == philo->times_eaten)
		{
			philo->data->have_eaten++;
			if (philo->data->have_eaten == philo->data->number_of_philosophers)
			{
				pthread_mutex_lock(&philo->data->mutex_stop);
				philo->data->stop_flag = 1;
				pthread_mutex_unlock(&philo->data->mutex_stop);
			}
		}
		print_msg(philo->data, philo->id, 3);
		custom_wait(philo, philo->data->time_to_sleep);
		print_msg(philo->data, philo->id, 4);
		if (philo->must_eat != -1)
			times--;
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if(philo->id % 2 != 0)
	{
		print_msg(philo->data, philo->id, 4);
		custom_wait(philo, philo->data->time_to_eat);
	}
	philo_does(philo);
	return (NULL);
}

void	run_threads(t_program_data *data)
{
	int				i;
	t_philo	*philos;
	pthread_t		th[data->number_of_philosophers];

	i = 0;
	philos = init_philos(data);
	if (!philos)
	{
		free_all(data, philos);
		destroy_mutexes(data);
		return ; // handle error and free
	}
	pthread_mutex_lock(&data->mutex_main);
	data->start_time = get_current_time();
	while (i < data->number_of_philosophers)
	{
		philos[i].last_meal_time = data->start_time;
		if (pthread_create(&th[i], NULL, &routine, (void *)&philos[i]) != 0)
		{
			perror("pthread_create failed");
		}
		i++;
	}
	pthread_mutex_unlock(&data->mutex_main);
	check_stop_in_main(data, philos);
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
