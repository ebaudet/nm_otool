/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/16 18:42:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

#include <stddef.h>

int				print_error(char *message);
int				file_error(char *message, char *file);
unsigned int	endian_swap(unsigned int x);

typedef struct	s_symtable
{
	char				*offset;
	char				symbol;
	char				*table_index;
	struct s_symtable	*next;
}				t_symtable;

typedef t_symtable	*(*t_compate_symtable)(t_symtable *, t_symtable *);

/*
** symtable.c
*/
t_symtable		*new_symtable(char *offset, char symbol, char *table_index);
t_symtable		*list_add_last_symtable(t_symtable **list, char *offset,
				char symbol, char *table_index);
t_symtable		*list_add_order_symtable(t_symtable **list, t_symtable *new,
				t_compate_symtable compare);
size_t			count_symtable(t_symtable **list);
void			free_symtable(t_symtable **list);

/*
** compare.c
*/
t_symtable		*compare_tableindex(t_symtable *a, t_symtable *b);
t_symtable		*compare_tableindex_rev(t_symtable *a, t_symtable *b);
t_symtable		*compare_end(t_symtable *a, t_symtable *b);
t_symtable		*compare_first(t_symtable *a, t_symtable *b);

/*
** NM_H
*/
#endif
