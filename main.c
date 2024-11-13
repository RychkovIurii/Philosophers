/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:18:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/13 12:58:10 by irychkov         ###   ########.fr       */
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
/* 
1. timestamp_in_ms X has taken a fork
2. timestamp_in_ms X is eating
3. timestamp_in_ms X is sleeping
4. timestamp_in_ms X is thinking
5. timestamp_in_ms X died
 */

void	print_msg(t_program_data *data, int id, int	message_code)
{
	size_t	timestamp_in_ms;

	pthread_mutex_lock(&data->mutex_print);
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop_flag == 1)
	{
		pthread_mutex_unlock(&data->mutex_stop);
		pthread_mutex_unlock(&data->mutex_print);
		return;
	}
	pthread_mutex_unlock(&data->mutex_stop);
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
	{
		printf("%zu %d died\n", timestamp_in_ms, id);
		pthread_mutex_lock(&data->mutex_stop);
		data->stop_flag = 1;
		pthread_mutex_unlock(&data->mutex_stop);
		pthread_mutex_unlock(&data->mutex_print);
		//usleep(10);
		return ;
	}

	pthread_mutex_unlock(&data->mutex_print);
}


void	custom_wait(t_program_data *data, size_t time_to_wait)
{
	size_t	start_time;
	size_t	current_time;

	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if (current_time - start_time >= time_to_wait)
			break;
		pthread_mutex_lock(&data->mutex_stop);
		if (data->stop_flag)
		{
			pthread_mutex_unlock(&data->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_stop);
		usleep(10);
	}
}

void	philo_does(t_single_philo *single_philo)
{
	int	times;

	if (single_philo->must_eat == -1)
		times = 1;
	else
		times = single_philo->must_eat;

	while (times)
	{
		pthread_mutex_lock(single_philo->left_fork);
		print_msg(single_philo->data, single_philo->id, 1);
		pthread_mutex_lock(single_philo->right_fork);
		print_msg(single_philo->data, single_philo->id, 1);
		print_msg(single_philo->data, single_philo->id, 2);
		custom_wait(single_philo->data, single_philo->data->time_to_eat);
		pthread_mutex_unlock(single_philo->right_fork);
		pthread_mutex_unlock(single_philo->left_fork);
		print_msg(single_philo->data, single_philo->id, 3);
		custom_wait(single_philo->data, single_philo->data->time_to_sleep);
		print_msg(single_philo->data, single_philo->id, 4);
		/* print_msg(single_philo->data, single_philo->id, 5); */
		if (single_philo->must_eat != -1)
			times--;
	}
	print_msg(single_philo->data, single_philo->id, 5);
}

//pthread_barrier_t barrier;

void	*routine(void *philo)
{
	t_single_philo *single_philo;

	single_philo = (t_single_philo *)philo;
	pthread_mutex_lock(&single_philo->data->mutex_main);
	pthread_mutex_unlock(&single_philo->data->mutex_main);
/* 	pthread_barrier_wait(&barrier); */
	/* print_msg(single_philo->data, single_philo->id, 1);
	sleep(1);
	print_msg(single_philo->data, single_philo->id, 5); */
	if(single_philo->id % 2 != 0)
	{
		print_msg(single_philo->data, single_philo->id, 4);
		custom_wait(single_philo->data, single_philo->data->time_to_eat / 2);
	}
	philo_does(philo);
	return (NULL);
}

void	check_stop(t_program_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_stop);
		if (data->stop_flag)
		{
			pthread_mutex_unlock(&data->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_stop);
		usleep(10);
	}
}

void	run_threads(t_program_data *data)
{
	int				i;
	t_single_philo	*philo;
	pthread_t		th[data->number_of_philosophers];

	i = 0;
	philo = init_single_philos(data);
	if (!philo)
	{
		free_all(data, philo);
		destroy_mutexes(data);
		return ; // handle error and free
	}
/* 	pthread_barrier_init(&barrier, NULL, 201); */
	pthread_mutex_lock(&data->mutex_main);
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&th[i], NULL, &routine, (void *)&philo[i]) != 0)
		{
			perror("pthread_create failed");
		}
		i++;
	}
	data->start_time = get_current_time();
	pthread_mutex_unlock(&data->mutex_main);
/* 	pthread_barrier_wait(&barrier); */
	check_stop(data);
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
	free_all(data, philo);
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
