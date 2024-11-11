/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:40:37 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/11 19:30:50 by irychkov         ###   ########.fr       */
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

int	converter(char *str)
{
	long long int	check;
	long long int	result;
	int				i;
	int				len;

	result = 0;
	i = 0;
	len = is_valid_num(str);
	while (i <= len && (str[i] >= '0' && str[i] <= '9'))
	{
		check = result * 10 + (str[i] - '0');
		if (check / 10 != result)
			return (0);
		result = check;
		i++;
	}
	return (result);
}
