/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 05:44:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

void	put_achitecture_name(char *av, int cputype)
{
	ft_printf("\n%s (for architecture ", av);
	if (cputype == CPU_TYPE_I386)
		ft_putstr("i386");
	else if (cputype == CPU_TYPE_X86)
		ft_putstr("x86");
	else if (cputype == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (cputype == CPU_TYPE_MC680x0)
		ft_putstr("mc680x0");
	else if (cputype == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else if (cputype == CPU_TYPE_HPPA)
		ft_putstr("hppa");
	else if (cputype == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (cputype == CPU_TYPE_ARM64)
		ft_putstr("arm64");
	else if (cputype == CPU_TYPE_MC88000)
		ft_putstr("mc88000");
	else if (cputype == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (cputype == CPU_TYPE_I860)
		ft_putstr("i860");
	else if (cputype == CPU_TYPE_POWERPC)
		ft_putstr("powerpc");
	else if (cputype == CPU_TYPE_POWERPC64)
		ft_putstr("powerpc64");
	ft_putendl("):");
}

int

void	handle_fat(char *ptr, t_symtable **list, char *av, int flag)
{
	struct fat_header		*fheader;
	struct fat_arch			*arch;
	unsigned int	i;
	struct mach_header_64 	*header;

	fheader = (struct fat_header *)ptr;
	// ft_printf("{magic:%#x, nfat_arch:%d}\n", bed(fheader->magic, flag), bed(fheader->nfat_arch, flag));
	i = 0;
	arch = (struct fat_arch *)(fheader + 1);
	while (++i <= bed(fheader->nfat_arch, flag))
	{
		header = (void *)ptr + bed(arch->offset, flag);
		put_achitecture_name(av, header->cputype);
		if (header->magic == MH_MAGIC_64)
		{
			flag &= ~FLAG_BIGEN;
			handle_64((char *)header, list, flag);
			print_output(list, 16);
		}
		else if (header->magic == MH_MAGIC)
		{
			flag &= ~FLAG_BIGEN;
			handle_32((char *)header, list, flag);
			print_output(list, 8);
		}
		arch++;
		flag |= FLAG_BIGEN;
	}
}