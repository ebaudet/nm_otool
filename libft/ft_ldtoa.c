/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:19:33 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

/*
** The dtoa() function converts the initial portion of the string
** pointed to by <str> to int representation.
*/

static int	ft_log10(long double d)
{
	int	i;

	i = 1;
	if (d < 0)
		d *= -1.0;
	if (d <= 10.0)
		return (i);
	while (++i)
	{
		d = d / 10;
		if (d <= 10.0)
			break ;
	}
	return (i);
}

static int	ft_nbchar(long double d, unsigned int precision)
{
	int		i;

	i = 0;
	if (precision > 0)
		i = precision + 1;
	if (d < 0)
	{
		i++;
		d = ft_fabs(d);
	}
	i += ft_log10(d);
	return (i);
}

static void	put_decimals(long double d, unsigned int precision, char *str)
{
	char	*tmp;
	double	decimals;
	int		i;
	int		symbol;

	if (precision == 0)
		return ;
	symbol = 1;
	if (d < 0)
		symbol = -1;
	decimals = d - (int)d;
	decimals = ft_fabs(decimals);
	ft_strcat(str, ".");
	i = 0;
	while (++i <= (int)precision)
		decimals *= 10;
	decimals += 0.5;
	tmp = ft_itoa(decimals);
	ft_strncat(str, tmp, precision);
	free(tmp);
}

char		*ft_ldtoa(long double d, unsigned int precision)
{
	char	*str;
	char	*tmp;
	int		len;

	len = ft_nbchar(d, precision);
	str = ft_memalloc(len + 1);
	tmp = ft_itoa(d);
	str = ft_strncat(str, tmp, len - precision - 1);
	free(tmp);
	put_decimals(d, precision, str);
	return (str);
}
