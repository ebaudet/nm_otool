/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:55:29 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 19:08:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

t_symtable		*add_symtable_32(struct nlist array, struct section *section,
				char *stringtable, t_nm *nm)
{
	t_symtable	*new;
	char		*offset;
	char		symbol;

	if (nm->flag & FLAG_PPC)
		symbol = get_symbol(section->sectname, array.n_type,
			array.n_value, array.n_sect);
	else
		symbol = get_symbol(section->sectname, bed(array.n_type, nm->flag),
			lbed(array.n_value, nm->flag), bed(array.n_sect, nm->flag));
	if (!array.n_value)
		offset = ft_strchr("uUi", symbol)
			? ft_strdup("        ")
			: ft_strdup("00000000");
	else
		offset = ft_strchr("i", symbol)
			? ft_strdup("        ")
			: ft_gethex((unsigned long)bed(array.n_value, nm->flag), 8);
	new = new_symtable(offset, symbol, stringtable + bed(array.n_un.n_strx,
		nm->flag));
	return (list_add(nm, new));
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

void			get_symtable_32(struct symtab_command *sym, int nsyms,
				char *ptr, t_nm *nm)
{
	int						i;
	char					*stringtable;
	struct nlist			*array;
	struct segment_command	*segment;
	struct section			*section;

	array = (void *)ptr + bed(sym->symoff, nm->flag);
	stringtable = (void *)ptr + bed(sym->stroff, nm->flag);
	segment = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	while (i < nsyms)
	{
		if (nm->flag & FLAG_PPC)
			section = get_section_32(segment, array[i].n_sect, nm->flag);
		else
			section = get_section_32(segment, bed(array[i].n_sect, nm->flag),
				nm->flag);
		if ((bed(array[i].n_type, nm->flag) & N_STAB) == 0)
			add_symtable_32(array[i], section, stringtable, nm);
		i++;
	}
}

int				handle_32(char *ptr, t_nm *nm)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header *)ptr;
	ncmds = bed(header->ncmds, nm->flag);
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (sec_ptr((char *)lc))
			return (ERROR_LC_PTR);
		if (bed(lc->cmd, nm->flag) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable_32(sym, bed(sym->nsyms, nm->flag), ptr, nm);
			break ;
		}
		lc = (void *)lc + bed(lc->cmdsize, nm->flag);
		i++;
	}
	return (8);
}
