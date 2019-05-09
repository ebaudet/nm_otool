/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:41:20 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/09 23:04:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

char	*ft_gethex(long long int nb, int width)
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
	return (ft_strdup(val));
}
