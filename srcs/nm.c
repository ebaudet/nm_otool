/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/27 22:16:16 by ebaudet          ###   ########.fr       */
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
#include "libft.h"

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		ft_putendl(stringtable + array[i].n_un.n_strx);
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
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
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
