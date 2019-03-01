/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 02:56:09 by ebaudet          ###   ########.fr       */
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

void	handle_fat(char *ptr, t_symtable **list, char *av)
{
	(void)list;
	(void)ptr;
	struct fat_header		*fheader;
	struct fat_arch			*arch;
	unsigned int	i;
	struct mach_header_64 	*header;

	fheader = (struct fat_header *)ptr;
	ft_printf("{magic:%#x, nfat_arch:%d}\n", endian_swap(fheader->magic), endian_swap(fheader->nfat_arch));
	i = 0;
	arch = (struct fat_arch *)(fheader + 1);
	while (++i <= endian_swap(fheader->nfat_arch))
	{
		// ft_printf("{%31kfat_arch %d%k : cputype:%x, cpusubtype:%x, offset:%d, size:%d, align:%d}\n",
	 //       i, endian_swap(arch->cputype), endian_swap(arch->cpusubtype), endian_swap(arch->offset), endian_swap(arch->size), (int)ft_pow(2, endian_swap((uint32_t)arch->align)));
		header = (void *)ptr + endian_swap(arch->offset);
		// ft_printf("{HEADER: magic:%x, cputype:%x, cpusubtype:%x, filetype:%x, ncmds:%d, sizeofcmds:%d, flags:%d}\n",
		// 	header->magic, header->cputype,
		// 	header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
		// 	header->flags);
		put_achitecture_name(av, header->cputype);
		if (header->magic == MH_MAGIC_64)
		{
			// ft_printf("%33k<call handle_64>%k\n");
			// ft_printf("%s (for architecture )", av);
			handle_64((char *)header, list);
			// ft_printf("%33k<end handle_64>%k\n");
			// ft_printf("%33k<call print_output>%k\n");
			print_output(list, 16);
			// ft_printf("%33k<end print_output>%k\n");
		}
		else if (header->magic == MH_MAGIC)
		{
			// ft_printf("%33k<call handle_32>%k\n");
			handle_32((char *)header, list);
			// ft_printf("%33k<end handle_32>%k\n");
			// ft_printf("%33k<call print_output>%k\n");
			print_output(list, 8);
			// ft_printf("%33k<end print_output>%k\n");
		}
		// free_symtable(list);

		arch++;
	}


// 	header = (struct mach_header_64 *)(arch + 1);
// 	ft_printf("{HEADER: magic:%x, cputype:%x, cpusubtype:%x, filetype:%x, ncmds:%d, sizeofcmds:%d, flags:%d}\n",
// 	 header->magic, header->cputype,
// header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
// header->flags);

	// struct load_command		*lc;
	// lc = (struct load_command *)(arch + 1);
	// printf("{load_command: cmd:%x, cmdsize:%x}\n", lc->cmd, lc->cmdsize);

// 	int						ncmds;
// 	int						i;
// 	struct mach_header_64	*header;
// 	struct load_command		*lc;
// 	struct symtab_command	*sym;

// 	header = (struct mach_header_64 *)ptr;
// 	ncmds = header->ncmds;
// 	i = 0;
// 	lc = (void *)ptr + sizeof(*header);
// 	ft_printf("{HEADER: magic:%x, cputype:%d, cpusubtype:%d, filetype:%d, ncmds:%d, sizeofcmds:%d, flags:%d, reserved:%d}\n",
// 	 header->magic, header->cputype,
// header->cpusubtype, header->filetype, header->ncmds, header->sizeofcmds,
// header->flags, header->reserved);
// 	while (i < ncmds)
// 	{
// 		// ft_printf("%33k<cmd %d/%d>%k\n", i, ncmds);
// 		if (lc->cmd == LC_SYMTAB)
// 		{
// 			sym = (struct symtab_command *)lc;
// 			get_symtable_fat(sym, sym->nsyms, ptr, list);
// 			break ;
// 		}
// 		lc = (void *)lc + lc->cmdsize;
// 		i++;
// 	}
}