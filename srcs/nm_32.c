/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:55:29 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/25 23:15:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

t_symtable *add_symtable_32(struct nlist array, struct section *section, char *stringtable, t_symtable **list)
{
	t_symtable	*new;
	char		*offset;

	if (!array.n_value)
			offset = ft_strdup("                ");
	else
		offset = ft_gethex((unsigned long)array.n_value, 8);
	ft_printf("%34k->%k {in get_symtable: offset[%16s] symbol[%c] table_index[%s]}\n",
	          offset,
	          get_symbol(section->sectname, array.n_type, array.n_value, array.n_sect),
	          stringtable+array.n_un.n_strx);
	new = new_symtable(offset, get_symbol(section->sectname, array.n_type,
		array.n_value, array.n_sect),
		stringtable+array.n_un.n_strx);
	if (new == NULL)
	{
		ft_printf("   {elememt list creation %31kERROR%k}\n");
		return (NULL);
	}
	// ft_printf("   {new: offset[%16s] symbol[%c] table_index[%s]}\n", new->offset, new->symbol, new->table_index);
	list_add_order_symtable(list, new, compare_end);
	// ft_printf("   {list add %32kOK%k}\n");
	return (new);
}

struct section	*get_section_32(struct segment_command *segment, uint32_t offset)
{
	struct section	*section;

	if (offset <= segment->nsects)
	{
		section = (struct section *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section_32((struct segment_command *)((void *)segment + segment->cmdsize), offset - segment->nsects));
}

void	get_symtable_32(struct symtab_command *sym, int nsyms, char *ptr,
                  t_symtable **list)
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
		// ft_printf("%33k<syms %d/%d>%k\n", i, nsyms);
		section = get_section_32(segment, array[i].n_sect);
		if ((array[i].n_type & N_STAB) == 0)
			add_symtable_32(array[i], section, stringtable, list);
		i++;
	}
}

void	handle_32(char *ptr, t_symtable **list)
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
	ft_printf("{HEADER: magic:%x, cputype:%d, cpusubtype:%d, filetype:%d, ncmds:%d, sizeofcmds:%d, flags:%d}\n",
	 header->magic, header->cputype,
header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
header->flags);
	while (i < ncmds)
	{
		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_32(sym, sym->nsyms, ptr, list);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
