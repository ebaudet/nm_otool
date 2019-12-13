/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:23:03 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/13 22:05:07 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "nm.h"
#include "libft.h"

void	print_output(t_nm *nm, int size, char *object)
{
	t_symtable	*tmp;

	if (nm->flag & FLAG_PRINT)
	{
		if (object != NULL)
			ft_printf("\n%s(%s):\n", nm->file, object);
		else
			ft_printf("\n%s:\n", nm->file);
	}
	tmp = *(nm->list);
	while (tmp)
	{
		ft_printf("%.*s %c ", size, tmp->offset, tmp->symbol);
		if (tmp->malloc)
			ft_putstr(tmp->table_index);
		else
			ft_putprint(tmp->table_index);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
