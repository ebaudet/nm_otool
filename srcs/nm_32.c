/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:55:29 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 04:40:21 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

t_symtable *add_symtable_32(struct nlist array, struct section *section,
                            char *stringtable, t_symtable **list, int flag)
{
	t_symtable	*new;
	char		*offset;

	if (!array.n_value)
			offset = ft_strdup("                ");
	else
		offset = ft_gethex((unsigned long)array.n_value, 8);
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
	else
		list_add_order_symtable(list, new, compare_tableindex);
	return (new);
}

struct section	*get_section_32(struct segment_command *segment,
                               uint32_t offset)
{
	struct section	*section;

	if (offset <= segment->nsects)
	{
		section = (struct section *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section_32((struct segment_command *)((void *)segment +
		segment->cmdsize), offset - segment->nsects));
}

void	get_symtable_32(struct symtab_command *sym, int nsyms, char *ptr,
                  t_symtable **list, int flag)
{
	int							i;
	char						*stringtable;
	struct nlist				*array;
	struct segment_command	*segment;
	struct section			*section;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	segment = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	while (i < nsyms)
	{
		section = get_section_32(segment, array[i].n_sect);
		if ((array[i].n_type & N_STAB) == 0)
			add_symtable_32(array[i], section, stringtable, list, flag);
		i++;
	}
}

void	handle_32(char *ptr, t_symtable **list, int flag)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
// 	ft_printf("{HEADER: magic:%x, cputype:%d, cpusubtype:%d, filetype:%d, ncmds:%d, sizeofcmds:%d, flags:%d}\n",
// 	 header->magic, header->cputype,
// header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
// header->flags);
	while (i < ncmds)
	{
		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_32(sym, sym->nsyms, ptr, list, flag);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
