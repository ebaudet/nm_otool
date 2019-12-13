/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/13 21:09:48 by ebaudet          ###   ########.fr       */
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

	if ((sec_ptr((char *)section) || sec_ptr((char *)stringtable))
		&& (nm->error = 1))
		return (NULL);
	symbol = get_symbol(section->sectname, bed(array.n_type, nm->flag),
		lbed(array.n_value, nm->flag), bed(array.n_sect, nm->flag));
	if (!array.n_value)
		offset = ft_strchr("uUi", symbol)
			? ft_strdup("                ")
			: ft_strdup("0000000000000000");
	else
		offset = ft_strchr("i", symbol)
			? ft_strdup("                ")
			: ft_gethex((unsigned long)lbed(array.n_value, nm->flag), 16);
	new = new_symtable(offset, symbol, stringtable + bed(array.n_un.n_strx,
		nm->flag));
	if ((!new || sec_ptr(new->table_index)) && (nm->error = 1))
		return (NULL);
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

int					get_symtable_64(struct symtab_command *sym, int nsyms,
					char *ptr, t_nm *nm)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;
	struct segment_command_64	*segment;
	struct section_64			*section;

	if (sec_nm((char *)ptr, nm))
		return (EXIT_FAILURE);
	array = (void *)ptr + bed(sym->symoff, nm->flag);
	stringtable = (void *)ptr + bed(sym->stroff, nm->flag);
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		if (sec_nm((char *)segment, nm))
			return (EXIT_FAILURE);
		section = get_section_64(segment, bed(array[i].n_sect, nm->flag),
			nm->flag);
		if ((bed(array[i].n_type, nm->flag) & N_STAB) == 0)
			if (add_symtable_64(array[i], section, stringtable, nm) == NULL)
				return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
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
		if (sec_ptr((char *)lc))
			return (ERROR_LC_PTR);
		if (bed(lc->cmd, nm->flag) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (get_symtable_64(sym, bed(sym->nsyms, nm->flag), ptr, nm))
				return (ERROR_NM);
			break ;
		}
		lc = (void *)lc + bed(lc->cmdsize, nm->flag);
		i++;
	}
	return (16);
}
