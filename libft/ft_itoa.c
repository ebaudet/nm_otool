/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:41:30 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/04 18:57:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_nbchar(int n)
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

static char		*ft_invnb(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(12 * sizeof(char));
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

char			*ft_itoa(int n)
{
	char	*str;
	char	*strinv;
	int		i;
	int		j;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	str = (char *)malloc(ft_nbchar(n) * sizeof(char));
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
