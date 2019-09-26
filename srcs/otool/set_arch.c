/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:35:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:53:15 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		set_arch(t_otool *otool, uint32_t magic)
{
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		otool->endian = E_LITTLE;
		otool->arch = E_64B;
		otool->segment = LC_SEGMENT_64;
		if (magic == MH_CIGAM_64)
			otool->endian = E_BIG;
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		otool->endian = E_LITTLE;
		otool->arch = E_32B;
		otool->segment = LC_SEGMENT;
		if (magic == MH_CIGAM)
			otool->endian = E_BIG;
	}
	else
	{
		if (magic == FAT_CIGAM)
			otool->endian = E_BIG;
		return (0);
	}
	return (1);
}
