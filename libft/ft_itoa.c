/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:41:30 by ebaudet           #+#    #+#             */
/*   Updated: 2019/01/14 15:48:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nbchar(int n)
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

char		*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_nbchar(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((str = (char *)malloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = (-1) * n;
	}
	str[size] = '\0';
	while (n > 9)
	{
		str[--size] = (n % 10) + '0';
		n = n / 10;
	}
	str[size - 1] = n + '0';
	return (str);
}
