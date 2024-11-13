/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:28:29 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/13 12:09:34 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_program_data
{
	const int		number_of_philosophers;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	const int		number_of_times_each_philosopher_must_eat;
	size_t			start_time;
	int				stop_flag;
	pthread_mutex_t	mutex_main;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	*forks;
}	t_program_data;

typedef struct s_single_philo {
	int					id;
	int					times_eaten;
	int					must_eat;
	size_t				last_meal_time;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_program_data		*data;
} t_single_philo;

int					manual(void);
int					converter(char *str);
t_program_data		*init_data(int ac, char *av[]);
t_single_philo		*init_single_philos(t_program_data *data);
void				destroy_mutexes(t_program_data *data);
void				free_all(t_program_data *data, t_single_philo *philo);
size_t				get_current_time(void);

#endif
