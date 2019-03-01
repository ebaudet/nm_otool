/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/01 02:26:38 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "math.h"


typedef struct		s_symtable
{
	char				*offset;
	char				symbol;
	char				*table_index;
	struct s_symtable	*next;
}					t_symtable;

typedef t_symtable	*(*t_compate_symtable)(t_symtable *, t_symtable *);

/*
** nm.c
*/
char				get_section_letter(char *section);
char				undef(int type, int addr, char c);
char				get_symbol(char *section, int type, int addr, int sect);
void				print_output(t_symtable **list, int size);

/*
** nm_64.c
*/
struct section_64	*get_section_64(struct segment_command_64 *segment,
					uint32_t offset);
t_symtable 			*add_symtable_64(struct nlist_64 array,
					struct section_64 *section, char *stringtable,
					t_symtable **list);
void				get_symtable_64(struct symtab_command *sym, int nsyms,
					char *ptr, t_symtable **list);
void				handle_64(char *ptr, t_symtable **list);

/*
** nm_32.c
*/
t_symtable 			*add_symtable_32(struct nlist array,
					struct section *section, char *stringtable,
					t_symtable **list);
struct section		*get_section_32(struct segment_command *segment,
					uint32_t offset);
void				get_symtable_32(struct symtab_command *sym, int nsyms,
					char *ptr, t_symtable **list);
void				handle_32(char *ptr, t_symtable **list);

/*
** nm_fat.c
*/
void				handle_fat(char *ptr, t_symtable **list, char *av);


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

/*
** ft_error.c
*/
int					print_error(char *message);
int					file_error(char *message, char *file, char *function);

/*
** endian_swap.c
*/
unsigned int		endian_swap(unsigned int x);

/*
** NM_H
*/
#endif
