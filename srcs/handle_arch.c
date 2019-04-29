/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:25:57 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 17:16:12 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"
#include "libftprintf.h"
#include <ranlib.h>
#include <ar.h>

void	handle_arch(t_nm *nm, char *ptr, int offset)
{
	char			*next;
	struct ar_hdr	*ar;

	if (!ft_strncmp((const char *)ptr, SYMDEF_SORTED, 20) ||
		!ft_strncmp((const char *)ptr, SYMDEF, 20))
	{
		next = ptr + offset;
		nm->flag |= FLAG_PRINT;
		while (sec_ptr(next))
		{
			handle_type(nm, next + 72 + ((ft_strlen(next + 60) - 1) / 8) * 8,
				next + 60);
			ar = (struct ar_hdr *)next;
			next += ft_atoi(ar->ar_size) + 60;
		}
	}
}
