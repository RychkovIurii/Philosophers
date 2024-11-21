/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:40:37 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/15 15:11:44 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int argument)
{
	if (argument > 47 && argument < 58)
		return (1);
	else
		return (0);
}

static int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	converter(char *str)
{
	long long int	result;
	int				i;

	i = 0;
	result = 0;
	if (!is_valid_num(str))
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	return ((int)result);
}

static int	is_valid_data(t_params *params)
{
	if (params->philosophers < 1 || params->time_to_die < 1
		|| params->time_to_eat < 1 || params->time_to_sleep < 1)
		return (0);
	if (params->must_eat == 0)
		return (0);
	return (1);
}

t_params	parse_arguments(int ac, char *av[])
{
	t_params	params;

	params.philosophers = converter(av[1]);
	params.time_to_die = converter(av[2]);
	params.time_to_eat = converter(av[3]);
	params.time_to_sleep = converter(av[4]);
	if (ac == 6)
		params.must_eat = converter(av[5]);
	else
		params.must_eat = -1;
	if (!is_valid_data(&params))
	{
		manual();
		params.philosophers = -1;
	}
	return (params);
}
