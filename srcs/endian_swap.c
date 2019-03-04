/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:52:17 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/04 03:07:41 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	endian_swap(unsigned int x)
{
	return ((x >> 24) | ((x >> 8) & 0x0000ff00)
	| ((x << 8) & 0x00ff0000) | (x << 24));
}

void			*p_endian_swap_64(void *p)
{
	unsigned long int	swap;

	swap = (unsigned long int)p;
	swap = ((swap << 8) & 0xff00ff00ff00ff00ULL)
	| ((swap >> 8) & 0x00ff00ff00ff00ffULL);
	swap = ((swap << 16) & 0xffff0000ffff0000ULL)
	| ((swap >> 16) & 0x0000ffff0000ffffULL);
	swap = ((swap << 32))
	| ((swap >> 32) & 0xffffffffULL);
	p = (void *)swap;
	return (p);
}
