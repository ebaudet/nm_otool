/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/11 17:04:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

#include <ar.h>

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

int				handle_type(char *ptr, char *av, int flag)
{
	unsigned int		magic_number;
	t_symtable			*list;
	int					size_print;
	// struct ar_hdr		*ar;

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
		// ft_printf("%33k<magic_number = %x>%k\n", magic_number);
		// ft_printf("[%.*s]\n[%s]\n", SARMAG, ptr, ARMAG);
		// if (!ft_strncmp((const char *)ptr, ARMAG, SARMAG))
		// {
		// 	ar = (struct ar_hdr *)(SARMAG * sizeof(char) + ptr);
		// 	ft_printf("{archinve: ar_name:%.16s, ar_date:%.12s, ar_uid:%.6s, ar_gid:%.6s, ar_mode:%.8s, ar_size: %.10s}\n",
		//         ar->ar_name, ar->ar_date, ar->ar_uid, ar->ar_gid, ar->ar_mode);
		// }
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
			if (handle_type(ptr, av[i], flag) == 0)
				file_error("The file was not recognized as a valid object file\n", av[i], av[0]);
			if (munmap(ptr, buf.st_size) < 0)
				return (file_error("Error munmap.", av[i], av[0]));
			close(fd);
		}
	}
	return (EXIT_SUCCESS);
}
