/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/15 19:01:09 by ebaudet          ###   ########.fr       */
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
	unsigned long	offset;
	char			symbol;
	char			*table_index;
	struct s_symtable	*next;
}				t_symtable;

typedef t_symtable	*(*t_compate_symtable)(t_symtable *, t_symtable *);

/*
** symtable.c
*/
t_symtable		*new_symtable(unsigned int offset, char symbol,
				char *table_index);
t_symtable		*list_add_last_symtable(t_symtable *list, unsigned int offset,
				char symbol, char *table_index);
size_t			count_symtable(t_symtable *list);

/*
** NM_H
*/
#endif
