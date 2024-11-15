/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:28:29 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/15 17:56:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_program_data
{
	const int		number_of_philosophers;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	const int		number_of_times_each_philosopher_must_eat;
	size_t			start_time;
	int				have_eaten;
	int				stop_flag;
	pthread_mutex_t	mutex_main;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	*forks;
}	t_program_data;

typedef struct s_philo
{
	int					id;
	int					times_eaten;
	int					must_eat;
	size_t				last_meal_time;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_program_data		*data;
}	t_philo;

typedef struct s_params
{
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_params;

t_program_data	*init_data(int ac, char *av[]);
t_params		parse_arguments(int ac, char *av[]);
t_philo			*init_philos(t_program_data *data);
void			philo_does(t_philo *philo);
void			check_stop_in_main(t_program_data *data, t_philo *philos);
void			print_msg(t_program_data *data, int id, int message_code);
int				check_starving(t_program_data *data, t_philo *philos);
size_t			get_current_time(void);
void			custom_wait(t_philo *philo, size_t time_to_wait);
int				is_stop_in_threads(t_program_data *data);
void			free_all(t_program_data *data, t_philo *philos);
void			destroy_mutexes(t_program_data *data);
int				error_and_return(char *msg, int error_code);
int				manual(void);
#endif
