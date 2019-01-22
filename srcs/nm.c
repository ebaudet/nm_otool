/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/01/22 22:38:17 by ebaudet          ###   ########.fr       */
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

void	print_output(struct symtab_command *sym, int nsyms, char *ptr)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;
	struct segment_command_64	*segment;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	segment = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < nsyms)
	{
		if (!array[i].n_value) {
			ft_putstr("                ");
		} else {
			ft_puthex((unsigned long)array[i].n_value, 16);
		}
		ft_putstr("|");
		ft_putchar(type(segment[i].segname, array[i].n_type, array[i].n_value, array[i].n_sect));
		ft_putstr("|");
		ft_puthex((unsigned long)array[i].n_sect, 3);
		ft_putstr("|");
		ft_puthex((unsigned long)array[i].n_type, 3);
		ft_putstr("|");
		ft_puthex((unsigned long)array[i].n_desc, 3);
		ft_putstr("|");
		ft_putstr(stringtable+array[i].n_un.n_strx);
		ft_putendl("");
		// ft_putendl(stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void	handle_64(char *ptr)
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
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym, sym->nsyms, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void	nm(char *ptr)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
	// @TODO: gérer ici les fat binaries
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
