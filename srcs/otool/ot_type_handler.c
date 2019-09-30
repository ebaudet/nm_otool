/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_type_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:33:03 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 17:29:56 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	ot_handle_arch(t_otool *otool)
{
	char			*next;
	struct ar_hdr	*ar;
	char			*ptr;
	int				offset;

	ar = (struct ar_hdr *)(SARMAG * sizeof(char) + otool->ptr);
	ptr = (char *)(ar + 1);
	offset = ft_atoi(ar->ar_size);
	if (!ft_strncmp((const char *)ptr, SYMDEF_SORTED, 20) ||
		!ft_strncmp((const char *)ptr, SYMDEF, 20))
	{
		ft_printf("Archive : %s\n", otool->file);
		otool->is_arch = true;
		next = ptr + offset;
		while (!sec_ptr(next))
		{
			otool->object = next + 60;
			ot_type_handler(otool,
				next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8);
			ar = (struct ar_hdr *)next;
			next += ft_atoi(ar->ar_size) + 60;
		}
	}
	return (EXIT_SUCCESS);
}

int			ot_type_handler(t_otool *otool, char *ptr)
{
	unsigned int		magic;
	int					result;

	otool->ptr = (ptr == NULL) ? otool->ptr_file : ptr;
	magic = *(unsigned int *)otool->ptr;
	if (set_arch(otool, magic))
	{
		result = ot_binary_handler(otool);
		if (result >= 0)
			return (result);
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		ot_flag(otool);
		otool->is_fat = TRUE;
		result = ot_fat_handler(otool);
		if (result >= 0)
			return (result);
	}
	else if (!ft_strncmp((const char *)otool->ptr, ARMAG, SARMAG))
		return (ot_handle_arch(otool));
	ft_printf("%s: is not an object file\n", otool->file);
	return (EXIT_SUCCESS);
}
