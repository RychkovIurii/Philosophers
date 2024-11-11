/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:40:37 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 18:05:06 by irychkov         ###   ########.fr       */
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

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		return (0);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

int	converter(const char *str)
{
	long long int	check;
	long long int	result;
	int				i;

	result = 0;
	i = is_valid(str);

	while (i && (str[i] >= '0' && str[i] <= '9'))
	{
		check = result * 10 + sign * (str[i] - '0');
		if (check / 10 != result)
			return (0);
		result = check;
		i++;
	}
	return (result);
}
