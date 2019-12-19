/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_lc_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:47:39 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/19 17:48:25 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		loop_lc_segment(t_otool *otool, char *addr)
{
	struct segment_command		*sc;
	struct section				*section;
	unsigned int				k;

	sc = (struct segment_command *)addr;
	if (ft_strcmp(sc->segname, "__TEXT") == 0 || sc->cmd == LC_SEGMENT_64)
	{
		k = 0;
		addr += sizeof_segment_command(otool->arch);
		section = (struct section *)addr;
		while (k < get_addr_endian(get_segment_command_nsects((char *)sc,
			otool->arch), otool))
		{
			section = (struct section *)addr;
			addr += sizeof_section(otool->arch);
			if (sec_ptr(addr))
				return (sec_error(otool->file));
			if (ft_strcmp(section->sectname, "__text") == 0)
				if (print_section(otool, (char *)section))
					return (EXIT_FAILURE);
			k++;
		}
	}
	return (EXIT_SUCCESS);
}
