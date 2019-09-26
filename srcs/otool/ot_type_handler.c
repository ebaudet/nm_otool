/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_type_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:33:03 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:52:36 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		ot_type_handler(t_otool *otool)
{
	unsigned int		magic;

	otool->ptr = otool->ptr_file;
	magic = *(unsigned int *)otool->ptr;
	if (set_arch(otool, magic))
		return (ot_binary_handler(otool));
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		ot_flag(otool);
		otool->is_fat = TRUE;
		return (ot_fat_handler(otool));
	}
	return (-1);
}
