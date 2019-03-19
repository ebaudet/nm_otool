/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/19 13:06:27 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

#include <ar.h>
#include <ranlib.h>

char			get_section_letter(char *section)
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

char			undef(int type, int addr, char c)
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

char			get_symbol(char *section, int type, int addr, int sect)
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

void			print_output(t_symtable **list, int size, char *av, int flag)
{
	t_symtable	*tmp;

	if (flag & FLAG_PRINT)
		ft_printf("\n%s:\n", av);
	tmp = *list;
	while (tmp)
	{
		ft_printf("%.*s %c %s\n", size, tmp->offset, tmp->symbol,
			tmp->table_index);
		tmp = tmp->next;
	}
}

void	handle_arch(char *base, char *ptr, int offset, char *av, int flag)
{
	int 			size;
	int				shift;
	char			*tmp;
	char 			*next;
	struct ar_hdr	*ar;
	(void)av;
	(void)flag;

	if (!ft_strncmp((const char *)ptr, SYMDEF_SORTED, 20) ||
		!ft_strncmp((const char *)ptr, SYMDEF, 20))
	{
		next = ptr + offset;
		ft_printf("-->%.*s<--\n", 20, ptr);
		ptr += 20;
		size = *((int *)ptr);
		ptr += sizeof(int);
		ft_printf(">%p<\n", ptr);
		ft_printf("%x\n", size);
		shift = -1;
		while ((++shift * sizeof(int)) < (unsigned long)size)
		{
			ft_printf("ptr-->symbol:%08x\tobject:%08x<--\n",
				bed(*(int *)(ptr + shift * sizeof(int)), flag),
				bed(*(int *)(ptr + (shift + 1) * sizeof(int)), flag));
			++shift;
			tmp = base + bed(*(int *)(ptr + (shift) * sizeof(int)), flag);
			ft_printf("[header:%32k%.60s%k type:%32k%-20s%k code_hexa:%31k", tmp, tmp + 60);
			for (int i = 0; i < 50; i++)
				ft_printf("%02hhx", tmp[i + 80]);
			ft_printf("%k %d %d]\n", ft_strlen(tmp + 60), 60 + ((ft_strlen(tmp + 60) + 1) / 10) * 10);
			handle_type(tmp + 72 + ((ft_strlen(tmp + 60) - 1) / 8) * 8, tmp + 60, flag);
		}
		tmp = base + bed(*(int *)(ptr + (shift) * sizeof(int)), flag);
		while (ft_strncmp(tmp, AR_EFMT1, ft_strlen(AR_EFMT1)))
		{
			ft_putchar('.');
			tmp++;
		}
		ft_printf("[header:%32k%.60s%k type:%32k%-20.20s%k\n", tmp, tmp + 60);
		handle_type(tmp + 72 + ((ft_strlen(tmp + 60) - 1) / 8) * 8, tmp + 60, flag);

		// If an argument is an archive, a listing for
       	// each  object  file  in the archive will be produced.
       	// => here are the objects files in the archive.
       	// /!\ But how to find the end ?
       	ft_printf("{original ptr:%p, size:%d, next: %p}\n", get_ptr(NULL), get_size(-1), next);
       	while (sec_ptr(next))
       	{
       		ft_printf("[header:%32k%.60s%k type:%32k%-20.20s%k\n", next, next + 60);
			handle_type(next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8, next + 60, flag);
			ar = (struct ar_hdr *)next;
			next += ft_atoi(ar->ar_size) + 60;
       	}
		// ft_printf("[header:%32k%.60s%k type:%32k%-20.20s%k\n", next, next + 60);
		// handle_type(next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8, next + 60, flag);
		// ar = (struct ar_hdr *)next;
		// next += ft_atoi(ar->ar_size) + 60;
		// ft_printf("[header:%32k%.60s%k type:%32k%-20.20s%k\n", next, next + 60);
		// handle_type(next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8, next + 60, flag);
		// ar = (struct ar_hdr *)next;
		// next += ft_atoi(ar->ar_size) + 60;
		// ft_printf("[header:%32k%.60s%k type:%32k%-20.20s%k\n", next, next + 60);
		// handle_type(next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8, next + 60, flag);
	}
}

/*

libft/libft.a(ft_concat.o):
                 U ___stack_chk_fail
                 U ___stack_chk_guard
                 U _free
0000000000000150 T _ft_concat
0000000000000000 T _ft_concat2
0000000000000080 T _ft_concat2c
0000000000000120 T _ft_concat2endl
00000000000003c0 T _ft_concatc
                 U _ft_memalloc
                 U _ft_strcat
                 U _ft_strcpy
                 U _ft_strdup
                 U _ft_strlen

ft_concat.o:
                 U ___stack_chk_fail
                 U ___stack_chk_guard
                 U _free
0000000000000150 T _ft_concat
                 T _ft_concat2 				<< error no print 0000000000000000
0000000000000080 T _ft_concat2c
0000000000000120 T _ft_concat2endl
00000000000003c0 T _ft_concatc
                 U _ft_memalloc
                 U _ft_strcat
                 U _ft_strcpy
                 U _ft_strdup
                 U _ft_strlen


ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive.o:
                 T _ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive
                 U _ft_memset

libft/libft.a(ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive.o):
0000000000000000 T _ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive
                 U _ft_memset
*/

int				handle_type(char *ptr, char *av, int flag)
{
	unsigned int		magic_number;
	t_symtable			*list;
	int					size_print;
	struct ar_hdr		*ar;

	list = NULL;
	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		size_print = handle_64(ptr, &list, (magic_number == MH_CIGAM_64) ?
			flag | FLAG_BIGEN : flag & ~FLAG_BIGEN);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		size_print = handle_32(ptr, &list, (magic_number == MH_CIGAM) ?
			flag | FLAG_BIGEN : flag & ~FLAG_BIGEN);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		size_print = handle_fat(ptr, av, (magic_number == FAT_CIGAM) ?
			flag | FLAG_BIGEN : flag & ~FLAG_BIGEN);
	else
	{
		ft_printf("%33k<magic_number = %x>%k\n", magic_number);
		ft_printf("[%.*s]\n[%s]\n", SARMAG, ptr, ARMAG);
		if (!ft_strncmp((const char *)ptr, ARMAG, SARMAG))
		{
			ar = (struct ar_hdr *)(SARMAG * sizeof(char) + ptr);
			ft_printf("{archinve: ar_name:%.16s, ar_date:%.12s, ar_uid:%.6s, ar_gid:%.6s, ar_mode:%.8s, ar_size: %.10s}\n",
		        ar->ar_name, ar->ar_date, ar->ar_uid, ar->ar_gid, ar->ar_mode, ar->ar_size);
			handle_arch(ptr, (char *)(ar + 1), ft_atoi(ar->ar_size), av, flag);
		}
		return (0);
	}
	if (size_print < 0)
		return (0);
	if (size_print > 0)
		print_output(&list, size_print, av, flag);
	free_symtable(&list);
	return (1);
}

int				main(int ac, char **av)
{
	int				fd;
	struct stat		buf;
	char			*ptr;
	int				i;
	int				flag;

	if (ac < 2)
	{
		ft_printf_fd(2, "There are %d args given to the function\n", ac);
		return (print_error("Please give me an arg"));
	}
	flag = 0;
	if ((i = nm_flag_handler(av, &flag)) < 0)
		return (EXIT_SUCCESS);
	flag = (ac - i > 0) ? flag | FLAG_PRINT : flag;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			file_error("No such file or directory.", av[i], av[0]);
		else
		{
			if (fstat(fd, &buf) < 0)
				return (file_error("Error fstat.", av[i], av[0]));
			if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
				return (file_error("Error mmap.", av[i], av[0]));
			get_ptr(ptr);
			get_size(buf.st_size);
			if (handle_type(ptr, av[i], flag) == 0)
				file_error("The file was not recognized as a valid object file\n", av[i], av[0]);
			if (munmap(ptr, buf.st_size) < 0)
				return (file_error("Error munmap.", av[i], av[0]));
			close(fd);
		}
	}
	return (EXIT_SUCCESS);
}
