/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:51:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/04 12:52:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define FLAG_P		0b1
# define FLAG_PCAPS	0b10
# define FLAG_R		0b100
# define FLAG_ARCH	0b1000
# define FLAG_BIGEN	0b10000
# define FLAG_N		0b100000
# define FLAG_PRINT	0b1000000
# define FLAG_PPC	0b10000000

# include <stddef.h>
# include <mach/machine.h>
# include <mach-o/fat.h>

typedef enum	te_arch
{
	E_32B,
	E_64B
}				e_arch;

typedef struct		s_arch_info {
	char			*name;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	e_arch			arch;
}					t_arch_info;

static const t_arch_info	g_infos[] = {
	{"any", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE, E_64B},
	{"arm", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_ALL, E_64B},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_ALL, E_64B},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_V8, E_64B},
	{"armv4t", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V4T, E_32B},
	{"armv5", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V5TEJ, E_32B},
	{"armv6", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6, E_32B},
	{"armv6m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6M, E_32B},
	{"armv7", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7, E_32B},
	{"armv7em", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7EM, E_32B},
	{"armv7f", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7F, E_32B},
	{"armv7k", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7K, E_32B},
	{"armv7m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7M, E_32B},
	{"armv7s", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7S, E_32B},
	{"armv8", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V8, E_64B},
	{"big", CPU_TYPE_ANY, CPU_SUBTYPE_BIG_ENDIAN, E_64B},
	{"hppa", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_ALL, E_32B},
	{"hppa7100LC", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_7100LC, E_32B},
	{"i386", CPU_TYPE_I386, CPU_SUBTYPE_I386_ALL, E_32B},
	{"i486", CPU_TYPE_I386, CPU_SUBTYPE_486, E_32B},
	{"i486SX", CPU_TYPE_I386, CPU_SUBTYPE_486SX, E_32B},
	{"i586", CPU_TYPE_I386, CPU_SUBTYPE_586, E_32B},
	{"i686", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO, E_32B},
	{"i860", CPU_TYPE_I860, CPU_SUBTYPE_I860_ALL, E_32B},
	{"little", CPU_TYPE_ANY, CPU_SUBTYPE_LITTLE_ENDIAN, E_32B},
	{"m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY, E_32B},
	{"m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040, E_32B},
	{"m68k", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL, E_32B},
	{"m88k", CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL, E_32B},
	{"pentIIm3", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3, E_32B},
	{"pentIIm5", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5, E_32B},
	{"pentium", CPU_TYPE_I386, CPU_SUBTYPE_PENT, E_32B},
	{"pentium4", CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4, E_64B},
	{"pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO, E_32B},
	{"ppc", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL, E_32B},
	{"ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601, E_32B},
	{"ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603, E_32B},
	{"ppc603e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e, E_32B},
	{"ppc603ev", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603ev, E_32B},
	{"ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604, E_32B},
	{"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e, E_32B},
	{"ppc64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL, E_64B},
	{"ppc7450", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450, E_32B},
	{"ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750, E_32B},
	{"ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970, E_32B},
	{"ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970, E_64B},
	{"sparc", CPU_TYPE_SPARC, CPU_SUBTYPE_SPARC_ALL, E_64B},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL, E_64B},
	{"x86_64", CPU_TYPE_X86_64, 0x80000003, E_64B},
	{"x86_64h", CPU_TYPE_I386, CPU_SUBTYPE_X86_64_H, E_64B},
	{"x86_64h", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H, E_64B},
	{"xscale", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_XSCALE, E_32B},
	{NULL, 0, 0, 0}
};

/*
** ft_pow.c
*/
long long int		ft_pow(int nb, unsigned int pow);

/*
** ft_puthex.c
*/
void				ft_puthex(long long int nb, int width);

/*
** ft_gethex.c
*/
char				*ft_gethex(long long int nb, int width);

/*
** int_to_hexa.c
*/
void				eb_puthexa(int nbr);

/*
** ft_in_array.c
*/
int					ft_in_array(const unsigned int *haystack, size_t size,
					unsigned int needle);

/*
** endian_swap.c
*/
unsigned int		endian_swap(unsigned int x);
unsigned long		lendian_swap(unsigned long x);
unsigned int		bed(unsigned int x, int flag);
unsigned long		lbed(unsigned long x, int flag);

/*
** ft_secure.c
*/
int					get_size(int size);
char				*get_ptr(char *ptr);
int					sec_ptr(char *ptr);

/*
** ft_error.c
*/
int					print_error(char *message);
int					file_error(char *message, char *file);


/*
** ft_is_my_arch.c
*/
int					is_my_arch_current(struct fat_arch *farch, int flag);
int					is_my_arch(struct fat_header *fheader,
					struct fat_arch *farch, int flag);

#endif
