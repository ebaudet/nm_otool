/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:06:55 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 16:13:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Add the new symtable to the list according to the flag order.
*/

t_symtable	*list_add(t_nm *nm, t_symtable *new)
{
	if (new == NULL)
		return (NULL);
	if (nm->flag & FLAG_P)
		list_add_order_symtable(nm->list, new, compare_end);
	else if (nm->flag & FLAG_PCAPS)
		list_add_order_symtable(nm->list, new, compare_first);
	else if (nm->flag & FLAG_R)
		list_add_order_symtable(nm->list, new, compare_tableindex_rev);
	else if (nm->flag & FLAG_N)
		list_add_order_symtable(nm->list, new, compare_offset);
	else
		list_add_order_symtable(nm->list, new, compare_tableindex);
	return (new);
}
