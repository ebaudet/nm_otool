/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_type_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:33:03 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 15:09:12 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		ot_type_handler(t_otool *otool)
{
	unsigned int		magic;
	int					result;

	otool->ptr = otool->ptr_file;
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
	ft_printf("%s: is not an object file\n", otool->file);
	return (EXIT_SUCCESS);
}
