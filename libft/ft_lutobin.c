/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutobin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 20:45:55 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/05 17:16:14 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_lutobin(uintmax_t lu)
{
	char		bin_number[256];
	uintmax_t	temp;
	int			i;

	ft_memset(bin_number, 0, 256);
	i = 0;
	if (lu == 0)
		bin_number[i++] = 0 + '0';
	while (lu != 0)
	{
		temp = lu % 2;
		temp += '0';
		bin_number[i++] = temp;
		lu = lu / 2;
	}
	ft_strreverse(bin_number);
	return (ft_strdup(bin_number));
}
