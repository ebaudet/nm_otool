/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obed.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:38:05 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:51:53 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

unsigned int	obed(unsigned int val, t_otool *otool)
{
	int flag;

	flag = (otool->endian == E_BIG) ? FLAG_BIGEN : 0;
	return (bed(val, flag));
}
