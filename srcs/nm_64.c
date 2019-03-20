/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/20 18:40:23 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

struct section_64	*get_section_64(struct segment_command_64 *segment,
	uint32_t offset, int flag)
{
	struct section_64	*section;

	if (offset <= bed(segment->nsects, flag))
	{
		section = (struct section_64 *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section_64((struct segment_command_64 *)((void *)segment
		+ bed(segment->cmdsize, flag)), offset - bed(segment->nsects, flag),
		flag));
}

t_symtable *add_symtable_64(struct nlist_64 array, struct section_64 *section,
	char *stringtable, t_symtable **list, int flag)
{
	t_symtable	*new;
	char		*offset;
	char		symbol;

	symbol = get_symbol(section->sectname, bed(array.n_type, flag),
		lbed(array.n_value, flag), bed(array.n_sect, flag));
	if (!array.n_value)
	{
		if (ft_strchr("uU", symbol))
			offset = ft_strdup("                ");
		else
			offset = ft_strdup("0000000000000000");
	}
	else
		offset = ft_gethex((unsigned long)lbed(array.n_value, flag), 16);
	new = new_symtable(offset, symbol, stringtable+bed(array.n_un.n_strx, flag));
	if (new == NULL)
		return (NULL);
	if (flag & FLAG_P)
		list_add_order_symtable(list, new, compare_end);
	else if (flag & FLAG_PCAPS)
		list_add_order_symtable(list, new, compare_first);
	else if (flag & FLAG_R)
		list_add_order_symtable(list, new, compare_tableindex_rev);
	else if (flag & FLAG_N)
		list_add_order_symtable(list, new, compare_offset);
	else
		list_add_order_symtable(list, new, compare_tableindex);
	return (new);
}

void	get_symtable_64(struct symtab_command *sym, int nsyms, char *ptr,
                  t_symtable **list, int flag)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;
	struct segment_command_64	*segment;
	struct section_64			*section;

	array = (void *)ptr + bed(sym->symoff, flag);
	stringtable = (void *)ptr + bed(sym->stroff, flag);
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		// ft_printf("%33k<syms %d/%d>%k\n", i, nsyms);
		section = get_section_64(segment, bed(array[i].n_sect, flag), flag);
		if ((bed(array[i].n_type, flag) & N_STAB) == 0)
			add_symtable_64(array[i], section, stringtable, list, flag);
		i++;
	}
}

int		handle_64(char *ptr, t_symtable **list, int flag)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = bed(header->ncmds, flag);
	i = 0;
	lc = (void *)ptr + sizeof(*header);
// 	ft_printf("{HEADER: magic:%x, cputype:%d, cpusubtype:%d, filetype:%d, ncmds:%d, sizeofcmds:%d, flags:%d, reserved:%d}\n",
// 	 header->magic, header->cputype,
// header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
// header->flags, header->reserved);
	while (i < ncmds)
	{
		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (bed(lc->cmd, flag) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_64(sym, bed(sym->nsyms, flag), ptr, list, flag);
			break ;
		}
		lc = (void *)lc + bed(lc->cmdsize, flag);
		i++;
	}
	return (16);
}