/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_fat_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:33:30 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:52:10 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		ot_fat_handler(t_otool *o)
{
	struct fat_header		*fheader;
	struct fat_arch			*farch;
	unsigned int			i;
	int						my_arch;

	fheader = (struct fat_header *)o->ptr;
	i = 0;
	farch = (struct fat_arch *)(fheader + 1);
	my_arch = is_my_arch(fheader, farch, o->flag);
	o->nfat_arch = bed(fheader->nfat_arch, o->flag);
	while (++i <= o->nfat_arch)
	{
		if (my_arch && !is_my_arch_current(farch, o->flag) && farch++)
			continue ;
		ot_put_achitecture_name(o, bed(farch->cputype, o->flag),
			bed(farch->cpusubtype, o->flag), my_arch);
		o->flag &= ~FLAG_PRINT;
		o->ptr = o->ptr_file + bed(farch->offset, o->flag);
		ot_binary_handler(o);
		o->flag &= ~FLAG_PPC;
		farch++;
	}
	return (0);
}
