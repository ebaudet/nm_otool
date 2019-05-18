/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/30 10:52:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

t_symtable			*add_symtable_64(struct nlist_64 array,
					struct section_64 *section, char *stringtable, t_nm *nm)
{
	t_symtable	*new;
	char		*offset;
	char		symbol;

	symbol = get_symbol(section->sectname, bed(array.n_type, nm->flag),
		lbed(array.n_value, nm->flag), bed(array.n_sect, nm->flag));
	if (!array.n_value)
	{
		if (ft_strchr("uU", symbol))
			offset = ft_strdup("                ");
		else
			offset = ft_strdup("0000000000000000");
	}
	else
		offset = ft_gethex((unsigned long)lbed(array.n_value, nm->flag), 16);
	new = new_symtable(offset, symbol, stringtable + bed(array.n_un.n_strx,
		nm->flag));
	return (list_add(nm, new));
}

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

void				get_symtable_64(struct symtab_command *sym, int nsyms,
					char *ptr, t_nm *nm)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;
	struct segment_command_64	*segment;
	struct section_64			*section;

	array = (void *)ptr + bed(sym->symoff, nm->flag);
	stringtable = (void *)ptr + bed(sym->stroff, nm->flag);
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		section = get_section_64(segment, bed(array[i].n_sect, nm->flag),
			nm->flag);
		if ((bed(array[i].n_type, nm->flag) & N_STAB) == 0)
			add_symtable_64(array[i], section, stringtable, nm);
		i++;
	}
}

int					handle_64(char *ptr, t_nm *nm)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = bed(header->ncmds, nm->flag);
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (bed(lc->cmd, nm->flag) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_64(sym, bed(sym->nsyms, nm->flag), ptr, nm);
			break ;
		}
		lc = (void *)lc + bed(lc->cmdsize, nm->flag);
		i++;
	}
	return (16);
}
