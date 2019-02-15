/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:34:27 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/15 19:43:56 by ebaudet          ###   ########.fr       */
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
	if (ft_strcmp(a->table_index, b->table_index) < 0)
		return (a);
	return (b);
}

/*
** Compare <a> and <b> with the table_index parmeter.
** Return in resverse ascii order.
*/

t_symtable	*compare_tableindex_rev(t_symtable *a, t_symtable *b)
{
	return (compare_tableindex(b, a));
}
