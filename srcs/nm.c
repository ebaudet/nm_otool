/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/26 21:15:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

#include <ar.h>
#include <ranlib.h>

void			print_output(t_symtable **list, int size, char *file, char *object, int flag)
{
	t_symtable	*tmp;

	if (flag & FLAG_PRINT)
	{
		if (object != NULL)
			ft_printf("\n%s(%s):\n", file, object);
		else
			ft_printf("\n%s:\n", file);
	}
	tmp = *list;
	while (tmp)
	{
		ft_printf("%.*s %c %s\n", size, tmp->offset, tmp->symbol,
			tmp->table_index);
		tmp = tmp->next;
	}
}

void	handle_arch(t_nm *nm, char *ptr, int offset)
{

	char 			*next;
	struct ar_hdr	*ar;
	// (void)av;

	if (!ft_strncmp((const char *)ptr, SYMDEF_SORTED, 20) ||
		!ft_strncmp((const char *)ptr, SYMDEF, 20))
	{
		next = ptr + offset;
       	nm->flag |= FLAG_PRINT;
       	ft_printf("{original ptr:%p, size:%d, next: %p}\n", get_ptr(NULL), get_size(-1), next);
       	while (sec_ptr(next))
       	{
			handle_type(nm, next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8, next + 60);
			ar = (struct ar_hdr *)next;
			next += ft_atoi(ar->ar_size) + 60;
       	}
	}
}

// int				handle_type(char *ptr, char *file, char *object, int flag)
int				handle_type(t_nm *nm, char *ptr, char *object)
{
	unsigned int		magic_number;
	int					size_print;
	struct ar_hdr		*ar;

	*(nm->list) = NULL;
	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		size_print = handle_64(ptr, nm->list, (magic_number == MH_CIGAM_64) ?
			nm->flag | FLAG_BIGEN : nm->flag & ~FLAG_BIGEN);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		size_print = handle_32(ptr, nm->list, (magic_number == MH_CIGAM) ?
			nm->flag | FLAG_BIGEN : nm->flag & ~FLAG_BIGEN);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		nm->flag = (magic_number == FAT_CIGAM) ? nm->flag | FLAG_BIGEN : nm->flag & ~FLAG_BIGEN;
		size_print = handle_fat(nm, ptr);
	}
	else
	{
		if (!ft_strncmp((const char *)ptr, ARMAG, SARMAG))
		{
			ar = (struct ar_hdr *)(SARMAG * sizeof(char) + ptr);
			handle_arch(nm, (char *)(ar + 1), ft_atoi(ar->ar_size));
		}
		return (0);
	}
	if (size_print < 0)
		return (0);
	if (size_print > 0)
		print_output(nm->list, size_print, nm->file, object, nm->flag);
	free_symtable(nm->list);
	return (1);
}

int 	handle_file(t_nm *nm)
{
	int				fd;
	struct stat		buf;
	int				return_value;
	char			*ptr;

	nm->flag |= FLAG_PRINT;
	return_value = EXIT_SUCCESS;
	if ((fd = open(nm->file, O_RDONLY)) < 0)
		return (file_error("No such file or directory.", nm));
	if (fstat(fd, &buf) < 0)
		return (file_error("Error fstat.", nm));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
		return (file_error("Error mmap.", nm));
	get_ptr(ptr);
	get_size(buf.st_size);
	if (handle_type(nm, ptr, NULL) == 0)
		return_value = file_error("The file was not recognized as a valid objec\
t file\n", nm);
	if (munmap(ptr, buf.st_size) < 0)
		return_value = file_error("Error munmap.", nm);
	close(fd);
	return (return_value);
}

void		nm_init(t_nm *nm, char **av)
{
	nm->file = NULL;
	nm->command = av[0];
	nm->av = av;
	nm->flag = 0;
}

int 		main(int ac, char **av)
{
	t_nm		nm;
	char		default_name[6] = "a.out";
	int			i;
	int			return_value;
	t_symtable	*list;

	return_value = EXIT_SUCCESS;
	nm_init(&nm, av);
	nm.list = &list;
	if (ac < 2)
	{
		nm.file = default_name;
		return (handle_file(&nm));
	}
	nm.file = av[1];
	if ((i = nm_flag_handler(av, &(nm.flag))) < 0)
		return (return_value);
	nm.flag = ((ac - i - 2) > 0) ? nm.flag | FLAG_PRINT : nm.flag;
	while (++i < ac)
	{
		nm.file = av[i];
		return_value |= handle_file(&nm);
	}
	return (return_value);
}
