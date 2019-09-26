/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_put_achitecture_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:33:56 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:52:28 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

char		*ot_put_achitecture_name(t_otool *o, cpu_type_t cputype,
			cpu_subtype_t cpusubtype, int my_arch)
{
	int		i;

	if (!my_arch && o->nfat_arch > 1)
		ft_printf("%s (architecture ", o->file);
	else
		ft_printf("%s:\n", o->file);
	if (my_arch)
		return ("");
	i = -1;
	while (g_infos[++i].name != NULL)
	{
		if (g_infos[i].cputype == cputype
			&& g_infos[i].cpusubtype == cpusubtype)
		{
			o->flag = (!ft_strcmp(g_infos[i].name, "ppc"))
				? o->flag | FLAG_PPC
				: o->flag & ~FLAG_PPC;
			if (o->nfat_arch > 1)
				ft_putstr(g_infos[i].name);
			break ;
		}
	}
	if (o->nfat_arch > 1)
		ft_putendl("):");
	return (g_infos[i].name);
}
