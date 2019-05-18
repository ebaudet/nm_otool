/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:32:13 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 01:17:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include <ranlib.h>
#include <ar.h>
#include "libftprintf.h"

static void		set_bigen(t_nm *nm, unsigned int magic_number)
{
	if (magic_number == MH_CIGAM_64
		|| magic_number == MH_CIGAM
		|| magic_number == FAT_CIGAM)
		nm->flag |= FLAG_BIGEN;
	else
		nm->flag &= ~FLAG_BIGEN;
}

static int		print_type(int size_print, t_nm *nm, char *object)
{
	if (size_print < 0)
		return (0);
	if (size_print > 0)
		print_output(nm, size_print, object);
	free_symtable(nm->list);
	return (1);
}

int				handle_type(t_nm *nm, char *ptr, char *object)
{
	unsigned int		magic_number;
	int					size_print;
	struct ar_hdr		*ar;

	*(nm->list) = NULL;
	magic_number = *(unsigned int *)ptr;
	set_bigen(nm, magic_number);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		size_print = handle_64(ptr, nm);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		size_print = handle_32(ptr, nm);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		size_print = handle_fat(nm, ptr);
	else if (!ft_strncmp((const char *)ptr, ARMAG, SARMAG))
	{
		ar = (struct ar_hdr *)(SARMAG * sizeof(char) + ptr);
		size_print = handle_arch(nm, (char *)(ar + 1), ft_atoi(ar->ar_size));
	}
	else
		return (0);
	return (print_type(size_print, nm, object));
}
