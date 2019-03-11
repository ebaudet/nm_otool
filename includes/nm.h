/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/11 16:55:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stddef.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include "math.h"

# define FLAG_P		0b1
# define FLAG_PCAPS	0b10
# define FLAG_R		0b100
# define FLAG_ARCH	0b1000
# define FLAG_BIGEN	0b10000
# define FLAG_N		0b100000
# define FLAG_PRINT	0b1000000

typedef struct		s_symtable
{
	char				*offset;
	char				symbol;
	char				*table_index;
	struct s_symtable	*next;
}					t_symtable;

typedef struct		s_arch_info {
	char			*name;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
}					t_arch_info;

typedef t_symtable	*(*t_compate_symtable)(t_symtable *, t_symtable *);

/*
** nm.c
*/
char				get_section_letter(char *section);
char				undef(int type, int addr, char c);
char				get_symbol(char *section, int type, int addr, int sect);
void				print_output(t_symtable **list, int size, char *av, int flag);
int					handle_type(char *ptr, char *av, int flag);

/*
** nm_64.c
*/
struct section_64	*get_section_64(struct segment_command_64 *segment,
					uint32_t offset, int flag);
t_symtable 			*add_symtable_64(struct nlist_64 array,
					struct section_64 *section, char *stringtable,
					t_symtable **list, int flag);
void				get_symtable_64(struct symtab_command *sym, int nsyms,
					char *ptr, t_symtable **list, int flag);
int					handle_64(char *ptr, t_symtable **list, int flag);

/*
** nm_32.c
*/
t_symtable 			*add_symtable_32(struct nlist array,
					struct section *section, char *stringtable,
					t_symtable **list, int flag);
struct section		*get_section_32(struct segment_command *segment,
					uint32_t offset, int flag);
void				get_symtable_32(struct symtab_command *sym, int nsyms,
					char *ptr, t_symtable **list, int flag);
int					handle_32(char *ptr, t_symtable **list, int flag);

/*
** nm_fat.c
*/
int					handle_fat(char *ptr, char *av, int flag);

/*
** flag_handler.c
*/
int					nm_flag_handler(char **av, int *flag);

/*
** symtable.c
*/
t_symtable			*new_symtable(char *offset, char symbol, char *table_index);
t_symtable			*list_add_last_symtable(t_symtable **list, char *offset,
					char symbol, char *table_index);
t_symtable			*list_add_order_symtable(t_symtable **list, t_symtable *new,
					t_compate_symtable compare);
size_t				count_symtable(t_symtable **list);
void				free_symtable(t_symtable **list);

/*
** compare.c
*/
t_symtable			*compare_tableindex(t_symtable *a, t_symtable *b);
t_symtable			*compare_tableindex_rev(t_symtable *a, t_symtable *b);
t_symtable			*compare_end(t_symtable *a, t_symtable *b);
t_symtable			*compare_first(t_symtable *a, t_symtable *b);
t_symtable			*compare_offset(t_symtable *a, t_symtable *b);

/*
** ft_error.c
*/
int					print_error(char *message);
int					file_error(char *message, char *file, char *function);

/*
** endian_swap.c
*/
unsigned int		endian_swap(unsigned int x);
unsigned long		lendian_swap(unsigned long x);
unsigned int		bed(unsigned int x, int flag);
unsigned long		lbed(unsigned long x, int flag);

/*
** NM_H
*/
#endif
