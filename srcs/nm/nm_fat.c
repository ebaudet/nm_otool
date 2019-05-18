/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 03:37:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "utils.h"
#include "libft.h"
#include "libftprintf.h"

char		*put_achitecture_name(t_nm *nm, cpu_type_t cputype,
			cpu_subtype_t cpusubtype, int my_arch)
{
	int		i;

	if (my_arch)
		return ("");
	if (nm->nfat_arch > 1)
		ft_printf("\n%s (for architecture ", nm->file);
	else
		ft_printf("%s:\n", nm->file);
	i = -1;
	while (g_infos[++i].name != NULL)
	{
		if (g_infos[i].cputype == cputype
			&& g_infos[i].cpusubtype == cpusubtype)
		{
			nm->flag = (!ft_strcmp(g_infos[i].name, "ppc"))
				? nm->flag | FLAG_PPC
				: nm->flag & ~FLAG_PPC;
			if (nm->nfat_arch > 1)
				ft_putstr(g_infos[i].name);
			break ;
		}
	}
	if (nm->nfat_arch > 1)
		ft_putendl("):");
	return (g_infos[i].name);
}

int			handle_fat(t_nm *nm, char *ptr)
{
	struct fat_header		*fheader;
	struct fat_arch			*farch;
	unsigned int			i;
	int						my_arch;

	nm->flag |= FLAG_BIGEN;
	fheader = (struct fat_header *)ptr;
	i = 0;
	farch = (struct fat_arch *)(fheader + 1);
	my_arch = is_my_arch(fheader, farch, nm->flag);
	nm->nfat_arch = bed(fheader->nfat_arch, nm->flag);
	while (++i <= nm->nfat_arch)
	{
		nm->flag |= FLAG_BIGEN;
		if (my_arch && !is_my_arch_current(farch, nm->flag) && farch++)
			continue ;
		put_achitecture_name(nm, bed(farch->cputype, nm->flag),
			bed(farch->cpusubtype, nm->flag), my_arch);
		nm->flag &= ~FLAG_PRINT;
		handle_type(nm, (char *)ptr + bed(farch->offset, nm->flag), NULL);
		nm->flag &= ~FLAG_PPC;
		farch++;
	}
	return (0);
}
