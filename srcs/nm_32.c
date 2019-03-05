/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:55:29 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/05 21:50:51 by ebaudet          ###   ########.fr       */
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
		offset = ft_gethex((unsigned long)bed(array.n_value, flag), 8);
	// ft_printf("{add_symtable_32: array: %p, section: %p, stringtable: %p}\n",
	//          &array, section, stringtable);
	// ft_printf("{%32kget_symbol: sectname:%p|%p, n_type:%x, n_value:%x, n_sect:%x%k}",
	//           section->sectname ,section->sectname,  bed(array.n_type, flag), bed(array.n_value, flag), bed(array.n_sect, flag));
	new = new_symtable(offset, get_symbol(section->sectname,
		bed(array.n_type, flag), bed(array.n_value, flag),
		bed(array.n_sect, flag)), stringtable+bed(array.n_un.n_strx, flag));
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
                               uint32_t offset, int flag)
{
	struct section	*section;

	if (offset <= bed(segment->nsects, flag))
	{
		section = (struct section *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section_32((struct segment_command *)((void *)segment +
		bed(segment->cmdsize, flag)), offset - bed(segment->nsects, flag),
		flag));
}

void	get_symtable_32(struct symtab_command *sym, int nsyms, char *ptr,
                  t_symtable **list, int flag)
{
	int						i;
	char					*stringtable;
	struct nlist			*array;
	struct segment_command	*segment;
	struct section			*section;

	array = (void *)ptr + bed(sym->symoff, flag);
	stringtable = (void *)ptr + bed(sym->stroff, flag);
	segment = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	while (i < nsyms)
	{
		section = get_section_32(segment, bed(array[i].n_sect, flag), flag);
		if ((bed(array[i].n_type, flag) & N_STAB) == 0)
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
	ncmds = bed(header->ncmds, flag);
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	// ft_printf("%33k[%s]%k", (flag & FLAG_BIGEN) ? "is big-endian" : "is litle-endian");
	// ft_printf("{HEADER: magic:%x, cputype:%x, cpusubtype:%x, filetype:%x, ncmds:%x, sizeofcmds:%x, flags:%x}\n",
	// bed(header->magic, flag), bed(header->cputype, flag),
	// bed(header->cpusubtype, flag), bed(header->filetype, flag), bed(header->ncmds, flag), bed(header->sizeofcmds, flag),
	// header->flags);
	// ft_printf("{HEADER: magic:%x, cputype:%x, cpusubtype:%x, filetype:%x, ncmds:%x, sizeofcmds:%x, flags:%x}\n",
	// header->magic, header->cputype,
	// header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
	// header->flags);
	while (i < ncmds)
	{
		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (bed(lc->cmd, flag) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_32(sym, bed(sym->nsyms, flag), ptr, list, flag);
			break ;
		}
		lc = (void *)lc + bed(lc->cmdsize, flag);
		i++;
	}
}
