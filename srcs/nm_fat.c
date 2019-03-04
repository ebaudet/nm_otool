/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/03 20:17:11 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

void		put_achitecture_name(char *av, int cputype, int my_arch)
{
	if (my_arch)
		return;
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
		ft_putstr("ppc");
	else if (cputype == CPU_TYPE_POWERPC64)
		ft_putstr("ppc64");
	ft_putendl("):");
}

// TODO : check pour n'afficher que l'architecture x86_64 si l'option FLAG_ARCH
// n'est pas indiquée.
// Pour faire ça, il faut faire une boucle dans les fat_arch et determiner si
// on retrouve notre archi.
// Si oui, on affichera les tables de symboles seulement pour notre architecture
// Si non, on affichera toutes les architectures, comme pour l'option -arch
static int	is_my_arch(char *ptr, struct fat_header *fheader, struct fat_arch *farch,
	int flag)
{
	(void)ptr;
	(void)fheader;
	(void)farch;
	(void)flag;
	unsigned int			i;

	if (flag & FLAG_ARCH)
		return (0);

	i = 0;
	while (++i <= bed(fheader->nfat_arch, flag))
	{
// 		ft_printf("{%31kfat_arch%k: cputype:%x, cpusubtype:%x, offset:%d, size:%d\
// , align:%d}\n", bed(farch->cputype, flag), bed(farch->cpusubtype, flag),
// bed(farch->offset, flag), bed(farch->size, flag), ft_pow(2, bed(farch->align, flag)));
		if (bed(farch->cputype, flag) == CPU_TYPE_X86_64)
			return (1);
		farch++;
	}
	return (0);
}

void		handle_fat(char *ptr, t_symtable **list, char *av, int flag)
{
	struct fat_header		*fheader;
	struct fat_arch			*farch;
	unsigned int			i;
	struct mach_header_64	*header;
	int						my_arch;

	fheader = (struct fat_header *)ptr;
	// ft_printf("{magic:%#x, nfat_arch:%d}\n", bed(fheader->magic, flag), bed(fheader->nfat_arch, flag));
	i = 0;
	farch = (struct fat_arch *)(fheader + 1);
	my_arch = is_my_arch(ptr, fheader, farch, flag);
	while (++i <= bed(fheader->nfat_arch, flag))
	{
		if (my_arch && (bed(farch->cputype, flag) != CPU_TYPE_X86_64) && farch++)
			continue ;
		header = (void *)ptr + bed(farch->offset, flag);
		put_achitecture_name(av, bed(farch->cputype, flag), my_arch);
		ft_printf("<JE PASSE ICI %x>\n", bed(header->magic, flag));
		unsigned short int a, b;
		a = 0xf0f0;
		b = 0xff00;
		ft_printf(
		"a:%0.4x, b:%0.4x, !a:%0.4x, !b:%0.4x, ~a:%0.4x, ~b:%0.4x, a&b:%0.4x, a|b:%0.4x, a^b:%0.4x\n",
		 a, b, !a, !b, ~a, ~b, a&b, a|b, a^b);
		if (flag == (flag | FLAG_BIGEN))
			ft_printf("1.FLAG_BIGEN is put\n");
		if (flag & FLAG_BIGEN)
			ft_printf("1.FLAG_BIGEN is put 2\n");
		if (flag == (flag & ~FLAG_BIGEN))
			ft_printf("1.FLAG_BIGEN is not put\n");
		if (flag & ~FLAG_BIGEN)
			ft_printf("1.FLAG_BIGEN is not put2\n");

		flag &= ~FLAG_BIGEN;
		if (flag == (flag | FLAG_BIGEN))
			ft_printf("2.FLAG_BIGEN is put\n");
		if (flag & FLAG_BIGEN)
			ft_printf("2.FLAG_BIGEN is put 2\n");
		if (flag == (flag & ~FLAG_BIGEN))
			ft_printf("2.FLAG_BIGEN is not put\n");
		if (flag & ~FLAG_BIGEN)
			ft_printf("2.FLAG_BIGEN is not put2\n");


		if (header->magic == MH_MAGIC_64 || header->magic == MH_CIGAM_64)
		{
			if (bed(header->magic, flag) == MH_CIGAM_64)
				flag |= FLAG_BIGEN;
			else
				flag &= ~FLAG_BIGEN;
			handle_64((char *)header, list, flag);
			print_output(list, 16);
		}
		else if (header->magic == MH_MAGIC || header->magic == MH_CIGAM)
		{
			if (bed(header->magic, flag) == MH_CIGAM)
				flag |= FLAG_BIGEN;
			else
				flag &= ~FLAG_BIGEN;
			handle_32((char *)header, list, flag);
			print_output(list, 8);
		} else {
			ft_printf("header magic:%x\n", header->magic);
		}
		free_symtable(list);
		farch++;
		flag |= FLAG_BIGEN;
	}
}