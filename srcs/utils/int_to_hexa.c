/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 15:17:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 01:54:21 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	eb_puthexa(int nbr)
{
	if (nbr >= 0 && nbr <= 9)
		ft_putchar('0' + nbr);
	else if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nbr);
	}
}
