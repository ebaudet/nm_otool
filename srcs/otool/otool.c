/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 04:01:00 by ebaudet          ###   ########.fr       */
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

size_t	sizeof_mach_header(e_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

size_t	sizeof_segment_command(e_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct segment_command));
	return (sizeof(struct segment_command_64));
}

size_t	sizeof_section(e_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct section));
	return (sizeof(struct section_64));
}

uint32_t	get_segment_command_nsects(char *ptr, e_arch arch)
{
	if (arch == E_32B)
		return (((struct segment_command *)ptr)->nsects);
	return (((struct segment_command_64 *)ptr)->nsects);
}

void	loop_lc_segment(t_otool *otool, char *addr)
{
	struct segment_command		*sc;
	struct section				*section;
	unsigned int				k;

	sc = (struct segment_command *)addr;
	if (ft_strcmp(sc->segname, "__TEXT") == 0)
	{
		k = 0;
		addr += sizeof_segment_command(otool->arch);
		section = (struct section *)addr;
		while (k < get_segment_command_nsects((char *)sc, otool->arch))
		{
			section = (struct section *)addr;
			addr += sizeof_section(otool->arch);
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
		if (magic == FAT_CIGAM)
			otool->endian = E_BIG;
		return (0);
	}
	return (1);
}

unsigned int obed(unsigned int val, t_otool *otool)
{
	int flag;

	flag = (otool->endian == E_BIG) ? FLAG_BIGEN : 0;
	return (bed(val, flag));
}

int		ot_binary_handler(t_otool *otool)
{
	struct mach_header	*mh;
	struct load_command	*lc;
	char				*addr;
	unsigned int		i;

	ft_printf_fd(2, "%34kfile is '%s'%k\n", otool->file);

	mh = (struct mach_header *)otool->ptr;
	if (!set_arch(otool, mh->magic))
		return (-1);
	addr = otool->ptr + sizeof_mach_header(otool->arch);
	i = 0;
	while (i < obed(mh->ncmds, otool))
	{
		lc = (struct load_command *)addr;
		if (obed(lc->cmd, otool) == otool->segment)
			loop_lc_segment(otool, addr);
		addr = (char *)lc + obed(lc->cmdsize, otool);
		i++;
	}
	return (0);
}

int		ot_flag(t_otool *o)
{
	int	flag;

	flag = 0;
	flag |= (o->endian == E_BIG) ? FLAG_BIGEN : flag;
	o->flag = flag;
	return (flag);
}

char		*ot_put_achitecture_name(t_otool *o, cpu_type_t cputype,
			cpu_subtype_t cpusubtype, int my_arch)
{
	int		i;

	if (my_arch)
		return ("");
	if (o->nfat_arch > 1)
		ft_printf("\n%s (for architecture ", o->file);
	else
		ft_printf("%s:\n", o->file);
	i = -1;
	while (g_infos[++i].name != NULL)
	{
		if (g_infos[i].cputype == cputype
			&& g_infos[i].cpusubtype == cpusubtype)
		{
			o->flag = (!ft_strcmp(g_infos[i].name, "ppc"))
				? o->flag | FLAG_PPC
				: o->flag & ~FLAG_PPC;
			if (o->nfat_arch > 1)
				ft_putstr(g_infos[i].name);
			break ;
		}
	}
	if (o->nfat_arch > 1)
		ft_putendl("):");
	return (g_infos[i].name);
}

int		ot_fat_handler(t_otool *o)
{
	struct fat_header		*fheader;
	struct fat_arch			*farch;
	unsigned int			i;
	int						my_arch;

	fheader = (struct fat_header *)o->ptr;
	i = 0;
	farch = (struct fat_arch *)(fheader + 1);
	my_arch = is_my_arch(fheader, farch, o->flag);
	o->nfat_arch = bed(fheader->nfat_arch, o->flag);
	while (++i <= o->nfat_arch)
	{
		if (my_arch && !is_my_arch_current(farch, o->flag) && farch++)
			continue ;
		ot_put_achitecture_name(o, bed(farch->cputype, o->flag),
			bed(farch->cpusubtype, o->flag), my_arch);
		o->flag &= ~FLAG_PRINT;
		o->ptr += bed(farch->offset, o->flag);
		ot_binary_handler(o);
		o->flag &= ~FLAG_PPC;
		farch++;
	}
	return (0);
}

int		ot_type_handler(t_otool *otool)
{
	unsigned int		magic;

	magic = *(unsigned int *)otool->ptr;
	if (set_arch(otool, magic))
		return (ot_binary_handler(otool));
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		ot_flag(otool);
		return (ot_fat_handler(otool));
	}
	return (-1);
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
	if (ot_type_handler(&otool) == -1)
		ft_printf("%s: is not an object file\n", file);
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
