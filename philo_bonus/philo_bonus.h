/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:48:05 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/27 18:40:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	int						id;
	pid_t					pid;
	int						must_eat;
	int						times_eaten;
	long					last_meal_time;
	struct s_program_data	*data;
}	t_philo;

typedef struct s_program_data
{
	const int		number_of_philosophers;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	const int		number_of_times_each_philosopher_must_eat;
	size_t			start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal_time;
	sem_t			*start;
	sem_t			*eat_count;
	t_philo			*philos;
}	t_program_data;

typedef struct s_params
{
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_params;

int				manual(void);
t_params		parse_arguments(int ac, char *av[]);
t_program_data	*init_data(int ac, char *av[]);
void			philosopher_routine(t_philo *philo);
void			print_died(t_program_data *data, int id, size_t start_time);
void			print_thinking(t_program_data *data, int id, size_t start_time);
void			print_sleeping(t_program_data *data, int id, size_t start_time);
void			print_eating(t_program_data *data, int id, size_t start_time);
void			print_fork(t_program_data *data, int id, size_t start_time);
size_t			get_current_time(void);
int				error_and_exit(char *msg, int error_code);
int				error_and_return(char *msg, int error_code);
void			free_resources(t_program_data *data);

#endif