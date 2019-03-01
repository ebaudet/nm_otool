/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 05:17:49 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

unsigned int	bed(unsigned int x, int flag)
{
	if (flag & FLAG_BIGEN)
		return (endian_swap(x));
	return (x);
}

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

void			print_output(t_symtable **list, int size)
{
	t_symtable	*tmp;

	tmp = *list;
	while (tmp)
	{
		ft_printf("%.*s %c %s\n", size, tmp->offset, tmp->symbol,
			tmp->table_index);
		tmp = tmp->next;
	}
}

int				nm(char *ptr, char *av, int flag)
{
	unsigned int		magic_number;
	t_symtable			*list;

	list = NULL;
	magic_number = *(unsigned int *)ptr;
	flag &= ~FLAG_BIGEN;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		if (magic_number == MH_CIGAM_64)
			flag |= FLAG_BIGEN;
		handle_64(ptr, &list, flag);
		print_output(&list, 16);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		if (magic_number == MH_CIGAM)
			flag |= FLAG_BIGEN;
		handle_32(ptr, &list, flag);
		print_output(&list, 8);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		if (magic_number == FAT_CIGAM)
			flag |= FLAG_BIGEN;
		handle_fat(ptr, &list, av, flag);
	}
	else
	{
		ft_printf("%33k<magic_number = %x>%k\n", magic_number);
		return (0);
	}
	// ft_printf("%33k<call free_symtable>%k\n");
	free_symtable(&list);
	// ft_printf("%33k<end free_symtable>%k\n");
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
	while (++i < ac)
	{
		if (ac > 2)
			ft_printf("\n%s:\n", av[i]);
		if ((fd = open(av[i], O_RDONLY)) < 0)
			file_error("No such file or directory.", av[i], av[0]);
		else
		{
			if (fstat(fd, &buf) < 0)
				return (file_error("Error fstat.", av[i], av[0]));
			if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
				return (file_error("Error mmap.", av[i], av[0]));
			if (nm(ptr, av[i], flag) == 0)
				file_error("The file was not recognized as a valid object file", av[i], av[0]);
			if (munmap(ptr, buf.st_size) < 0)
				return (file_error("Error munmap.", av[i], av[0]));
			close(fd);
		}
	}

	return (EXIT_SUCCESS);
}
