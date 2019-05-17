/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/17 21:18:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libftprintf.h"
#include "libft.h"
#include "utils.h"
#include "otool.h"

void	print_section_64(t_otool *otool, struct section_64 *section)
{
	unsigned int		j;

	ft_printf("%s:\nContents of (__TEXT,__text) section", otool->file);
	// ft_putstr(otool->file);
	// ft_putstr(":\nContents of (__TEXT,__text) section");
	j = 0;
	while (j < section->size)
	{
		if (!(j % 16))
		{
			ft_printf("\n%016x\t", section->addr + j);
			// ft_putchar('\n');
			// ft_puthex(section->addr + j, 16);
			// ft_putchar('\t');
		}
		ft_printf("%02x ", otool->ptr[section->offset + j] & 0xFF);
		// ft_puthex(otool->ptr[section->offset + j] & 0xFF, 2);
		// ft_putchar(' ');
		j++;
	}
	ft_putchar('\n');
}

void	print_section_32(t_otool *otool, struct section *section)
{
	unsigned int		j;

	ft_putstr(otool->file);
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
		ft_puthex(otool->ptr[section->offset + j] & 0xFF, 2);
		ft_putchar(' ');
		j++;
	}
	ft_putchar('\n');
}

void	print_section(t_otool *otool, char *section)
{
	if (otool->arch == E_32B)
		print_section_32(otool, (struct section *)section);
	if (otool->arch == E_64B)
		print_section_64(otool, (struct section_64 *)section);
}

size_t	sizeof_mach_header(t_otool *otool)
{
	if (otool->arch == E_32B)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

size_t	sizeof_segment_command(t_otool *otool)
{
	if (otool->arch == E_32B)
		return (sizeof(struct segment_command));
	return (sizeof(struct segment_command_64));
}

size_t	sizeof_section(t_otool *otool)
{
	if (otool->arch == E_32B)
		return (sizeof(struct section));
	return (sizeof(struct section_64));
}

void	loop_lc_segment(t_otool *otool, char *addr)
{
	struct segment_command_64	*sc;
	struct section				*section;
	unsigned int				k;

	sc = (struct segment_command_64 *)addr;
	if (ft_strcmp(sc->segname, "__TEXT") == 0)
	{
		k = 0;
		addr += sizeof_segment_command(otool);
		section = (struct section *)addr;
		while (k < sc->nsects)
		{
			section = (struct section *)addr;
			addr += sizeof_section(otool);
			if (ft_strcmp(section->sectname, "__text") == 0)
				print_section(otool, (char *)section);
			k++;
		}
	}
}

int		set_arch(t_otool *otool, uint32_t magic)
{
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		otool->endian = E_LITTLE;
		otool->arch = E_64B;
		otool->segment = LC_SEGMENT_64;
		if (magic == MH_CIGAM_64)
			otool->endian = E_BIG;
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		otool->endian = E_LITTLE;
		otool->arch = E_32B;
		otool->segment = LC_SEGMENT;
		if (magic == MH_CIGAM)
			otool->endian = E_BIG;
	}
	else
	{
		ft_printf_fd(2, "%35kmagic is %x%k\n", magic);
		return (0);
	}
	return (1);
}

unsigned int obed(t_otool *otool, unsigned int val)
{
	int flag;

	flag = (otool->endian == E_BIG) ? FLAG_BIGEN : 0;
	return (bed(val, flag));
}

int		ft_otool(t_otool *otool)
{
	struct mach_header	*mh;
	struct load_command	*lc;
	char				*addr;
	unsigned int		i;

	ft_printf_fd(2, "%34kfile is '%s'%k\n", otool->file);
	addr = otool->ptr + sizeof_mach_header(otool);
	mh = (struct mach_header *)otool->ptr;
	if (!set_arch(otool, mh->magic))
		return (-1);
	i = 0;
	while (i < obed(otool, mh->ncmds))
	{
		lc = (struct load_command *)addr;

		if (obed(otool, lc->cmdsize) == 0)
		{
			++i;
			continue ;
		}
		if (obed(otool, lc->cmdsize) == otool->segment)
			loop_lc_segment(otool, addr);
		addr = (char *)lc + obed(otool, lc->cmdsize);
		i++;
	}
	return (0);
}

int		treatment_file(char *file)
{
	int				fd;
	struct stat		buf;
	t_otool			otool;

	otool.file = file;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (file_error("Erreur d'ouverture du fichier ", file));
	if (fstat(fd, &buf) < 0)
		return (file_error("Erreur fstat du fichier ", file));
	if (S_ISDIR(buf.st_mode))
		return (file_error(": Is a directory", file));
	if ((otool.ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (file_error("Erreur mmap du fichier ", file));
	get_ptr(otool.ptr);
	get_size(buf.st_size);
	if (ft_otool(&otool) == -1)
	{
		file_error("not a mac header 64/32 bit ", file);
	}
	if (munmap(otool.ptr, buf.st_size) < 0)
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
