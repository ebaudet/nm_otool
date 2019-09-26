/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:34:22 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:52:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		ot_flag(t_otool *o)
{
	int	flag;

	flag = 0;
	flag |= (o->endian == E_BIG) ? FLAG_BIGEN : flag;
	o->flag = flag;
	return (flag);
}
