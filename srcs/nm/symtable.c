/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:42:32 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/13 22:18:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

/*
** Create a new link of list t_symtable and assign the <offset>, <symbol>,
** <table_index> values.
** Return a pointer to the new link.
*/

t_symtable	*new_symtable(char *offset, char symbol, char *table_index)
{
	t_symtable	*new;

	if (sec_ptr(table_index))
		return (NULL);
	if ((new = (t_symtable *)malloc(sizeof(t_symtable))) == NULL)
		return (NULL);
	new->offset = offset;
	new->symbol = symbol;
	new->malloc = 0;
	if (ft_strchr("iI", symbol))
	{
		new->table_index = ft_concat(4, table_index, " (indirect for ",
			table_index, ")");
		new->malloc = 1;
	}
	else
		new->table_index = table_index;
	new->next = NULL;
	return (new);
}

/*
** Add a new link at the end of list <list>.
** The new link is created in the function and is <offset>, <symbol>,
** <table_index> values are assigned.
** Return a pointeur to the new link.
*/

t_symtable	*list_add_last_symtable(t_symtable **list, char *offset,
	char symbol, char *table_index)
{
	t_symtable	*tmp;
	t_symtable	*new;

	if ((new = new_symtable(offset, symbol, table_index)) == NULL)
		return (NULL);
	if (*list == NULL)
	{
		*list = new;
		return (*list);
	}
	tmp = *list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

/*
** Add <new> in ordererd list stared by <list> in a position defined by the
** <compare> function.
** Return the first element of the list.
*/

t_symtable	*list_add_order_symtable(t_symtable **list, t_symtable *new,
	t_compate_symtable compare)
{
	t_symtable	*tmp;
	t_symtable	*old;

	if (*list == NULL)
	{
		*list = new;
		new->next = NULL;
		return (*list);
	}
	if (new == (compare)(*list, new))
	{
		new->next = (*list);
		*list = new;
		return (*list);
	}
	tmp = *list;
	old = *list;
	while (tmp && (tmp == (compare)(tmp, new)))
	{
		old = tmp;
		tmp = tmp->next;
	}
	new->next = old->next;
	old->next = new;
	return (*list);
}

/*
** Count the number of elements of the list <list>
*/

size_t		count_symtable(t_symtable **list)
{
	t_symtable	*tmp;
	size_t		cpt;

	cpt = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		cpt++;
	}
	return (cpt);
}

/*
** Free the chained list <list>
*/

void		free_symtable(t_symtable **list)
{
	t_symtable	*tmp;
	t_symtable	*old;

	if (!list || *list == NULL)
		return ;
	tmp = *list;
	while (tmp != NULL)
	{
		old = tmp;
		tmp = tmp->next;
		if (old->malloc)
			free(old->table_index);
		free(old->offset);
		free(old);
	}
	*list = NULL;
}
