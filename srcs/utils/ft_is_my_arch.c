/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_my_arch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 03:28:42 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 03:33:20 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <mach-o/fat.h>
#include <mach/machine.h>

int		is_my_arch_current(struct fat_arch *farch, int flag)
{
	if (bed(farch->cputype, flag) == CPU_TYPE_X86_64
		&& (bed(farch->cpusubtype, flag) == 0x80000003
			|| bed(farch->cpusubtype, flag) == CPU_SUBTYPE_X86_64_ALL))
		return (1);
	return (0);
}

int		is_my_arch(struct fat_header *fheader, struct fat_arch *farch, int flag)
{
	unsigned int	i;

	if (flag & FLAG_ARCH)
	{
		return (0);
	}
	i = 0;
	while (++i <= bed(fheader->nfat_arch, flag))
	{
		if (is_my_arch_current(farch, flag))
			return (1);
		farch++;
	}
	return (0);
}
