/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:41:30 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/08 15:42:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_nbchar(intmax_t n)
{
	int		i;

	i = 0;
	while (n <= -10 || n >= 10)
	{
		n = n / 10;
		i++;
	}
	if (n < 0)
		return (i + 2);
	return (i + 1);
}

static char		*ft_invnb(intmax_t n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)ft_memalloc(20 * sizeof(char));
	if (n == 0)
		str[i++] = '0';
	while (n)
	{
		str[i++] = (n % 10) + '0';
		n = n / 10;
	}
	str[i] = 0;
	return (str);
}

char			*ft_itoa(intmax_t n)
{
	char	*str;
	char	*strinv;
	int		i;
	int		j;

	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	i = 0;
	str = (char *)ft_memalloc((ft_nbchar(n) + 1) * sizeof(char));
	if (n < 0)
	{
		str[i++] = '-';
		n = (-1) * n;
	}
	strinv = ft_invnb(n);
	j = ft_strlen(strinv);
	while (j > 0)
		str[i++] = strinv[--j];
	str[i] = 0;
	free(strinv);
	return (str);
}
