/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:51:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/13 19:39:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define FLAG_P		1
# define FLAG_PCAPS	2
# define FLAG_R		4
# define FLAG_ARCH	8
# define FLAG_BIGEN	16
# define FLAG_N		32
# define FLAG_PRINT	64
# define FLAG_PPC	128

# include <stddef.h>
# include <mach/machine.h>
# include <mach-o/fat.h>

typedef struct		s_arch_info {
	char			*name;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
}					t_arch_info;

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

long long int		ft_pow(int nb, unsigned int pow);
void				ft_puthex(long long int nb, int width);
char				*ft_gethex(long long int nb, int width);
void				eb_puthexa(int nbr);
int					ft_in_array(const unsigned int *haystack, size_t size,
					unsigned int needle);
void				ft_putprint(char const *s);

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
