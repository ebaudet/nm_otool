/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:41:52 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 14:53:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void		print_section_64(t_otool *otool, struct section_64 *section)
{
	unsigned int	j;

	j = 0;
	if (sec_ptr(&otool->ptr[section->offset + j]))
		return ;
	if (otool->is_fat == TRUE)
		ft_printf("Contents of (__TEXT,__text) section");
	else
		ft_printf("%s:\nContents of (__TEXT,__text) section", otool->file);
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

static void		print_section_32(t_otool *otool, struct section *section)
{
	unsigned int	j;

	j = 0;
	if (sec_ptr(&otool->ptr[get_addr_endian(section->offset, otool) + j]))
		return ;
	if (otool->is_fat)
		ft_printf("Contents of (__TEXT,__text) section");
	else
		ft_printf("%s:\nContents of (__TEXT,__text) section", otool->file);
	while (j < get_addr_endian(section->size, otool))
	{
		if (!(j % 16))
		{
			ft_putchar('\n');
			ft_puthex(get_addr_endian(section->addr, otool) + j,
				otool->flag & FLAG_PPC ? 8 : 8);
			ft_putchar('\t');
		}
		ft_puthex(otool->ptr[get_addr_endian(section->offset,
			otool) + j] & 0xFF, 2);
		if (!((otool->flag & FLAG_PPC) && (j % 4) - 3))
			ft_putchar(' ');
		j += otool->flag & FLAG_PPC ? 1 : 1;
	}
	ft_putchar('\n');
}

void			print_section(t_otool *otool, char *section)
{
	if (otool->arch == E_32B)
		print_section_32(otool, (struct section *)section);
	else if (otool->arch == E_64B)
		print_section_64(otool, (struct section_64 *)section);
	else
		ft_printf("no arch detected\n");
}
