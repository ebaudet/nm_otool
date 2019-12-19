/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:23 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/19 17:45:28 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <stdbool.h>
# include "utils.h"
# include "libft.h"
# include "libftprintf.h"
# include <mach-o/loader.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ar.h>
# include <ranlib.h>

typedef enum	e_arch
{
	E_32B,
	E_64B
}				t_arch;

typedef enum	e_end
{
	E_BIG,
	E_LITTLE
}				t_end;

typedef struct	s_otool
{
	t_arch			arch;
	t_end			endian;
	char			*file;
	char			*ptr_file;
	char			*ptr;
	unsigned int	segment;
	int				flag;
	unsigned int	nfat_arch;
	bool			is_fat;
	bool			is_arch;
	char			*object;
}				t_otool;

unsigned int	get_addr_endian(unsigned int addr, t_otool *otool);
uint32_t		get_segment_command_nsects(char *ptr, t_arch arch);
int				loop_lc_segment(t_otool *otool, char *addr);
unsigned int	obed(unsigned int val, t_otool *otool);
int				ot_binary_handler(t_otool *otool);
int				ot_fat_handler(t_otool *o);
int				ot_flag(t_otool *o);
char			*ot_put_achitecture_name(t_otool *o, cpu_type_t cputype,
				cpu_subtype_t cpusubtype, int my_arch);
int				ot_type_handler(t_otool *otool, char *prt);
int				print_section(t_otool *otool, char *section);
int				set_arch(t_otool *otool, uint32_t magic);
size_t			sizeof_mach_header(t_arch arch);
size_t			sizeof_section(t_arch arch);
size_t			sizeof_segment_command(t_arch arch);
int				treatment_file(char *file);

/*
** OTOOL_H
*/
#endif
