/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_addr_endian.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:38:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:39:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

unsigned int	get_addr_endian(unsigned int addr, t_otool *otool)
{
	if (otool->flag & FLAG_PPC)
		return (obed(addr, otool));
	return (addr);
}
