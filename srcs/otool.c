/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/13 21:22:24 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <libft.h>
#include <libftprintf.h>
// #include "libft.h"
#include "math.h"
#include "otool.h"

void	print_section(char *av, struct section_64 *section, char *copy)
{
	unsigned int		j;

	ft_putstr(av);
	ft_putstr(":\nContents of (__TEXT,__text) section");
	j = 0;
	while (j < section->size)
	{
		if (!(j % 16))
		{
			ft_putchar('\n');
			ft_puthex(section->addr + j, 16);
			ft_putchar('\t');
		}
		ft_puthex(copy[section->offset + j] & 0xFF, 2);
		ft_putchar(' ');
		j++;
	}
	ft_putchar('\n');
}

void	loop_lc_segment_64(char *file, char *addr, char *copy)
{
	struct segment_command_64	*sc;
	struct section_64			*section;
	unsigned int				k;

	sc = (struct segment_command_64 *)addr;
	if (ft_strcmp(sc->segname, "__TEXT") == 0)
	{
		k = 0;
		addr += sizeof(struct segment_command_64);
		section = (struct section_64 *)addr;
		while (k < sc->nsects)
		{
			section = (struct section_64 *)addr;
			addr += sizeof(struct section_64);
			if (ft_strcmp(section->sectname, "__text") == 0)
				print_section(file, section, copy);
			k++;
		}
	}
}

int		ft_otool(char *file, char *addr)
{
	struct mach_header_64		*mh;
	struct load_command			*lc;
	unsigned int				i;
	char						*copy;

	copy = addr;
	mh = (struct mach_header_64 *)addr;
	addr += sizeof(struct mach_header_64);
	i = 0;
	if (mh->magic != MH_MAGIC_64)
		return (-1);
	while (i < mh->ncmds)
	{
		lc = (struct load_command *)addr;
		if (lc->cmdsize == 0)
		{
			i++;
			continue;
		}
		if (lc->cmd == LC_SEGMENT_64)
			loop_lc_segment_64(file, addr, copy);
		addr = (char *)lc + lc->cmdsize;
		i++;
	}
	return (0);
}

int		treatment_file(char *file)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (file_error("Erreur d'ouverture du fichier ", file));
	if (fstat(fd, &buf) < 0)
		return (file_error("Erreur fstat du fichier ", file));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (file_error("Erreur mmap du fichier ", file));
	if (ft_otool(file, ptr) == -1)
	{
		ft_putstr_fd("not a mac header 64\n", 2);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (file_error("Erreur munmap du fichier ", file));
	close(fd);
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int				i;

	i = 0;
	if (ac == 1)
		treatment_file("a.out");
	else
	{
		while (av[++i])
		{
			treatment_file(av[i]);
		}
	}
	return (EXIT_SUCCESS);
}
