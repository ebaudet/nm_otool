/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:42:32 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/15 19:32:24 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdlib.h>

/*
** Create a new link of list t_symtable and assign the <offset>, <symbol>,
** <table_index> values.
** Return a pointer to the new link.
*/

t_symtable	*new_symtable(unsigned int offset, char symbol, char *table_index)
{
	t_symtable	*symtable;

	if ((symtable = (t_symtable *)malloc(sizeof(t_symtable))) == NULL)
		return (NULL);
	symtable->offset = offset;
	symtable->symbol = symbol;
	symtable->table_index = table_index;
	symtable->next = NULL;
	return (symtable);
}

/*
** Add a new link at the end of list <list>.
** The new link is created in the function and is <offset>, <symbol>,
** <table_index> values are assigned.
** Return a pointeur to the new link.
*/

t_symtable	*list_add_last_symtable(t_symtable *list, unsigned int offset,
	char symbol, char *table_index)
{
	t_symtable	*tmp;
	t_symtable	*symtable;

	if ((symtable = new_symtable(offset, symbol, table_index)) == NULL)
		return (NULL);
	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = symtable;
	return (symtable);
}

/*
** Add <new> in ordererd list stared by <list> in a position defined by the
** <compare> function.
** Return the first element of the list.
*/

t_symtable	*list_add_order_symtable(t_symtable *list, t_symtable *new,
	t_compate_symtable compare)
{
	t_symtable	*tmp;
	t_symtable	*old;

	tmp = list;
	old = list;
	while (tmp && tmp->next && (tmp == (compare)(tmp, new)))
	{
		old = tmp;
		tmp = tmp->next;
	}
	old->next = new;
	new->next = tmp;
	return (list);
}

/*
** Count the number of elements of the list <list>
*/

size_t		count_symtable(t_symtable *list)
{
	t_symtable	*tmp;
	size_t		cpt;

	cpt = 0;
	tmp = list;
	while (tmp)
	{
		tmp = tmp->next;
		cpt++;
	}
	return (cpt);
}
