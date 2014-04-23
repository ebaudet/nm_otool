/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/16 19:05:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_nb(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_op(char c)
{
	return (c == '-' || c == '+');
}

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f'
	|| c == '\v');
}

int			ft_atoi(const char *str)
{
	int		val;
	int		is_neg;
	int		i;

	val = 0;
	is_neg = 1;
	i = 0;
	while (ft_is_space(str[i]) && str[i] != 0)
		i++;
	if (!ft_is_nb(str[i]) && !ft_is_op(str[i]))
		return (0);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		is_neg = -1;
		i++;
	}
	while (ft_is_nb(str[i]))
	{
		val = (val * 10) + (str[i] - '0');
		i++;
	}
	return (val * is_neg);
}
