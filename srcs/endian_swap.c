/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:52:17 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/11 17:05:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

q#include "nm.h"

unsigned int	endian_swap(unsigned int x)
{
	return ((x >> 24) | ((x >> 8) & 0x0000ff00)
	| ((x << 8) & 0x00ff0000) | (x << 24));
}

unsigned long	lendian_swap(unsigned long x)
{
	return ((x >> 56)
		| ((x >> 40) & 0x000000000000ff00)
		| ((x >> 24) & 0x0000000000ff0000)
		| ((x >> 8) & 0x00000000ff000000)
		| ((x << 8) & 0x000000ff00000000)
		| ((x << 24) & 0x0000ff0000000000)
		| ((x << 40) & 0x00ff000000000000)
		| (x << 56));
}

unsigned int	bed(unsigned int x, int flag)
{
	if (flag & FLAG_BIGEN)
		return (endian_swap(x));
	return (x);
}

unsigned long	lbed(unsigned long x, int flag)
{
	if (flag & FLAG_BIGEN)
		return (lendian_swap(x));
	return (x);
}
