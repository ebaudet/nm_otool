/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:34:27 by ebaudet           #+#    #+#             */
/*   Updated: 2019/03/02 23:01:04 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

/*
** Compare <a> and <b> with the table_index parmeter.
** Return in ascii order.
*/

t_symtable	*compare_tableindex(t_symtable *a, t_symtable *b)
{
	if (ft_strcmp(a->table_index, b->table_index) <= 0)
		return (a);
	return (b);
}

/*
** Compare <a> and <b> with the table_index parmeter.
** Return in reverse ascii order.
*/

t_symtable	*compare_tableindex_rev(t_symtable *a, t_symtable *b)
{
	if (ft_strcmp(a->table_index, b->table_index) > 0)
		return (a);
	return (b);
}

/*
** Return the first parameters <a> in order to put the <b> at the end.
*/

t_symtable	*compare_end(t_symtable *a, t_symtable *b)
{
	(void)b;
	return (a);
}

/*
** Return the second parameters <b> in order to put the <b> at the begining.
*/

t_symtable	*compare_first(t_symtable *a, t_symtable *b)
{
	(void)a;
	return (b);
}
