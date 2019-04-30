/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:56:24 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/30 12:42:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

static const t_arch_info	g_infos[] = {
	{"any", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE},
	{"arm", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_ALL},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_ALL},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_V8},
	{"armv4t", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V4T},
	{"armv5", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V5TEJ},
	{"armv6", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6},
	{"armv6m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6M},
	{"armv7", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7},
	{"armv7em", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7EM},
	{"armv7f", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7F},
	{"armv7k", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7K},
	{"armv7m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7M},
	{"armv7s", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7S},
	{"armv8", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V8},
	{"big", CPU_TYPE_ANY, CPU_SUBTYPE_BIG_ENDIAN},
	{"hppa", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_ALL},
	{"hppa7100LC", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_7100LC},
	{"i386", CPU_TYPE_I386, CPU_SUBTYPE_I386_ALL},
	{"i486", CPU_TYPE_I386, CPU_SUBTYPE_486},
	{"i486SX", CPU_TYPE_I386, CPU_SUBTYPE_486SX},
	{"i586", CPU_TYPE_I386, CPU_SUBTYPE_586},
	{"i686", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO},
	{"i860", CPU_TYPE_I860, CPU_SUBTYPE_I860_ALL},
	{"little", CPU_TYPE_ANY, CPU_SUBTYPE_LITTLE_ENDIAN},
	{"m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY},
	{"m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040},
	{"m68k", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL},
	{"m88k", CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL},
	{"pentIIm3", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3},
	{"pentIIm5", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5},
	{"pentium", CPU_TYPE_I386, CPU_SUBTYPE_PENT},
	{"pentium4", CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4},
	{"pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO},
	{"ppc", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL},
	{"ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601},
	{"ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603},
	{"ppc603e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e},
	{"ppc603ev", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603ev},
	{"ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604},
	{"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e},
	{"ppc64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL},
	{"ppc7450", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450},
	{"ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750},
	{"ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970},
	{"ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970},
	{"sparc", CPU_TYPE_SPARC, CPU_SUBTYPE_SPARC_ALL},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL},
	{"x86_64", CPU_TYPE_X86_64, 0x80000003},
	{"x86_64h", CPU_TYPE_I386, CPU_SUBTYPE_X86_64_H},
	{"x86_64h", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H},
	{"xscale", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_XSCALE},
	{NULL, 0, 0}
};

char		*put_achitecture_name(char *av, cpu_type_t cputype,
			cpu_subtype_t cpusubtype, int my_arch, int print_arch)
{
	int		i;

	if (my_arch)
		return ("");
	if (print_arch > 1)
		ft_printf("\n%s (for architecture ", av);
	else
		ft_printf("%s:\n", av);
	i = -1;
	while (g_infos[++i].name != NULL)
	{
		if (g_infos[i].cputype == cputype
			&& g_infos[i].cpusubtype == cpusubtype)
		{
			if (print_arch > 1)
				ft_putstr(g_infos[i].name);
			break ;
		}
	}
	if (print_arch > 1)
		ft_putendl("):");
	return (g_infos[i].name);
}

/*
** TODO : check pour n'afficher que l'architecture x86_64 si l'option FLAG_ARCH
** n'est pas indiquée.
** Pour faire ça, il faut faire une boucle dans les fat_arch et determiner si
** on retrouve notre archi.
** Si oui, on affichera les tables de symboles seulement pour notre architecture
** Si non, on affichera toutes les architectures, comme pour l'option -arch
*/

static int	is_my_arch_current(struct fat_arch *farch, int flag)
{
	if (bed(farch->cputype, flag) == CPU_TYPE_X86_64
		&& (bed(farch->cpusubtype, flag) == 0x80000003
			|| bed(farch->cpusubtype, flag) == CPU_SUBTYPE_X86_64_ALL))
		return (1);
	return (0);
}

static int	is_my_arch(struct fat_header *fheader, struct fat_arch *farch,
	int flag)
{
	unsigned int			i;

	if (flag & FLAG_ARCH)
	{
		return (0);
	}
	i = 0;
	while (++i <= bed(fheader->nfat_arch, flag))
	{
		if (is_my_arch_current(farch, flag))
			return (1);
		farch++;
	}
	return (0);
}

int			handle_fat(t_nm *nm, char *ptr)
{
	struct fat_header		*fheader;
	struct fat_arch			*farch;
	unsigned int			i;
	struct mach_header_64	*header;
	int						my_arch;
	unsigned int nfat_arch;

	nm->flag |= FLAG_BIGEN;
	fheader = (struct fat_header *)ptr;
	i = 0;
	farch = (struct fat_arch *)(fheader + 1);
	my_arch = is_my_arch(fheader, farch, nm->flag);
	nfat_arch = bed(fheader->nfat_arch, nm->flag);
	while (++i <= nfat_arch)
	{
		nm->flag |= FLAG_BIGEN;

		if (my_arch && !is_my_arch_current(farch, nm->flag) && farch++)
			continue ;
		header = (void *)ptr + bed(farch->offset, nm->flag);
		if (!ft_strcmp(put_achitecture_name(nm->file, bed(farch->cputype, nm->flag),
			bed(farch->cpusubtype, nm->flag), my_arch, bed(fheader->nfat_arch, nm->flag)), "ppc"))
		{
			nm->flag |= FLAG_PPC;
		}
		else
			nm->flag &= ~FLAG_PPC;
		nm->flag &= ~FLAG_PRINT;
		handle_type(nm, (char *)header, NULL);
		nm->flag &= ~FLAG_PPC;
		farch++;
	}
	return (0);
}
