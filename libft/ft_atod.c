/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/25 21:43:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double		ft_atod(const char *str)
{
	double	value;
	int		sign;
	int		i;

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
	if (*str == '.')
	{
		(str)++;
		i = 1;
		while (ft_isdigit(*str))
		{
			value += (double)(*str - '0') / pow(10, i++);
			str++;
		}
	}
	str += 2;
	return (value * sign);
}
