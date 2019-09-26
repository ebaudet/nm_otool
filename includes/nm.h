/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:59:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stddef.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <stdlib.h>
# include <unistd.h>
# include "utils.h"

typedef struct		s_symtable
{
	char				*offset;
	char				symbol;
	char				*table_index;
	struct s_symtable	*next;
}					t_symtable;

typedef struct		s_nm {
	char			*file;
	char			*command;
	char			**av;
	int				flag;
	int				flag_save;
	t_symtable		**list;
	unsigned int	nfat_arch;
}					t_nm;

typedef t_symtable	*(*t_compate_symtable)(t_symtable *, t_symtable *);

/*
** nm.c
*/
int					nm_error(char *message, t_nm *nm);

/*
** handle_arch.c
*/
int					handle_arch(t_nm *nm, char *ptr, int offset);

/*
** handle_type.c
*/
int					handle_type(t_nm *nm, char *ptr, char *object);

/*
** handle_file.c
*/
int					handle_file(t_nm *nm);

/*
** nm_64.c
*/
struct section_64	*get_section_64(struct segment_command_64 *segment,
					uint32_t offset, int flag);
t_symtable			*add_symtable_64(struct nlist_64 array,
					struct section_64 *section, char *stringtable, t_nm *nm);
void				get_symtable_64(struct symtab_command *sym, int nsyms,
					char *ptr, t_nm *nm);
int					handle_64(char *ptr, t_nm *nm);

/*
** nm_32.c
*/
t_symtable			*add_symtable_32(struct nlist array,
					struct section *section, char *stringtable, t_nm *nm);
struct section		*get_section_32(struct segment_command *segment,
					uint32_t offset, int flag);
void				get_symtable_32(struct symtab_command *sym, int nsyms,
					char *ptr, t_nm *nm);
int					handle_32(char *ptr, t_nm *nm);

/*
** nm_fat.c
*/
int					handle_fat(t_nm *nm, char *ptr);

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
** list_add.c
*/
t_symtable			*list_add(t_nm *nm, t_symtable *new);

/*
** compare.c
*/
t_symtable			*compare_tableindex(t_symtable *a, t_symtable *b);
t_symtable			*compare_tableindex_rev(t_symtable *a, t_symtable *b);
t_symtable			*compare_end(t_symtable *a, t_symtable *b);
t_symtable			*compare_first(t_symtable *a, t_symtable *b);
t_symtable			*compare_offset(t_symtable *a, t_symtable *b);

/*
** symbol.c
*/
char				get_section_letter(char *section);
char				undef(int type, int addr, char c);
char				get_symbol(char *section, int type, int addr, int sect);

/*
** print_output.c
*/
void				print_output(t_nm *nm, int size, char *object);

/*
** NM_H
*/
#endif
