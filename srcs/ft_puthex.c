/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:50:52 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/24 19:53:21 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

void	ft_puthex(long long int nb, int width)
{
	char			val[width + 1];
	int				i;
	long long int	tmp;

	i = width;
	while (--i >= 0)
	{
		tmp = nb / ft_pow(16, i);
		nb -= tmp * ft_pow(16, i);
		tmp = (tmp < 10 ? tmp + '0' : tmp - 10 + 'a');
		val[width - (i + 1)] = tmp;
	}
	val[width] = '\0';
	ft_putstr(val);
}
