/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:51:00 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_pow10(unsigned int y)
{
	double result;

	result = 1;
	while (y >= 1)
	{
		result *= 10;
		y--;
	}
	return (result);
}

static double	ft_atod_decimals(const char *str, double value, int sign)
{
	unsigned int	i;

	if (*str == '.')
	{
		(str)++;
		i = 1;
		while (ft_isdigit(*str))
		{
			value += (double)(*str - '0') / ft_pow10(i++);
			str++;
		}
	}
	str += 2;
	return (value * sign);
}

double			ft_atod(const char *str)
{
	double			value;
	int				sign;

	value = 0;
	sign = (*str == '-') ? -1 : 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	return (ft_atod_decimals(str, value, sign));
}
