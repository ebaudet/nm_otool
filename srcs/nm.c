/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/16 19:42:41 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "nm.h"
#include "math.h"
#include "libft.h"
#include "libftprintf.h"

static char	get_section_letter(char *section)
{
	char	c;

	c = '?';
	if (ft_strcmp(section, SECT_TEXT) == 0)
		c = 'T';
	else if (ft_strcmp(section, SECT_DATA) == 0)
		c = 'D';
	else if (ft_strcmp(section, SECT_BSS) == 0)
		c = 'B';
	else
		c = 'S';
	return (c);
}

static char	undef(int type, int addr, char c)
{
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			c = 'C';
		else
			c = 'U';
	}
	return (c);
}

char		type(char *section, int type, int addr, int sect)
{
	char	c;

	c = '?';
	if (!section)
		return ('U');
	c = undef(type, addr, c);
	if (c != '?')
		return (c);
	else if ((type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		c = 'U';
	else if ((type & N_TYPE) == N_SECT)
		c = get_section_letter(section);
	else if ((type & N_TYPE) == N_INDR)
		c = 'I';
	else if (sect == 0xb)
		c = 'S';
	else if ((type & N_STAB) != 0)
		c = 'T';
	if (!(type & N_EXT) && c != '?')
		c += 32;
	return (c);
}

struct section_64	*get_section(struct segment_command_64 *segment, uint32_t offset)
{
	struct section_64	*section;

	if (offset <= segment->nsects)
	{
		section = (struct section_64 *)&segment[1] + offset - 1;
		return (section);
	}
	return (get_section((struct segment_command_64 *)((void *)segment + segment->cmdsize), offset - segment->nsects));
}

/* old way :
void	print_output(struct symtab_command *sym, int nsyms, char *ptr)
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
		section = get_section(segment, array[i].n_sect);
		if (!array[i].n_value)
		{
			ft_putstr("                ");
		}
		else
		{
			ft_puthex((unsigned long)array[i].n_value, 16);
		}
		ft_printf(" %c %s\n",
			type(section->sectname, array[i].n_type, array[i].n_value, array[i].n_sect),
			stringtable+array[i].n_un.n_strx
			);
		i++;
	}
}
*/

void	print_output(t_symtable **list)
{
	t_symtable	*tmp;

	tmp = *list;
	while (tmp)
	{
		ft_printf("%16s %c %s\n", tmp->offset, tmp->symbol, tmp->table_index);
		tmp = tmp->next;
	}
}

void	get_symtable(struct symtab_command *sym, int nsyms, char *ptr,
                  t_symtable **list)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;
	struct segment_command_64	*segment;
	struct section_64			*section;
	char						*offset;
	t_symtable					*new;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		ft_printf("%33k<syms %d/%d>%k\n", i, nsyms);
		section = get_section(segment, array[i].n_sect);
		if (!array[i].n_value)
			offset = ft_strdup("                ");
		else
			offset = ft_gethex((unsigned long)array[i].n_value, 16);
		ft_printf("%34k->%k {in get_symtable: offset[%16s] symbol[%c] table_index[%s]}\n",
		          offset,
		          type(section->sectname, array[i].n_type, array[i].n_value, array[i].n_sect),
		          stringtable+array[i].n_un.n_strx);
		new = new_symtable(offset, type(section->sectname, array[i].n_type,
			array[i].n_value, array[i].n_sect),
			stringtable+array[i].n_un.n_strx);
		ft_printf("   {new: offset[%16s] symbol[%c] table_index[%s]}\n", new->offset, new->symbol, new->table_index);
		// list_add_last_symtable(list, offset, type(section->sectname, array[i].n_type,
		// 	array[i].n_value, array[i].n_sect), stringtable+array[i].n_un.n_strx);
		list_add_order_symtable(list, new, compare_tableindex);
		ft_printf("   {list add %32kOK%k}\n");
		i++;
	}
}

void	handle_64(char *ptr, t_symtable **list)
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
	while (i < ncmds)
	{
		ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_symtable(sym, sym->nsyms, ptr, list);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void	nm(char *ptr)
{
	unsigned int		magic_number;
	t_symtable			*list;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		ft_printf("%33k<call print_output>%k\n");
		handle_64(ptr, &list);
		ft_printf("%33k<end print_output>%k\n");
	}
	// @TODO: gérer ici les fat binaries
	ft_printf("%33k<call print_output>%k\n");
	print_output(&list);
	ft_printf("%33k<end print_output>%k\n");
	ft_printf("%33k<call free_symtable>%k\n");
	free_symtable(&list);
	ft_printf("%33k<end free_symtable>%k\n");
}

int		main(int ac, char **av)
{
	int				fd;
	struct stat		buf;
	char			*ptr;

	if (ac != 2)
		return (print_error("Please give me an arg"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (file_error("Can't open ", av[1]));
	if (fstat(fd, &buf) < 0)
		return (file_error("Error fstat : ", av[1]));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (file_error("Error mmap : ", av[1]));
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (file_error("Error munmap : ", av[1]));
	close(fd);
	return (EXIT_SUCCESS);
}
