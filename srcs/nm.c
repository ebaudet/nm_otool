/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 02:56:25 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

char	get_section_letter(char *section)
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

char	undef(int type, int addr, char c)
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

char	get_symbol(char *section, int type, int addr, int sect)
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

void	print_output(t_symtable **list, int size)
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

int		nm(char *ptr, char *av)
{
	unsigned int		magic_number;
	t_symtable			*list;

	list = NULL;
	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		ft_printf("%33k<call handle_64>%k\n");
		// ft_printf("type: N_STAB[%b], N_PEXT[%b], N_TYPE[%b], N_EXT[%b], N_UNDF[%b], N_ABS[%b], N_SECT[%b], N_PBUD[%b], N_INDR[%b] \n", N_STAB, N_PEXT, N_TYPE, N_EXT, N_UNDF, N_ABS, N_SECT, N_PBUD, N_INDR);
		handle_64(ptr, &list);
		ft_printf("%33k<end handle_64>%k\n");
		ft_printf("%33k<call print_output>%k\n");
		print_output(&list, 16);
		ft_printf("%33k<end print_output>%k\n");

	}
	else if (magic_number == MH_MAGIC)
	{
		ft_printf("%33k<call handle_32>%k\n");
		handle_32(ptr, &list);
		ft_printf("%33k<end handle_32>%k\n");
		ft_printf("%33k<call print_output>%k\n");
		print_output(&list, 8);
		ft_printf("%33k<end print_output>%k\n");

	}
	else if (magic_number == FAT_CIGAM)
	{
		// @TODO: gérer ici les fat binaries
		ft_printf("%33k<magic_number = %x | FAT_CIGAM>%k\n", magic_number);
		ft_printf("%36k~Todo: handle FAT_CIGAM binaries~%k\n", magic_number);
		handle_fat(ptr, &list, av);
		// print_output(&list, 16);
		// return (1);
	}
	else
	{
		ft_printf("%33k<magic_number = %x>%k\n", magic_number);
		return (0);
	}
	ft_printf("%33k<call free_symtable>%k\n");
	free_symtable(&list);
	ft_printf("%33k<end free_symtable>%k\n");
	return (1);
}

int		main(int ac, char **av)
{
	int				fd;
	struct stat		buf;
	char			*ptr;
	int				i;

	// (void)ac;
	// (void)av;
	// ft_printf("%0.8x %0.8x %0.8x %0.8x\n", 0x00, 0x10 & 0x01, 0x10 & ~0x01, 0x1111 & ~0x0010);
	// ft_printf("%0.8x %0.8x %0.8x %0.8x\n", 0x00, 0x0010 | 0x1001, 0x10 | ~0x01, 0x11 | ~0x01);
	// return (1);

	if (ac < 2)
	{
		ft_printf_fd(2, "There are %d args given to the function\n", ac);
		return (print_error("Please give me an arg"));
	}
	i = 0;
	while (++i < ac)
	{
		if (ac > 2)
			ft_printf("%s:\n", av[i]);
		if ((fd = open(av[i], O_RDONLY)) < 0)
			 file_error("No such file or directory.", av[i], av[0]);
		else
		{
			if (fstat(fd, &buf) < 0)
				return (file_error("Error fstat.", av[i], av[0]));
			if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
				return (file_error("Error mmap.", av[i], av[0]));
			if (nm(ptr, av[i]) == 0)
				file_error("The file was not recognized as a valid object file", av[i], av[0]);
			if (munmap(ptr, buf.st_size) < 0)
				return (file_error("Error munmap.", av[i], av[0]));
			close(fd);
		}
	}

	return (EXIT_SUCCESS);
}
