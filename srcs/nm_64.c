/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/06 20:37:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

struct section_64	*get_section_64(struct segment_command_64 *segment, uint32_t offset)
{
	struct section_64	*section;

	if (offset <= segment->nsects)
	{
		section = (struct section_64 *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section_64((struct segment_command_64 *)((void *)segment + segment->cmdsize), offset - segment->nsects));
}

t_symtable *add_symtable_64(struct nlist_64 array, struct section_64 *section,
	char *stringtable, t_symtable **list, int flag)
{
	t_symtable	*new;
	char		*offset;

	if (!array.n_value)
			offset = ft_strdup("                ");
	else
		offset = ft_gethex((unsigned long)array.n_value, 16);
	new = new_symtable(offset, get_symbol(section->sectname, array.n_type,
		array.n_value, array.n_sect),
		stringtable+array.n_un.n_strx);
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

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		// ft_printf("%33k<syms %d/%d>%k\n", i, nsyms);
		section = get_section_64(segment, array[i].n_sect);
		if ((array[i].n_type & N_STAB) == 0)
			add_symtable_64(array[i], section, stringtable, list, flag);
		i++;
	}
}

void	handle_64(char *ptr, t_symtable **list, int flag)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	ft_printf("{HEADER: magic:%x, cputype:%d, cpusubtype:%d, filetype:%d, ncmds:%d, sizeofcmds:%d, flags:%d, reserved:%d}\n",
	 header->magic, header->cputype,
header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
header->flags, header->reserved);
	while (i < ncmds)
	{
		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_64(sym, sym->nsyms, ptr, list, flag);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}