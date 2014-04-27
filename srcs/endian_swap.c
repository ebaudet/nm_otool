/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:52:17 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/27 20:53:00 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	endian_swap(unsigned int x)
{
	return ((x >> 24) | ((x >> 8) & 0x0000ff00)
	| ((x << 8) & 0x00ff0000) | (x << 24));
}
